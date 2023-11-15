/* SPDX-License-Identifier: GPL-2.0 */
/*
 * R-Car R9A07G043F Clock Module
 *
 * Copyright (C) 2022 Renesas Electronics Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 */

#include <clk-uclass.h>
#include <dm.h>
#include <linux/clk-provider.h>
#include <dt-bindings/clock/r9a07g043f-cpg.h>
#include "renesas-rzg2l-cpg.h"


extern int rzg2l_clk_probe(struct udevice *dev);
extern int rzg2l_clk_remove(struct udevice *dev);
extern const struct clk_ops rzg2l_clk_ops;

enum clk_ids {
	/* Core Clock Outputs exported to DT */
	LAST_DT_CORE_CLK = R9A07G043F_OSCCLK,

	/* External Input Clocks */
	CLK_XINCLK,

	/* Internal Core Clocks */
	CLK_OSC_DIV1000,
	CLK_PLL1,
	CLK_SEL_PLL1,
	CLK600,
	CLK_PLL2,
	CLK_PLL2_1,
	CLK_SEL_PLL2_1,
	CLK800FIX_C,
	CLK800FIX_CDIV2,
	CLK200FIX_C,
	CLK200_C,
	CLK100FIX_C,
	CLK_PLL2_2,
	CLK_SEL_PLL2_2,
	CLK533_C,
	CLK533_CDIV2,
	CLK533FIX_C,
	CLK533FIX_CDIV2,
	CLK533FIX_LPCLK,
	CLK_PLL3,
	CLK_PLL3_1,
	CLK_SEL_PLL3_1,
	CLK800FIX_CD,
	CLK800FIX_DIV2,
	CLK200FIX_CD,
	CLK200_CD,
	CLK100FIX_CD,
	CLK100_CD,
	CLK_PLL3_2,
	CLK_SEL_PLL3_2,
	CLK_PLL3_3,
	CLK_SEL_PLL3_3,
	CLK533_CD,
	CLK533FIX_CD,
	CLK_PLL4,
	CLK_SEL_PLL4,
	CLK_PLL5,
	CLK_PLL5_1,
	CLK_SEL_PLL5_1,
	CLK_PLL5_3,
	CLK_SEL_PLL5_3,
	CLK_PLL5_2,
	CLK_SEL_PLL5_2,
	CLK_SEL_PLL5_4,
	CLK_250,
	CLK_PLL6,
	CLK_PLL6_1,
	CLK_SEL_PLL6_1,
	CLK_SEL_G1_1,
	CLK_SEL_G1_2,
	CLK_SEL_G2,
	CLK_PLL6_DIV2,
	CLK_SEL_PLL6_2,

	/* Module Clocks */
	CLK_MODE_BASE,
};

/*Divider tables*/
static struct clk_div_table divdsilpcl[] = {
	{0, 16},
	{1, 32},
	{2, 64},
	{3, 128},
};

static struct clk_div_table dtable_2b[] = {
	{0, 1},
	{1, 2},
	{2, 4},
	{3, 8},
};

static struct clk_div_table dtable_3b[] = {
	{0, 1},
	{1, 2},
	{2, 4},
	{3, 8},
	{4, 32},
};

static struct clk_div_table dtable_4b[] = {
	{0, 1},
	{1, 2},
	{2, 3},
	{3, 4},
	{4, 5},
	{5, 6},
	{6, 7},
	{7, 8},
	{8, 9},
	{9, 10},
	{10, 11},
	{11, 12},
	{12, 13},
	{13, 14},
	{14, 15},
	{15, 16},
};

