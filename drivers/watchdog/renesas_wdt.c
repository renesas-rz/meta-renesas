// SPDX-License-Identifier: GPL-2.0+

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <wdt.h>
#include <hang.h>
#include <asm/io.h>
#include <asm/processor.h>
#include <linux/io.h>
#include <sysreset.h>
#include <efi_loader.h>
#include <fdtdec.h>
#include <stdio.h>
#include <watchdog.h>
#include <console.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <env.h>
#include <renesas_wdt.h>

#define CODE_VAL1       0x5a5a0000 /* Code value of RWTCNT */
#define CODE_VAL2_3     0xa5a5a500 /* Code value of RWTCSRA and RWTCSRB */
#define MAX_VAL         0xffff	   /* Max count value of watchdog timer */
#define RWTCNT          0
#define RWTCSRA         4
#define RWTCSRA_WRFLG   BIT(5)
#define RWTCSRA_WOVF    BIT(4)
#define RWTCSRA_TME     BIT(7)
#define RWTCSRB         8
#define RWDT_DEFAULT_TIMEOUT	60000

/*
 * In probe, clk_rate is checked to be not more than 16 bit x biggest
 * clock divider (12 bits). d is only a factor to fully utilize the
 * WDT counter and will not exceed its 16 bits. Thus, no overflow, we
 * stay below 32 bits.
 */

#define MUL_BY_CLKS_PER_SEC(p, d) \
	DIV_ROUND_UP((d) * (p)->clk_rate, clk_divs[(p)->cks])

static const unsigned int clk_divs[] = { 1, 4, 16, 32, 64, 128, 1024, 4096 };
static bool second_init;
bool watchdog_overflow;

struct rwdt_priv {
	struct clk clk;
	void __iomem *base;
	u8 cks;
	unsigned long clk_rate;
	unsigned int timeout;
	bool is_active;
};

static const struct udevice_id rwdt_match[] = {
	{ .compatible = "renesas,r8a774a1-wdt", },
	{ .compatible = "renesas,r8a774b1-wdt", },
	{ .compatible = "renesas,r8a774c0-wdt", },
	{ .compatible = "renesas,r8a774e1-wdt", },
	{ /* sentinel */ }
};

static void rwdt_wait_cycles(struct rwdt_priv *priv, unsigned int cycles)
{
	unsigned int delay;

	delay = DIV_ROUND_UP(cycles * 1000000, priv->clk_rate);
	udelay(delay);
}

static void rwdt_write(struct rwdt_priv *priv, u32 val, unsigned int reg)
{
	if (reg == RWTCNT) {
		val &= 0xffff;
		val |= CODE_VAL1;	/* RWTCNT */
	} else {
		val &= 0xff;
		val |= CODE_VAL2_3;	/* RWTCSRA and RWTCSRB */
	}

	writel(val, priv->base + reg);
}

static int rwdt_init_timeout(struct udevice *watchdog_dev)
{
	struct rwdt_priv *priv = dev_get_priv(watchdog_dev);

	rwdt_write(priv, 65536 - MUL_BY_CLKS_PER_SEC(priv, priv->timeout),
		   RWTCNT);

	return 0;
}

int rwdt_reset(struct udevice *watchdog_dev)
{
	struct rwdt_priv *priv = dev_get_priv(watchdog_dev);

	if (priv->is_active)
		rwdt_init_timeout(watchdog_dev);

	if (second_init) {
		env_set_ulong("wdt_status", priv->is_active);
		env_set_ulong("wdt_timeout", priv->timeout * 1000);
	}

	return 0;
}

static int rwdt_expire_now(struct udevice *watchdog_dev, ulong flags)
{
	struct rwdt_priv *priv = dev_get_priv(watchdog_dev);

	if (!priv->is_active)
		return -ENODEV;
	while (readl(priv->base + RWTCSRA) & RWTCSRA_WRFLG)
		cpu_relax();

	rwdt_write(priv, MAX_VAL, RWTCNT);
	hang();
	return 0;
}

static int rwdt_stop(struct udevice *watchdog_dev)
{
	struct rwdt_priv *priv = dev_get_priv(watchdog_dev);

	if (priv->is_active) {
		rwdt_write(priv, readl(priv->base + RWTCSRA) & ~RWTCSRA_TME,
			   RWTCSRA);
		/* Delay 3 cycles before disabling module clock */
		rwdt_wait_cycles(priv, 3);
		clk_disable(&priv->clk);
		priv->is_active = 0;

		/* Change environment variables */
		if (second_init == 1) {
			env_set_ulong("wdt_status", 0);
			env_save();
		}
	}
	return 0;
}

