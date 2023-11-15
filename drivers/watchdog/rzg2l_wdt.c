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
#include <linux/math64.h>
#include <rzg2l_wdt.h>

#define PECR            0x10
#define PEEN            0x14
#define WDTCNT          0x00
#define WDTSET          0x04
#define WDTTIM          0x08
#define WDTINT          0x0C
#define WDTCNT_WDTEN    BIT(0)
#define WDTINT_INTDISP  BIT(0)
#define PEEN_FORCE	BIT(0)

#define WDT_DEFAULT_TIMEOUT             60000

/* Setting period time register only 12 bit set in WDTSET[31:20] */
#define WDTSET_COUNTER_MASK             (0xFFF00000)
#define WDTSET_COUNTER_VAL(f)           ((f) << 20)

#define F2CYCLE_NSEC(f)                 (1000000000 / (f))

#define MICRO				1000000UL
/* Clock Control Register WDT (CPG_CLKON_WDT) */
#define CPG_CLKON_WDT			0x11010548
/* Reset Control Register WDT (CPG_RST_WDT) */
#define CPG_RST_WDT			0x11010848

static bool second_init;
bool watchdog_overflow;

struct rzg2l_wdt_priv {
	struct clk clk;
	void __iomem *base;
	unsigned long osc_clk_rate;
	unsigned int timeout;
	bool is_active;
	unsigned long delay;
};

static const struct udevice_id rzg2l_wdt_match[] = {
	{ .compatible = "renesas,r9a07g044c-wdt", },
	{ .compatible = "renesas,r9a07g044l-wdt", },
	{ .compatible = "renesas,r9a07g054l-wdt", },
	{ .compatible = "renesas,r9a07g043u-wdt", },
	{ .compatible = "renesas,r9a07g043f-wdt", },
	{ .compatible = "renesas,r9a07g044-wdt", },
	{ /* sentinel */ }
};

static void rzg2l_wdt_wait_delay(struct rzg2l_wdt_priv *priv)
{
	/* delay timer when change the setting register */
	ndelay(priv->delay);
}

static u32 rzg2l_wdt_get_cycle_usec(unsigned long cycle, u32 wdttime)
{

	u64 timer_cycle_us = 1024 * 1024ULL * ((u64)wdttime + 1) * MICRO;

	return div64_ul(timer_cycle_us, cycle);
}

static void rzg2l_wdt_write(struct rzg2l_wdt_priv *priv, u32 val, unsigned int reg)
{
	if (reg == WDTSET)
		val &= WDTSET_COUNTER_MASK;

	writel(val, priv->base + reg);
	/* Registers other than the WDTINT is always synchronized with WDT_CLK */
	if (reg != WDTINT)
		rzg2l_wdt_wait_delay(priv);

}

static void rzg2l_wdt_init_timeout(struct udevice *watchdog_dev)
{
	struct rzg2l_wdt_priv *priv = dev_get_priv(watchdog_dev);
	u32 time_out;

	/* Clear Lapsed Time Register and clear Interrupt */
	rzg2l_wdt_write(priv, WDTINT_INTDISP, WDTINT);

	/* 2 consecutive overflow cycle needed to trigger reset */
	time_out = (priv->timeout * (MICRO / 2)) /
		   rzg2l_wdt_get_cycle_usec(priv->osc_clk_rate, 0);

	rzg2l_wdt_write(priv, WDTSET_COUNTER_VAL(time_out), WDTSET);
}

int rzg2l_wdt_reset(struct udevice *watchdog_dev)
{
	struct rzg2l_wdt_priv *priv = dev_get_priv(watchdog_dev);

	if (priv->is_active)
		rzg2l_wdt_init_timeout(watchdog_dev);

	if (second_init) {
		env_set_ulong("wdt_status", priv->is_active);
		env_set_ulong("wdt_timeout", priv->timeout * 1000);
	}

	return 0;
}

static int rzg2l_expire_now(struct udevice *watchdog_dev, ulong flags)
{
	struct rzg2l_wdt_priv *priv = dev_get_priv(watchdog_dev);

	if (!priv->is_active)
		return -ENODEV;

	/* Generate Reset (WDTRSTB) Signal on parity error */
	rzg2l_wdt_write(priv, 0, PECR);

	/* Force parity error */
	rzg2l_wdt_write(priv, PEEN_FORCE, PEEN);
	hang();

	return 0;
}

static int rzg2l_wdt_stop(struct udevice *watchdog_dev)
{
	struct rzg2l_wdt_priv *priv = dev_get_priv(watchdog_dev);

	if (priv->is_active) {

		/* If the watchdog is active,
		 * hard code to reset the module for updating the WDTSET
		 */

		writel(0x00070008, CPG_RST_WDT);

		/* Hard code to disable clock source for watchdog */
		writel(0x003F00C0, CPG_CLKON_WDT);

		udelay(35);

		priv->is_active = 0;

		/* Change environment variables */
		if (second_init == 1) {
			env_set_ulong("wdt_status", 0);
			env_save();
		}
	}
	return 0;
}