/*MUX clock tables*/
static const char *sel_pll1[]	= {"xinclk", ".pll1"};
static const char *sel_pll2_1[]	= {"xinclk", ".pll2_1"};
static const char *sel_pll2_2[]	= {"xinclk", ".pll2_2"};
static const char *sel_pll3_1[]	= {"xinclk", ".pll3_1"};
static const char *sel_pll3_2[]	= {"xinclk", ".pll3_2"};
static const char *sel_pll3_3[]	= {".sel_pll3_2", ".pll3_3"};
static const char *sel_pll4[]	= {".osc_div1000", ".pll4"};
static const char *sel_pll5_1[]	= {"xinclk", ".pll5_1"};
static const char *sel_pll5_3[]	= {"xinclk", ".pll5_3"};
static const char *sel_pll5_4[]	= {".sel_pll5_1", ".sel_pll5_3"};
static const char *sel_pll5_2[]	= {"xinclk", ".pll5_2"};
static const char *sel_pll6_1[]	= {"xinclk", ".pll6"};
static const char *sel_g1_1[]	= {".sel_pll6_1", ".clk600"};
static const char *sel_g1_2[]	= {".clk533fix_cd", ".clk800fix_div2"};
static const char *sel_g2[]	= {".sel_g1_1", ".sel_g1_2"};
static const char *sel_pll6_2[]	= {".pll6_div2", ".clk250"};
static const char *sel_eth[]	= {"xinclk", ".sel_pll6_2"};
static const char *sel_shdi[]	= {".clk800fix_c", ".clk533_c",
				   ".clk800fix_cdiv2", ".clk533_cdiv2"};

