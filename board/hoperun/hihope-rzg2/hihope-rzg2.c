// SPDX-License-Identifier: GPL-2.0+
/*
 * board/hoperun/hihope-rzg2/hihope-rzg2.c
 *     This file is HiHope RZ/G2[HMN] board support.
 *
 * Copyright (C) 2021 Renesas Electronics Corporation
 */

#include <common.h>
#include <env.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/gpio.h>
#include <asm/arch/gpio.h>
#include <asm/processor.h>
#include <asm/arch/rmobile.h>
#include <asm/arch/rcar-mstp.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/libfdt.h>
#include <renesas_wdt.h>

#include "../../renesas/rzg-common/common.h"

#define RST_BASE	0xE6160000
#define RST_CA57RESCNT	(RST_BASE + 0x40)
#define RST_CA53RESCNT	(RST_BASE + 0x44)
#define RST_CA57_CODE	0xA5A5000F
#define RST_CA53_CODE	0x5A5A000F

DECLARE_GLOBAL_DATA_PTR;
#define HSUSB_MSTP704		BIT(4)	/* HSUSB */

/* HSUSB block registers */
#define HSUSB_REG_LPSTS			0xE6590102
#define HSUSB_REG_LPSTS_SUSPM_NORMAL	BIT(14)
#define HSUSB_REG_UGCTRL2		0xE6590184
#define HSUSB_REG_UGCTRL2_USB0SEL_EHCI	0x10
#define HSUSB_REG_UGCTRL2_RESERVED_3	0x1 /* bit[3:0] should be B'0001 */

#define PRR_REGISTER (0xFFF00044)

#define GPIO_HIHOPE_REV_BIT1		113	/* GP5_19 */
#define GPIO_HIHOPE_REV_BIT0		115	/* GP5_21 */
#define GPIO_HIHOPE_REV2_BOARD_CHECK	119	/* GP5_25 */

#define GPIO_BT_POWER			73	/* GP3_13 */
#define GPIO_WIFI_POWER			82	/* GP4_06 */
#define GPIO_WLAN_REG_ON		157
#define GPIO_BT_REG_ON			158

static int board_rev;

void clear_wlan_bt_reg_on(void)
{
	if (board_rev > 2) {
		gpio_request(GPIO_BT_POWER, "bt_power");
		gpio_request(GPIO_WIFI_POWER, "wifi_power");
		gpio_direction_output(GPIO_BT_POWER, 0);
		gpio_direction_output(GPIO_WIFI_POWER, 0);
	} else {
		gpio_request(GPIO_WLAN_REG_ON, "wlan_reg_on");
		gpio_request(GPIO_BT_REG_ON, "bt_reg_on");
		gpio_direction_output(GPIO_WLAN_REG_ON, 0);
		gpio_direction_output(GPIO_BT_REG_ON, 0);
	}
}

int check_rev(void)
{
	int ret = 0;

	switch (rmobile_get_cpu_type()) {
	case RMOBILE_CPU_TYPE_R8A7795:
		ret = 4;
		break;

	case RMOBILE_CPU_TYPE_R8A7796:
		if ((rmobile_get_cpu_rev_integer() == 1) &&
		    (rmobile_get_cpu_rev_fraction() < 3)) {
			ret = 2;
		} else {
			gpio_request(GPIO_HIHOPE_REV_BIT0, "hihope_rev_bit0");
			gpio_request(GPIO_HIHOPE_REV_BIT1, "hihope_rev_bit1");
			gpio_direction_input(GPIO_HIHOPE_REV_BIT1);
			gpio_direction_input(GPIO_HIHOPE_REV_BIT0);
			ret = 0x03 +
				  ((gpio_get_value(GPIO_HIHOPE_REV_BIT1) << 1) |
				    gpio_get_value(GPIO_HIHOPE_REV_BIT0));
		}
		break;

	case RMOBILE_CPU_TYPE_R8A77965:
		gpio_request(GPIO_HIHOPE_REV2_BOARD_CHECK, "hihope_rev2_check");
		gpio_direction_input(GPIO_HIHOPE_REV2_BOARD_CHECK);
		if (gpio_get_value(GPIO_HIHOPE_REV2_BOARD_CHECK)) {
			ret = 2;
		} else {
			gpio_request(GPIO_HIHOPE_REV_BIT0, "hihope_rev_bit0");
			gpio_request(GPIO_HIHOPE_REV_BIT1, "hihope_rev_bit1");
			gpio_direction_input(GPIO_HIHOPE_REV_BIT1);
			gpio_direction_input(GPIO_HIHOPE_REV_BIT0);
			ret = 0x03 +
				  ((gpio_get_value(GPIO_HIHOPE_REV_BIT1) << 1) |
				    gpio_get_value(GPIO_HIHOPE_REV_BIT0));
		}
		break;

	default:
		ret = -1;
		break;
	}

	return ret;
}