static int rwdt_start(struct udevice *watchdog_dev, u64 timeout, ulong flag)
{
	struct rwdt_priv *priv = dev_get_priv(watchdog_dev);
	u8 val;
	int ret;

	/*
	 * Watchdog timeout must be equal or bigger than
	 * default timeout to avoid the case watchdog will reset
	 * when not completing loading Kernel
	 */
	if (timeout < RWDT_DEFAULT_TIMEOUT) {
		printf("Input timeout must be equal or bigger than ");
		printf("default timeout %d(ms)\n", RWDT_DEFAULT_TIMEOUT);
		timeout = RWDT_DEFAULT_TIMEOUT;
	}

	priv->timeout = timeout / 1000;

	if (priv->is_active) {
		rwdt_init_timeout(watchdog_dev);
	} else {
		/* Re-supply clock source for watchdog */
		ret = clk_enable(&priv->clk);
		if (ret) {
			printf("Failed to enable clk for wdt\n");
			return ret;
		}
		priv->clk_rate = clk_get_rate(&priv->clk);
		/* Stop the timer before we modify any register */
		val = readl(priv->base + RWTCSRA) & ~RWTCSRA_TME;
		rwdt_write(priv, val, RWTCSRA);
		/* Delay 2 cycles before setting watchdog counter */
		rwdt_wait_cycles(priv, 2);
		rwdt_init_timeout(watchdog_dev);
		rwdt_write(priv, priv->cks, RWTCSRA);
		rwdt_write(priv, 0, RWTCSRB);

		while (readl(priv->base + RWTCSRA) & RWTCSRA_WRFLG)
			cpu_relax();

		rwdt_write(priv, priv->cks | RWTCSRA_TME, RWTCSRA);
		priv->is_active = 1;
	}

	/*
	 * Flag decides to change watchdog environment variables
	 * flag = 1: Change environment variables.
	 * Other cases: Do not change evironment variables.
	 */
	if (flag == 1) {
		env_set_ulong("wdt_status", 1);
		env_set_ulong("wdt_timeout", timeout);
		env_save();
	}

	return 0;
}

int reinitr_wdt(void)
{
	u64 timeout;
	int ret;

	if (uclass_get_device(UCLASS_WDT, 0,
			      (struct udevice **)&gd->watchdog_dev)) {
		printf("Re-init wdt failed!\n");
		return -ENODEV;
	}

	timeout = env_get_ulong("wdt_timeout", 10, 0);
	ret = wdt_start(gd->watchdog_dev, timeout, 0);

	if (env_get_ulong("wdt_status", 2, 1)) {
		printf("U-boot WDT started!\n");
	} else {
		ret = wdt_stop(gd->watchdog_dev);
		printf("U-boot WDT stopped!\n");
	}
	second_init = 1;
	return ret;
}

static int rwdt_probe(struct udevice *watchdog_dev)
{
	struct rwdt_priv *priv = dev_get_priv(watchdog_dev);
	int ret, i;
	unsigned long clks_per_sec;

	priv->base = (void *) devfdt_get_addr(watchdog_dev);
	printf("WDT:   watchdog@%p\n", priv->base);
	if (!priv->base) {
		printf("failed to get wdt addr\n");
		return -EINVAL;
	}

	ret = clk_get_by_index(watchdog_dev, 0, &priv->clk);
	if (ret)
		return ret;

	ret = clk_enable(&priv->clk);
	if (ret)
		return ret;
	priv->clk_rate = clk_get_rate(&priv->clk);

	for (i = ARRAY_SIZE(clk_divs) - 1; i >= 0; i--) {
		clks_per_sec = priv->clk_rate / clk_divs[i];
		if (clks_per_sec && clks_per_sec < 65536) {
			priv->cks = i;
			break;
		}
	}

	watchdog_overflow = (readl(priv->base + RWTCSRA) & RWTCSRA_WOVF) >> 4;

	return 0;
}

static const struct wdt_ops rwdt_ops = {
	.start		= rwdt_start,
	.stop		= rwdt_stop,
	.expire_now	= rwdt_expire_now,
	.reset		= rwdt_reset,
};

U_BOOT_DRIVER(renesas_wdt) = {
	.name     = "renesas-wdt",
	.id       = UCLASS_WDT,
	.of_match = rwdt_match,
	.probe    = rwdt_probe,
	.ops      = &rwdt_ops,
	.priv_auto = sizeof(struct rwdt_priv),
};