static const struct cpg_core_clk r9a07g043f_core_clks[] = {
	/* External Clock Inputs */
	DEF_INPUT("xinclk",	 CLK_XINCLK),

	/* Internal Core Clocks */
	DEF_FIXED(".osc", R9A07G043F_OSCCLK, CLK_XINCLK, 1, 1),
	DEF_FIXED(".osc_div1000", CLK_OSC_DIV1000, CLK_XINCLK, 1, 1000),
	DEF_BASE(".pll1", CLK_PLL1, CLK_TYPE_PLL1, CLK_XINCLK),
	DEF_BASE(".pll2", CLK_PLL2, CLK_TYPE_PLL2, CLK_XINCLK),
	DEF_BASE(".pll3", CLK_PLL3, CLK_TYPE_PLL3, CLK_XINCLK),
	DEF_BASE(".pll4", CLK_PLL4, CLK_TYPE_PLL4, CLK_XINCLK),
	DEF_BASE(".pll5", CLK_PLL5, CLK_TYPE_PLL5, CLK_XINCLK),
	DEF_BASE(".pll6", CLK_PLL6, CLK_TYPE_PLL6, CLK_XINCLK),
	DEF_MUX(".sel_pll1", CLK_SEL_PLL1, SEL_PLL1,
			sel_pll1, 2, CLK_MUX_READ_ONLY),
	DEF_FIXED(".clk600", CLK600, CLK_PLL1, 1, 2),
	DEF_FIXED(".pll2_1", CLK_PLL2_1, CLK_PLL2, 1, 2),
	DEF_MUX(".sel_pll2_1", CLK_SEL_PLL2_1, SEL_PLL2_1,
			sel_pll2_1, 2, CLK_MUX_READ_ONLY),
	DEF_FIXED(".clk800fix_c", CLK800FIX_C, CLK_SEL_PLL2_1, 1, 2),
	DEF_FIXED(".clk800fix_cdiv2", CLK800FIX_CDIV2, CLK800FIX_C, 1, 2),
	DEF_FIXED(".clk200fix_c", CLK200FIX_C, CLK800FIX_C, 1, 4),
	DEF_DIV(".clk200_c", CLK200_C, CLK200FIX_C,
			DIVPL2B, dtable_3b, 0),
	DEF_FIXED(".clk100fix_c", CLK100FIX_C, CLK200FIX_C, 1, 2),
	DEF_FIXED(".pll2_2", CLK_PLL2_2, CLK_PLL2, 1, 6),
	DEF_MUX(".sel_pll2_2", CLK_SEL_PLL2_2, SEL_PLL2_2,
			sel_pll2_2, 2, CLK_MUX_READ_ONLY),
	DEF_DIV(".clk533_c", CLK533_C, CLK_SEL_PLL2_2,
			DIVPL2C, dtable_3b, 0),
	DEF_FIXED(".clk533_cdiv2", CLK533_CDIV2, CLK533_C, 1, 2),
	DEF_FIXED(".clk533fix_c", CLK533FIX_C, CLK_SEL_PLL2_2, 1, 1),
	DEF_FIXED(".clk533fix_cdiv2", CLK533FIX_CDIV2, CLK533FIX_C, 1, 2),
	DEF_FIXED(".clk533fix_lpclk", CLK533FIX_LPCLK, CLK533FIX_C, 1, 2),
	DEF_FIXED(".pll3_1", CLK_PLL3_1, CLK_PLL3, 1, 2),
	DEF_MUX(".sel_pll3_1", CLK_SEL_PLL3_1, SEL_PLL3_1,
			sel_pll3_1, 2, CLK_MUX_READ_ONLY),
	DEF_FIXED(".clk800fix_cd", CLK800FIX_CD, CLK_SEL_PLL3_1, 1, 2),
	DEF_FIXED(".clk800fix_div2", CLK800FIX_DIV2, CLK800FIX_CD, 1, 2),
	DEF_FIXED(".clk200fix_cd", CLK200FIX_CD, CLK800FIX_CD, 1, 4),
	DEF_FIXED(".clk100fix_cd", CLK100FIX_CD, CLK200FIX_CD, 1, 2),
	DEF_FIXED(".pll3_2", CLK_PLL3_2, CLK_PLL3, 1, 6),
	DEF_MUX(".sel_pll3_2", CLK_SEL_PLL3_2, SEL_PLL3_2,
			sel_pll3_2, 2, CLK_MUX_READ_ONLY),
	DEF_FIXED(".pll3_3", CLK_PLL3_3, CLK_PLL3, 1, 8),
	DEF_MUX(".sel_pll3_3", CLK_SEL_PLL3_3, SEL_PLL3_3,
			sel_pll3_3, 2, CLK_MUX_READ_ONLY),
	DEF_DIV(".clk533_cd", CLK533_CD, CLK_SEL_PLL3_3,
			DIVPL3C, dtable_3b, 0),
	DEF_FIXED(".clk533fix_cd", CLK533FIX_CD, CLK_SEL_PLL3_2, 1, 1),
	DEF_MUX(".sel_pll4", CLK_SEL_PLL4, SEL_PLL4,
			sel_pll4, 2, 0),
	DEF_FIXED(".pll5_1", CLK_PLL5_1, CLK_PLL5, 1, 1),
	DEF_MUX(".sel_pll5_1", CLK_SEL_PLL5_1, SEL_PLL5_1,
			sel_pll5_1, 2, CLK_MUX_READ_ONLY),
	DEF_FIXED(".pll5_3", CLK_PLL5_3, CLK_PLL5, 1, 2),
	DEF_MUX(".sel_pll5_3", CLK_SEL_PLL5_3, SEL_PLL5_3,
			sel_pll5_3, 2, CLK_MUX_READ_ONLY),
	DEF_MUX(".sel_pll5_4", CLK_SEL_PLL5_4, SEL_PLL5_4,
			sel_pll5_4, 2, 0),
	DEF_FIXED(".pll5_2", CLK_PLL5_2, CLK_PLL5, 1, 6),
	DEF_MUX(".sel_pll5_2", CLK_SEL_PLL5_2, SEL_PLL5_2,
			sel_pll5_2, 2, CLK_MUX_READ_ONLY),
	DEF_FIXED(".clk250", CLK_250, CLK_SEL_PLL5_2, 1, 2),
	DEF_MUX(".sel_pll6_1", CLK_SEL_PLL6_1, SEL_PLL6_1,
			sel_pll6_1, 2, CLK_MUX_READ_ONLY),
	DEF_MUX(".sel_g1_1", CLK_SEL_G1_1, SEL_G1_1,
			sel_g1_1, 2, CLK_MUX_READ_ONLY),
	DEF_MUX(".sel_g1_2", CLK_SEL_G1_2, SEL_G1_2,
			sel_g1_2, 2, CLK_MUX_READ_ONLY),
	DEF_MUX(".sel_g2", CLK_SEL_G2, SEL_G2,
			sel_g2, 2, 0),
	DEF_FIXED(".pll6_div2", CLK_PLL6_DIV2, CLK_PLL6, 1, 2),
	DEF_MUX(".sel_pll6_2", CLK_SEL_PLL6_2, SEL_PLL6_2,
			sel_pll6_2, 2, 0),

	/* Core output clk*/
	DEF_DIV("I", R9A07G043F_CLK_I, CLK_SEL_PLL1,
			DIVPL1, NULL, CLK_DIVIDER_POWER_OF_TWO),
	DEF_DIV("I2", R9A07G043F_CLK_I2, CLK200FIX_CD,
		DIVPL3CLK200FIX, dtable_3b, 0),
	DEF_DIV("G", R9A07G043F_CLK_G, CLK_SEL_G2,
			DIVGPU, NULL, CLK_DIVIDER_POWER_OF_TWO),
	DEF_FIXED("S0", R9A07G043F_CLK_S0, CLK_SEL_PLL4, 1, 2),
	DEF_FIXED("S1", R9A07G043F_CLK_S0, CLK_SEL_PLL4, 1, 4),
	DEF_FIXED("SPI0", R9A07G043F_CLK_SPI0, CLK533_CD, 1, 2),
	DEF_FIXED("SPI1", R9A07G043F_CLK_SPI1, CLK533_CD, 1, 4),
	DEF_MUX("SD0", R9A07G043F_CLK_SD0, SEL_SDHI0,
			sel_shdi, 4, 0),
	DEF_MUX("SD1", R9A07G043F_CLK_SD1, SEL_SDHI1,
			sel_shdi, 4, 0),
	DEF_FIXED("M0", R9A07G043F_CLK_M0, CLK200FIX_CD, 1, 1),
	DEF_FIXED("M1", R9A07G043F_CLK_M1, CLK_SEL_PLL5_1, 1, 1),
	DEF_FIXED("M2", R9A07G043F_CLK_M2, CLK533FIX_CD, 1, 2),
	DEF_2DIV("M3", R9A07G043F_CLK_M3, CLK_SEL_PLL5_4,
		DIVDSIA, DIVDSIB, dtable_2b, dtable_4b, 0),
	DEF_DIV("M4", R9A07G043F_CLK_M4, CLK533FIX_LPCLK,
			DIVDSILPCL, divdsilpcl, 0),
	DEF_MUX("HP", R9A07G043F_CLK_HP, SEL_ETH, sel_eth, 2, 0),
	DEF_FIXED("TSU", R9A07G043F_CLK_TSU, CLK800FIX_C, 1, 10),
	DEF_FIXED("ZT", R9A07G043F_CLK_ZT, CLK100FIX_CD, 1, 1),
	DEF_DIV("P0", R9A07G043F_CLK_P0, CLK100FIX_C,
			DIVPL2A, dtable_3b, 0),
	DEF_DIV("P1", R9A07G043F_CLK_P1, CLK200FIX_CD,
			DIVPL3B, dtable_3b, 0),
	DEF_DIV("P2", R9A07G043F_CLK_P2, CLK100FIX_CD,
			DIVPL3A, dtable_3b, 0),
	DEF_FIXED("AT", R9A07G043F_CLK_AT, CLK800FIX_CD, 1, 2),
};