int board_init(void)
{
	u32 i;

	/* address of boot parameters */
	gd->bd->bi_boot_params = CONFIG_SYS_TEXT_BASE + 0x50000;

	/* Configure the HSUSB block */
	mstp_clrbits_le32(SMSTPCR7, SMSTPCR7, HSUSB_MSTP704);
	/*
	 * We need to add a barrier instruction after HSUSB module stop release.
	 * This barrier instruction can be either reading back the same MSTP
	 * register or any other register in the same IP block. So like linux
	 * adding check for MSTPSR register, which indicates the clock has been
	 * started.
	 */
	for (i = 1000; i > 0; --i) {
		if (!(readl(MSTPSR7) & HSUSB_MSTP704))
			break;
		cpu_relax();
	}

	/* Select EHCI/OHCI host module for USB2.0 ch0 */
	writel(HSUSB_REG_UGCTRL2_USB0SEL_EHCI | HSUSB_REG_UGCTRL2_RESERVED_3,
	       HSUSB_REG_UGCTRL2);
	/* low power status */
	setbits_le16(HSUSB_REG_LPSTS, HSUSB_REG_LPSTS_SUSPM_NORMAL);

	board_rev = check_rev();
	if (board_rev < 0)
		return board_rev;

	clear_wlan_bt_reg_on();

	return 0;
}

void reset_cpu(void)
{
	unsigned long midr, cputype;

	asm volatile("mrs %0, midr_el1" : "=r" (midr));
	cputype = (midr >> 4) & 0xfff;

	if (cputype == 0xd03)
		writel(RST_CA53_CODE, RST_CA53RESCNT);
	else
		writel(RST_CA57_CODE, RST_CA57RESCNT);
}

#if defined(CONFIG_MULTI_DTB_FIT)
/* If the firmware passed a device tree, use it for board identification. */
extern u64 rcar_atf_boot_args[];

static bool is_hoperun_hihope_rzg2_board(const char *board_name)
{
	void *atf_fdt_blob = (void *)(rcar_atf_boot_args[1]);
	bool ret = false;

	if ((fdt_magic(atf_fdt_blob) == FDT_MAGIC) &&
	    (fdt_node_check_compatible(atf_fdt_blob, 0, board_name) == 0))
		ret = true;

	return ret;
}

int board_fit_config_name_match(const char *name)
{
	if (is_hoperun_hihope_rzg2_board("hoperun,hihope-rzg2m") &&
	    !strcmp(name, "r8a774a1-hihope-rzg2m-u-boot"))
		return 0;

	if (is_hoperun_hihope_rzg2_board("hoperun,hihope-rzg2n") &&
	    !strcmp(name, "r8a774b1-hihope-rzg2n-u-boot"))
		return 0;

	if (is_hoperun_hihope_rzg2_board("hoperun,hihope-rzg2h") &&
	    !strcmp(name, "r8a774e1-hihope-rzg2h-u-boot"))
		return 0;

	return -1;
}
#endif

int board_late_init(void)
{
#ifdef CONFIG_WDT_RENESAS
	reinitr_wdt();
#endif

	env_set_hex("board_rev", board_rev);

	return 0;
}

static const char * const rzg2h_dt_ecc_partial[] = {
	"/memory@48000000", "reg", "<0x0 0x48000000 0x0 0x78000000>",
	"/memory@500000000", NULL, NULL,
	"/memory@600000000", "reg", "<0x6 0x00000000 0x0 0x80000000>",
	"/memory@600000000", "device_type", "memory",
};

static const char * const rzg2h_dt_ecc_full_single[] = {
	"/memory@48000000", "reg", "<0x0 0x48000000 0x0 0x4C000000>",
	"/memory@500000000", NULL, NULL,
	"/memory@600000000", "reg", "<0x6 0x00000000 0x0 0x40000000>",
	"/memory@600000000", "device_type", "memory",
	"/reserved-memory/linux,lossy_decompress", NULL, NULL,
	"/reserved-memory/linux,cma", "reg", "<0x0 0x50000000 0x0 0x20000000>",
	"/reserved-memory/linux,multimedia", "reg",
					     "<0x0 0x70000000 0x0 0x10000000>",
	"/mmngr", "memory-region", "<&/reserved-memory/linux,multimedia>",
};

static const char * const rzg2h_dt_ecc_full_dual[] = {
	"/memory@48000000", "reg", "<0x0 0x48000000 0x0 0x78000000>",
	"/memory@500000000", NULL, NULL,
	"/memory@600000000", NULL, NULL,
	"/reserved-memory/linux,lossy_decompress", NULL, NULL,
	"/reserved-memory/linux,cma", "reg", "<0x0 0x50000000 0x0 0x20000000>",
	"/reserved-memory/linux,multimedia", "reg",
					     "<0x0 0x70000000 0x0 0x10000000>",
	"/mmngr", "memory-region", "<&/reserved-memory/linux,multimedia>",
	"/soc/iommu@e67b0000", "status", "okay",
	"/soc/iommu@fd800000", "status", "okay",
	"/soc/iommu@fd950000", "status", "okay",
	"/soc/iommu@fd960000", "status", "okay",
	"/soc/iommu@fd970000", "status", "okay",
};