static int rzg2l_wdt_start(struct udevice *watchdog_dev, u64 timeout, ulong flag)
{
	struct rzg2l_wdt_priv *priv = dev_get_priv(watchdog_dev);

	/*
	 * Watchdog timeout must be equal or bigger than
	 * default timeout to avoid the case watchdog will reset
	 * when not completing loading Kernel. If the timeout is
	 * checked, we allow the user to set a timeout less than
	 * the default timeout.
	 */

	if (timeout < WDT_DEFAULT_TIMEOUT
		&& !(flag & RZG2L_WDT_FLAG_TIMEOUT_CHECKED))
		timeout = WDT_DEFAULT_TIMEOUT;

	priv->timeout = timeout/1000;

	if (priv->is_active) {
		rzg2l_wdt_init_timeout(watchdog_dev);
	} else {

		/* Hard code to access to reset signal is stopped */
		writel(0x000F000F, CPG_RST_WDT);

		/* Hard code to access to re-supply clock source for watchdog */
		writel(0x00FF00FF, CPG_CLKON_WDT);

		udelay(35);

		/* Initialize time out */
		rzg2l_wdt_init_timeout(watchdog_dev);
		/* Initialize watchdog counter register */
		rzg2l_wdt_write(priv, 0, WDTTIM);
		/* Enable watchdog timer*/
		rzg2l_wdt_write(priv, WDTCNT_WDTEN, WDTCNT);
		priv->is_active = 1;
	}

	/* Flag decides to change watchdog environment variables
	 * flag = 1: Change environment variables.
	 * Other cases: Do not change evironment variables.
	 */

	if (flag & RZG2L_WDT_FLAG_WRITE_TO_ENV) {
		env_set_ulong("wdt_status", 1);
		env_set_ulong("wdt_timeout", timeout);
		env_save();
	}
	return 0;
}

int rzg2l_reinitr_wdt(void)
{
	u64 timeout;
	int ret;

	if (uclass_get_device(UCLASS_WDT, 0,
				(struct udevice **)&gd->watchdog_dev)) {
		printf("Re-init wdt failed!\n");
		return -ENODEV;
	}

	timeout = env_get_ulong("wdt_timeout", 10, 0);

	ret = wdt_stop(gd->watchdog_dev);
	if (ret != 0) {
		printf("WDT:   Failed to stop\n");
		return 0;
	}

	ret = wdt_start(gd->watchdog_dev, timeout, 0);
	if (ret != 0) {
		printf("WDT:   Failed to start\n");
		return 0;
	}

	if (env_get_ulong("wdt_status", 2, 1)) {
		printf("U-boot WDT started!\n");
	} else {
		ret = wdt_stop(gd->watchdog_dev);
		printf("U-boot WDT stopped!\n");
	}
	second_init = 1;

	return ret;
}

static int rzg2l_wdt_probe(struct udevice *watchdog_dev)
{
	struct rzg2l_wdt_priv *priv = dev_get_priv(watchdog_dev);
	unsigned long pclk_rate;
	int ret;

	priv->base = dev_read_addr_ptr(watchdog_dev);
	printf("WDT:   watchdog@%p\n", priv->base);
	if (!priv->base) {
		printf("failed to get wdt addr\n");
		return -EINVAL;
	}
	/* Get watchdog main clock */
	ret = clk_get_by_index(watchdog_dev, 0, &priv->clk);
	if (ret) {
		printf("failed to get by index oscclk\n");
		return -EINVAL;
	}
	priv->osc_clk_rate = clk_get_rate(&priv->clk);

	/* Get Peripheral clock
	 * Because pclk is not defined in the CPG clock
	 * Hard code to set pclk rate
	 */
	pclk_rate = 100000000;

	priv->delay = F2CYCLE_NSEC(priv->osc_clk_rate) * 6 + F2CYCLE_NSEC(pclk_rate) * 9;

	return 0;
}

static const struct wdt_ops rzg2l_wdt_ops = {
	.start		= rzg2l_wdt_start,
	.stop		= rzg2l_wdt_stop,
	.reset		= rzg2l_wdt_reset,
	.expire_now	= rzg2l_expire_now,
};

U_BOOT_DRIVER(rzg2l_wdt) = {
	.name     = "rzg2l-wdt",
	.id       = UCLASS_WDT,
	.of_match = rzg2l_wdt_match,
	.probe    = rzg2l_wdt_probe,
	.ops      = &rzg2l_wdt_ops,
	.priv_auto = sizeof(struct rzg2l_wdt_priv),
};