static struct mssr_mod_clk r9a07g043f_mod_clks[] = {
	DEF_MOD("ia55",		R9A07G043F_CLK_IA55,
				R9A07G043F_CLK_P1,
				MSSR(6, (BIT(0) | BIT(1)), BIT(0))),
	DEF_MOD("syc",		R9A07G043F_CLK_SYC,
				CLK_XINCLK,
				MSSR(10, BIT(0), BIT(0))),
	DEF_MOD("dmac",		R9A07G043F_CLK_DMAC,
				R9A07G043F_CLK_P1,
				MSSR(11, (BIT(0) | BIT(1)),
					 (BIT(0) | BIT(1)))),
	DEF_MOD("mtu3",		R9A07G043F_CLK_MTU,
				R9A07G043F_CLK_P0,
				MSSR(14, BIT(0), BIT(0))),
	DEF_MOD("eth0",		R9A07G043F_CLK_ETH0,
				R9A07G043F_CLK_HP,
				MSSR(31, BIT(0), BIT(0))),
	DEF_MOD("eth1",		R9A07G043F_CLK_ETH1,
				R9A07G043F_CLK_HP,
				MSSR(31, BIT(1), BIT(1))),
	DEF_MOD("i2c0",		R9A07G043F_CLK_I2C0,
				R9A07G043F_CLK_P0,
				MSSR(32, BIT(0), BIT(0))),
	DEF_MOD("i2c1",		R9A07G043F_CLK_I2C1,
				R9A07G043F_CLK_P0,
				MSSR(32, BIT(1), BIT(1))),
	DEF_MOD("i2c2",		R9A07G043F_CLK_I2C2,
				R9A07G043F_CLK_P0,
				MSSR(32, BIT(2), BIT(2))),
	DEF_MOD("i2c3",		R9A07G043F_CLK_I2C3,
				R9A07G043F_CLK_P0,
				MSSR(32, BIT(3), BIT(3))),
	DEF_MOD("scif0",	R9A07G043F_CLK_SCIF0,
				R9A07G043F_CLK_P0,
				MSSR(33, BIT(0), BIT(0))),
	DEF_MOD("scif1",	R9A07G043F_CLK_SCIF1,
				R9A07G043F_CLK_P0,
				MSSR(33, BIT(1), BIT(1))),
	DEF_MOD("scif2",	R9A07G043F_CLK_SCIF2,
				R9A07G043F_CLK_P0,
				MSSR(33, BIT(2), BIT(2))),
	DEF_MOD("scif3",	R9A07G043F_CLK_SCIF3,
				R9A07G043F_CLK_P0,
				MSSR(33, BIT(3), BIT(3))),
	DEF_MOD("scif4",	R9A07G043F_CLK_SCIF4,
				R9A07G043F_CLK_P0,
				MSSR(33, BIT(4), BIT(4))),
	DEF_MOD("sci0",		R9A07G043F_CLK_SCI0,
				R9A07G043F_CLK_P0,
				MSSR(34, BIT(0), BIT(0))),
	DEF_MOD("sci1",		R9A07G043F_CLK_SCI1,
				R9A07G043F_CLK_P0,
				MSSR(34, BIT(1), BIT(1))),
	DEF_MOD("gpio",		R9A07G043F_CLK_GPIO,
				CLK_XINCLK,
				MSSR(38, BIT(0),
					(BIT(0) | BIT(1) | BIT(2)))),
	DEF_MOD("sdhi0",	R9A07G043F_CLK_SDHI0,
				R9A07G043F_CLK_SD0,
				MSSR(21, (BIT(0) | BIT(1) | BIT(2) | BIT(3)),
					 BIT(0))),
	DEF_MOD("sdhi1",	R9A07G043F_CLK_SDHI1,
				R9A07G043F_CLK_SD1,
				MSSR(21, (BIT(4) | BIT(5) | BIT(6) | BIT(7)),
					 BIT(1))),
	DEF_MOD("usb0",		R9A07G043F_CLK_USB0,
				R9A07G043F_CLK_P1,
				MSSR(30, (BIT(0) | BIT(2) | BIT(3)),
					 (BIT(0) | BIT(2) | BIT(3)))),
	DEF_MOD("usb1",		R9A07G043F_CLK_USB1,
				R9A07G043F_CLK_P1,
				MSSR(30, (BIT(1) | BIT(3)),
					 (BIT(1) | BIT(3)))),
	DEF_MOD("canfd",	R9A07G043F_CLK_CANFD,
				R9A07G043F_CLK_P0,
				MSSR(37, BIT(0), (BIT(0) | BIT(1)))),
	DEF_MOD("ssi0",		R9A07G043F_CLK_SSI0,
				R9A07G043F_CLK_P0,
				MSSR(28, (BIT(0) | BIT(1)), BIT(0))),
	DEF_MOD("ssi1",		R9A07G043F_CLK_SSI1,
				R9A07G043F_CLK_P0,
				MSSR(28, (BIT(2) | BIT(3)), BIT(1))),
	DEF_MOD("ssi2",		R9A07G043F_CLK_SSI2,
				R9A07G043F_CLK_P0,
				MSSR(28, (BIT(4) | BIT(5)), BIT(2))),
	DEF_MOD("ssi3",		R9A07G043F_CLK_SSI3,
				R9A07G043F_CLK_P0,
				MSSR(28, (BIT(6) | BIT(7)), BIT(3))),
	DEF_MOD("ostm0",	R9A07G043F_CLK_OSTM0,
				R9A07G043F_CLK_P0,
				MSSR(13, BIT(0), BIT(0))),
	DEF_MOD("ostm1",	R9A07G043F_CLK_OSTM1,
				R9A07G043F_CLK_P0,
				MSSR(13, BIT(1), BIT(1))),
	DEF_MOD("ostm2",	R9A07G043F_CLK_OSTM2,
				R9A07G043F_CLK_P0,
				MSSR(13, BIT(2), BIT(3))),
	DEF_MOD("wdt0",		R9A07G043F_CLK_WDT0,
				R9A07G043F_CLK_P0,
				MSSR(18, (BIT(0) | BIT(1)), BIT(0))),
	DEF_MOD("wdt_pon",	R9A07G043F_CLK_WDT_PON,
				R9A07G043F_CLK_P0,
				MSSR(18, (BIT(6) | BIT(7)), BIT(3))),
	DEF_MOD("src",		R9A07G043F_CLK_SRC,
				R9A07G043F_CLK_P0,
				MSSR(29, BIT(0), BIT(0))),
	DEF_MOD("rspi0",	R9A07G043F_CLK_RSPI0,
				R9A07G043F_CLK_P0,
				MSSR(36, BIT(0), BIT(0))),
	DEF_MOD("rspi1",	R9A07G043F_CLK_RSPI1,
				R9A07G043F_CLK_P0,
				MSSR(36, BIT(1), BIT(1))),
	DEF_MOD("rspi2",	R9A07G043F_CLK_RSPI2,
				R9A07G043F_CLK_P0,
				MSSR(36, BIT(2), BIT(2))),
	DEF_MOD("adc",		R9A07G043F_CLK_ADC,
				R9A07G043F_CLK_TSU,
				MSSR(42, (BIT(0) | BIT(1)), (BIT(0) | BIT(1)))),
	DEF_MOD("tsu",		R9A07G043F_CLK_TSU_PCLK,
				R9A07G043F_CLK_TSU,
				MSSR(43, BIT(0), BIT(0))),
	DEF_MOD("spi-multi",	R9A07G043F_CLK_SPI,
				R9A07G043F_CLK_SPI1,
				MSSR(21, (BIT(0) | BIT(1)), BIT(0))),
};