static const char * const rzg2m_dt_ecc_full_single[] = {
	"/memory@48000000", "reg", "<0x0 0x48000000 0x0 0x4C000000>",
	"/memory@600000000", "reg", "<0x6 0x00000000 0x0 0x40000000>",
	"/memory@600000000", "device_type", "memory",
	"/reserved-memory/linux,lossy_decompress", NULL, NULL,
	"/reserved-memory/linux,cma", "reg", "<0x0 0x50000000 0x0 0x20000000>",
	"/reserved-memory/linux,multimedia", "reg",
					     "<0x0 0x70000000 0x0 0x10000000>",
	"/mmngr", "memory-region", "<&/reserved-memory/linux,multimedia>",
};

static const char * const rzg2m_dt_ecc_full_dual[] = {
	"/memory@48000000", "reg", "<0x0 0x48000000 0x0 0x78000000>",
	"/memory@600000000", NULL, NULL,
	"/reserved-memory/linux,lossy_decompress", NULL, NULL,
	"/reserved-memory/linux,cma", "reg", "<0x0 0x50000000 0x0 0x20000000>",
	"/reserved-memory/linux,multimedia", "reg",
					     "<0x0 0x70000000 0x0 0x10000000>",
	"/mmngr", "memory-region", "<&/reserved-memory/linux,multimedia>",
	"/soc/mmu@e67b0000", "status", "okay",
	"/soc/mmu@fd800000", "status", "okay",
	"/soc/mmu@fd950000", "status", "okay",
};

static const char * const rzg2n_dt_ecc_full_single[] = {
	"/memory@48000000", "reg", "<0x0 0x48000000 0x0 0x78000000>",
	"/memory@480000000", "reg", "<0x4 0x80000000 0x0 0x14000000>",
	"/reserved-memory/linux,lossy_decompress", NULL, NULL,
	"/reserved-memory/linux,cma", "reg", "<0x0 0x50000000 0x0 0x20000000>",
	"/reserved-memory/linux,multimedia", "reg",
					     "<0x0 0x70000000 0x0 0x10000000>",
	"/mmngr", "memory-region", "<&/reserved-memory/linux,multimedia>",
};

int ft_verify_fdt(void *fdt)
{
	const char **fdt_dt = NULL;
	int use_ecc, ecc_mode, size;
	struct pt_regs regs;

	size = 0;
	/* Setting SiP Service GET_ECC_MODE command*/
	regs.regs[0] = RZG_SIP_SVC_GET_ECC_MODE;
	smc_call(&regs);
	/* First result is USE ECC or not, Second result is ECC MODE*/
	use_ecc = regs.regs[0];
	ecc_mode = regs.regs[1];

	if (use_ecc == 1) {
		switch (rmobile_get_cpu_type()) {
		case RMOBILE_CPU_TYPE_R8A7795:
			switch (ecc_mode) {
			case 0:
				fdt_dt = (const char **)rzg2h_dt_ecc_partial;
				size = ARRAY_SIZE(rzg2h_dt_ecc_partial);
				break;
			case 1:
				fdt_dt = (const char **)rzg2h_dt_ecc_full_dual;
				size = ARRAY_SIZE(rzg2h_dt_ecc_full_dual);
				break;
			case 2:
				fdt_dt = (const char **)rzg2h_dt_ecc_full_single;
				size = ARRAY_SIZE(rzg2h_dt_ecc_full_single);
				break;
			default:
				printf("Not support changing device-tree to ");
				printf("compatible with ECC_MODE = %d\n", ecc_mode);
				return 1;
			};
			break;
		case RMOBILE_CPU_TYPE_R8A7796:
			switch (ecc_mode) {
			case 1:
				fdt_dt = (const char **)rzg2m_dt_ecc_full_dual;
				size = ARRAY_SIZE(rzg2m_dt_ecc_full_dual);
				break;
			case 2:
				/* ECC Single only configurate in RZ/G2M rev.3.0 */
				if (rmobile_get_cpu_rev_integer() == 3) {
					fdt_dt = (const char **)rzg2m_dt_ecc_full_single;
					size = ARRAY_SIZE(rzg2m_dt_ecc_full_single);
				} else {
					return 1;
				}
				break;
			default:
				printf("Not support changing device-tree to ");
				printf("compatible with ECC_MODE = %d\n", ecc_mode);
				return 1;
			};
			break;
		case RMOBILE_CPU_TYPE_R8A77965:
			switch (ecc_mode) {
			case 2:
				fdt_dt = (const char **)rzg2n_dt_ecc_full_single;
				size = ARRAY_SIZE(rzg2n_dt_ecc_full_single);
				break;
			default:
				printf("Not support changing device-tree to ");
				printf("compatible with ECC_MODE = %d\n", ecc_mode);
				return 1;
			};
			break;
		default:
			printf("Invalid Platform\n");
			return 1;
		}
	} else {
		return 1;
	}

	return update_fdt(fdt, fdt_dt, size);
}