/* clock type, register offset1, register offset2, register offset3*/
static const struct cpg_pll_info cpg_pll_configs[] = {
	{ CLK_TYPE_PLL1, PLL146_CLK1_R(0), PLL146_CLK2_R(0), 0},
	{ CLK_TYPE_PLL2, PLL235_CLK1_R(0), PLL235_CLK3_R(0), PLL235_CLK4_R(0)},
	{ CLK_TYPE_PLL3, PLL235_CLK1_R(1), PLL235_CLK3_R(1), PLL235_CLK4_R(1)},
	{ CLK_TYPE_PLL4, PLL146_CLK1_R(1), PLL146_CLK2_R(1), 0},
	{ CLK_TYPE_PLL5, PLL235_CLK1_R(2), PLL235_CLK3_R(2), PLL235_CLK4_R(2)},
	{ CLK_TYPE_PLL6, PLL146_CLK1_R(2), PLL146_CLK2_R(2), 0},
};

/* Some struct value not defined: mstp_table, reset_node,get_pll_config */
 const struct cpg_mssr_info r9a07g043f_cpg_info = {
	.core_clk		= r9a07g043f_core_clks,
	.core_clk_size		= ARRAY_SIZE(r9a07g043f_core_clks),
	.mod_clk		= r9a07g043f_mod_clks,
	.mod_clk_size		= ARRAY_SIZE(r9a07g043f_mod_clks),
	.clk_extal_id		= CLK_XINCLK,
	.mod_clk_base		= CLK_MODE_BASE,
};

static const struct udevice_id r9a07g043f_clk_ids[] = {
	{
		.compatible	= "renesas,r9a07g043f-cpg",
		.data		= (ulong)&r9a07g043f_cpg_info,
	},
	{ }
};

U_BOOT_DRIVER(clk_r9a07g043f) = {
	.name		= "clk_r9a07g043f",
	.id		= UCLASS_CLK,
	.of_match	= r9a07g043f_clk_ids,
	.priv_auto	= sizeof(struct rzg2l_clk_priv),
	.ops		= &rzg2l_clk_ops,
	.probe		= rzg2l_clk_probe,
	.remove		= rzg2l_clk_remove,
};
