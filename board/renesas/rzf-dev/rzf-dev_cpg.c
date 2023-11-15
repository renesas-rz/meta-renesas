// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 */

#include <common.h>
#include <renesas/rzf-dev/rzf-dev_def.h>
#include <renesas/rzf-dev/rzf-dev_cpg_regs.h>
#include <renesas/rzf-dev/mmio.h>
#include <linux/delay.h>

#define CPG_RST_DDR_OPT_VALUE		(0x00000000)

#define	CPG_OFF			(0)
#define	CPG_ON			(1)

#define CPG_T_CLK		(0)
#define CPG_T_RST		(1)

typedef struct {
	uintptr_t reg;
	uintptr_t mon;
	uint32_t  val;
	uint32_t  type;
} CPG_SETUP_DATA;

typedef struct {
	uintptr_t reg;
	uint32_t  val;
} CPG_REG_SETTING;

typedef struct {
	CPG_REG_SETTING		clk1_dat;
	CPG_REG_SETTING		clk2_dat;
	CPG_REG_SETTING		stby_dat;
} CPG_PLL_SETDATA_146;

typedef struct {
	CPG_REG_SETTING		clk1_dat;
	CPG_REG_SETTING		clk2_dat;
	CPG_REG_SETTING		clk3_dat;
	CPG_REG_SETTING		clk4_dat;
	CPG_REG_SETTING		clk5_dat;
	CPG_REG_SETTING		stby_dat;
} CPG_PLL_SETDATA_235;

static CPG_PLL_SETDATA_146 cpg_pll4_setdata = {
#if (CONFIG_RZF_DDR_PLL4 ==1600)
	{ CPG_PLL4_CLK1, 0xFAE13203 },
	{ CPG_PLL4_CLK2, 0x00081000 },
#elif (CONFIG_RZF_DDR_PLL4 == 1333)
	{ CPG_PLL4_CLK1, 0xA66629C3 },
	{ CPG_PLL4_CLK2, 0x00080D00 },
#else
#error "Unknown Board Type."
#endif
	{ CPG_PLL4_STBY, 0x00010001 }
};

static CPG_PLL_SETDATA_146 cpg_pll6_setdata = {
	{ CPG_PLL6_CLK1, 0x00003e83 },
	{ CPG_PLL6_CLK2, 0x00082D02 },
	{ CPG_PLL6_STBY, 0x00010001 }, /* SSC OFF */
};

#define	CPG_PLL2_INDEX					(0)
#define	CPG_PLL3_INDEX					(1)
#define	CPG_PLL5_INDEX					(2)

static CPG_SETUP_DATA cpg_clk_on_tbl[] = {

	{		/* DMAC */
		(uintptr_t)CPG_CLKON_DAMC_REG,
		(uintptr_t)CPG_CLKMON_DAMC_REG,
		0x00030003,
		CPG_T_CLK
	},
	{		/* OSTM */
		(uintptr_t)CPG_CLKON_OSTM,
		(uintptr_t)CPG_CLKMON_OSTM,
		0x00060000,
		CPG_T_CLK
	},
	{		/* MTU */
		(uintptr_t)CPG_CLKON_MTU,
		(uintptr_t)CPG_CLKMON_MTU,
		0x00010000,
		CPG_T_CLK
	},
	{		/* POE3 */
		(uintptr_t)CPG_CLKON_POE3,
		(uintptr_t)CPG_CLKMON_POE3,
		0x00010000,
		CPG_T_CLK
	},
	{		/* WDT */
		(uintptr_t)CPG_CLKON_WDT,
		(uintptr_t)CPG_CLKMON_WDT,
		0x00300000,
		CPG_T_CLK
	},
#ifndef CONFIG_DEBUG_RZF_FPGA
	{		/* DDR */
		(uintptr_t)CPG_CLKON_DDR,
		(uintptr_t)CPG_CLKMON_DDR,
		0x00030000,
		CPG_T_CLK
	},
#else
	{		/* DDR */
		(uintptr_t)CPG_CLKON_DDR,
		(uintptr_t)CPG_CLKMON_DDR,
		0x00030003,
		CPG_T_CLK
	},
	{		/* SYSC */
		(uintptr_t)CPG_CLKON_SYSC,
		(uintptr_t)CPG_CLKMON_SYSC,
		0x00010001,
		CPG_T_CLK
	},
#endif
	{		/* SPI_MULTI */
		(uintptr_t)CPG_CLKON_SPI_MULTI,
		(uintptr_t)CPG_CLKMON_SPI_MULTI,
		0x00030003,
		CPG_T_CLK
	},
	{		/* SDHI */
		(uintptr_t)CPG_CLKON_SDHI,
		(uintptr_t)CPG_CLKMON_SDHI,
		0x00ff00ff,
		CPG_T_CLK
	},
	{		/* Serial Sound Interface */
		(uintptr_t)CPG_CLKON_SSI,
		(uintptr_t)CPG_CLKMON_SSI,
		0x00ff0000,
		CPG_T_CLK
	},
	{		/* Sampling Rate Converter */
		(uintptr_t)CPG_CLKON_SRC,
		(uintptr_t)CPG_CLKMON_SRC,
		0x00010000,
		CPG_T_CLK
	},
	{		/* USB2.0 */
		(uintptr_t)CPG_CLKON_USB,
		(uintptr_t)CPG_CLKMON_USB,
		0x000f0000,
		CPG_T_CLK
	},
	{		/* ETHER */
		(uintptr_t)CPG_CLKON_ETH,
		(uintptr_t)CPG_CLKMON_ETH,
		0x00030000,
		CPG_T_CLK
	},
	{		/* I2C */
		(uintptr_t)CPG_CLKON_I2C,
		(uintptr_t)CPG_CLKMON_I2C,
		0x000f0000,
		CPG_T_CLK
	},
	{		/* SCIF */
		(uintptr_t)CPG_CLKON_SCIF,
		(uintptr_t)CPG_CLKMON_SCIF,
		0x001f0001,
		CPG_T_CLK
	},
	{		/* SCI */
		(uintptr_t)CPG_CLKON_SCI,
		(uintptr_t)CPG_CLKMON_SCI,
		0x00030000,
		CPG_T_CLK
	},
	{		/* IrDA */
		(uintptr_t)CPG_CLKON_IRDA,
		(uintptr_t)CPG_CLKMON_IRDA,
		0x00010000,
		CPG_T_CLK
	},
	{		/* SPI */
		(uintptr_t)CPG_CLKON_RSPI,
		(uintptr_t)CPG_CLKMON_RSPI,
		0x00070000,
		CPG_T_CLK
	},
	{		/* CAN */
		(uintptr_t)CPG_CLKON_CANFD,
		(uintptr_t)CPG_CLKMON_CANFD,
		0x00010000,
		CPG_T_CLK
	},
	{		/* GPIO */
		(uintptr_t)CPG_CLKON_GPIO,
		(uintptr_t)CPG_CLKMON_GPIO,
		0x00010001,
		CPG_T_CLK
	},
	{		/* ADC */
		(uintptr_t)CPG_CLKON_ADC,
		(uintptr_t)CPG_CLKMON_ADC,
		0x00030000,
		CPG_T_CLK
	},
	{		/* Thermal Sensor Unit */
		(uintptr_t)CPG_CLKON_TSU,
		(uintptr_t)CPG_CLKMON_TSU,
		0x00010000,
		CPG_T_CLK
	}
};

static CPG_SETUP_DATA cpg_reset_tbl[] = {
	{		/* DMAC */
		(uintptr_t)CPG_RST_DMAC,
		(uintptr_t)CPG_RSTMON_DMAC,
		0x00030003,
		CPG_T_RST
	},
	{		/* OSTM */
		(uintptr_t)CPG_RST_OSTM,
		(uintptr_t)CPG_RSTMON_OSTM,
		0x00060000,
		CPG_T_RST
	},
	{		/* MTU */
		(uintptr_t)CPG_RST_MTU,
		(uintptr_t)CPG_RSTMON_MTU,
		0x00010000,
		CPG_T_RST
	},
	{		/* POE3 */
		(uintptr_t)CPG_RST_POE3,
		(uintptr_t)CPG_RSTMON_POE3,
		0x00010000,
		CPG_T_RST
	},
	{		/* WDT */
		(uintptr_t)CPG_RST_WDT,
		(uintptr_t)CPG_RSTMON_WDT,
		0x00040000,
		CPG_T_RST
	},
#ifndef CONFIG_DEBUG_RZF_FPGA
	{		/* DDR */
		(uintptr_t)CPG_RST_DDR,
		(uintptr_t)CPG_RSTMON_DDR,
	    0x004F0000,
		CPG_T_RST
	},
#else
	{		/* DDR */
		(uintptr_t)CPG_RST_DDR,
		(uintptr_t)CPG_RSTMON_DDR,
		0x007F007F,
		CPG_T_RST
	},
	{		/* SYSC */
		(uintptr_t)CPG_RST_SYSC,
		(uintptr_t)CPG_RSTMON_SYSC,
		0x00010001,
		CPG_T_RST
	},

#endif
	{		/* SPI_MULTI */
		(uintptr_t)CPG_RST_SPI,
		(uintptr_t)CPG_RSTMON_SPI,
		0x00030003,
		CPG_T_RST
	},
	{		/* SDHI */
		(uintptr_t)CPG_RST_SDHI,
		(uintptr_t)CPG_RSTMON_SDHI,
		0x00030003,
		CPG_T_RST
	},
	{		/* Serial Sound Interface */
		(uintptr_t)CPG_RST_SSIF,
		(uintptr_t)CPG_RSTMON_SSIF,
		0x000f0000,
		CPG_T_RST
	},
	{		/* Sampling Rate Converter */
		(uintptr_t)CPG_RST_SRC,
		(uintptr_t)CPG_RSTMON_SRC,
		0x00010000,
		CPG_T_RST
	},
	{		/* USB2.0 */
		(uintptr_t)CPG_RST_USB,
		(uintptr_t)CPG_RSTMON_USB,
		0x000f0000,
		CPG_T_RST
	},
	{		/* ETHER */
		(uintptr_t)CPG_RST_ETH,
		(uintptr_t)CPG_RSTMON_ETH,
		0x00030000,
		CPG_T_RST
	},
	{		/* I2C */
		(uintptr_t)CPG_RST_I2C,
		(uintptr_t)CPG_RSTMON_I2C,
		0x000f0000,
		CPG_T_RST
	},
	{		/* SCIF */
		(uintptr_t)CPG_RST_SCIF,
		(uintptr_t)CPG_RSTMON_SCIF,
		0x001f0001,
		CPG_T_RST
	},
	{		/* SCI */
		(uintptr_t)CPG_RST_SCI,
		(uintptr_t)CPG_RSTMON_SCI,
		0x00030000,
		CPG_T_RST
	},
	{		/* IrDA */
		(uintptr_t)CPG_RST_IRDA,
		(uintptr_t)CPG_RSTMON_IRDA,
		0x00010000,
		CPG_T_RST
	},
	{		/* SPI */
		(uintptr_t)CPG_RST_RSPI,
		(uintptr_t)CPG_RSTMON_RSPI,
		0x00070000,
		CPG_T_RST
	},
	{		/* CAN */
		(uintptr_t)CPG_RST_CANFD,
		(uintptr_t)CPG_RSTMON_CANFD,
		0x00030000,
		CPG_T_RST
	},
	{		/* GPIO */
		(uintptr_t)CPG_RST_GPIO,
		(uintptr_t)CPG_RSTMON_GPIO,
		0x00070007,
		CPG_T_RST
	},
	{		/* ADC */
		(uintptr_t)CPG_RST_ADC,
		(uintptr_t)CPG_RSTMON_ADC,
		0x00030000,
		CPG_T_RST
	},
	{		/* Thermal Sensor Unit */
		(uintptr_t)CPG_RST_TSU,
		(uintptr_t)CPG_RSTMON_TSU,
		0x00010000,
		CPG_T_RST
	},
};

static CPG_REG_SETTING cpg_static_select_tbl[] = {
	{ (uintptr_t)CPG_PL3A_DDIV,             0x01000100 },
	{ (uintptr_t)CPG_PL3_SSEL,              0x01000000 },
};

static CPG_REG_SETTING cpg_dynamic_select_tbl[] = {
	{ (uintptr_t)CPG_PL4_DSEL,              0x00010001 },
	{ (uintptr_t)CPG_PL2SDHI_DSEL, 		0x00110022 },
};

#define CPG_SEL_PLL1_ON_OFF					(0)
#define CPG_SEL_PLL2_1_ON_OFF				(1)
#define CPG_SEL_PLL2_2_ON_OFF				(2)
#define CPG_SEL_PLL3_1_ON_OFF				(3)
#define CPG_SEL_PLL3_2_ON_OFF				(4)
#define CPG_SEL_PLL3_3_ON_OFF				(5)

static CPG_REG_SETTING cpg_sel_pll1_on_off[] = {
	{(uintptr_t)CPG_CLKON_CA55, 0x00010001 }
};

static CPG_REG_SETTING cpg_sel_pll2_1_on_off[] = {
	{(uintptr_t)CPG_CLKON_ADC, 0x00010001 },
	{(uintptr_t)CPG_CLKON_TSU, 0x00010001 },
	{(uintptr_t)CPG_CLKON_SDHI, 0x00770077 }
};

static CPG_REG_SETTING cpg_sel_pll2_2_on_off[] = {
	{(uintptr_t)CPG_CLKON_SDHI, 0x00770077 },
};

static CPG_REG_SETTING cpg_sel_pll3_1_on_off[] = {
	{(uintptr_t)CPG_CLKON_AXI_ACPU_BUS, 0x000F000F },
	{(uintptr_t)CPG_CLKON_AXI_COM_BUS, 0x00030003 },
	{(uintptr_t)CPG_CLKON_AXI_DEFAULT_SLV, 0x00010001 },
	{(uintptr_t)CPG_CLKON_AXI_MCPU_BUS, 0x01930193 },
	{(uintptr_t)CPG_CLKON_AXI_TZCDDR, 0x001F001F },
	{(uintptr_t)CPG_CLKON_CA55, 0x001E001E },
	{(uintptr_t)CPG_CLKON_CST, 0x07FD07FD },
	{(uintptr_t)CPG_CLKON_DAMC_REG, 0x00030003 },
	{(uintptr_t)CPG_CLKON_DDR, 0x00030003 },
	{(uintptr_t)CPG_CLKON_ETH, 0x00030003 },
	{(uintptr_t)CPG_CLKON_IA55, 0x00030003 },
	{(uintptr_t)CPG_CLKON_IM33, 0x00030003 },
	{(uintptr_t)CPG_CLKON_JAUTH, 0x00010001 },
	{(uintptr_t)CPG_CLKON_OTP, 0x00020002 },
	{(uintptr_t)CPG_CLKON_PERI_COM, 0x00030003 },
	{(uintptr_t)CPG_CLKON_PERI_CPU, 0x003F003F },
	{(uintptr_t)CPG_CLKON_PERI_DDR, 0x00010001 },
	{(uintptr_t)CPG_CLKON_REG0_BUS, 0x00010001 },
	{(uintptr_t)CPG_CLKON_REG1_BUS, 0x00030003 },
	{(uintptr_t)CPG_CLKON_ROM, 0x00010001 },
	{(uintptr_t)CPG_CLKON_SDHI, 0x00880088 },
	{(uintptr_t)CPG_CLKON_SRAM_ACPU, 0x00010001 },
	{(uintptr_t)CPG_CLKON_SRAM_MCPU, 0x00010001 },
	{(uintptr_t)CPG_CLKON_SYSC, 0x00020002 },
	{(uintptr_t)CPG_CLKON_TSIPG, 0x00030003 },
	{(uintptr_t)CPG_CLKON_USB, 0x000F000F }
};

static CPG_REG_SETTING cpg_sel_pll3_2_on_off[] = {
	{(uintptr_t)CPG_CLKON_SPI_MULTI, 0x00030003 },
	{(uintptr_t)CPG_CLKON_AXI_MCPU_BUS, 0x02080208 },
};

static CPG_REG_SETTING cpg_sel_pll3_3_on_off[] = {
	{(uintptr_t)CPG_CLKON_SPI_MULTI, 0x00030003 },
	{(uintptr_t)CPG_CLKON_AXI_MCPU_BUS, 0x02080208 },
};


static void cpg_ctrl_clkrst(CPG_SETUP_DATA const *array, uint32_t num)
{
	int i;
	uint32_t mask;
	uint32_t cmp;

	for (i = 0; i < num; i++, array++) {
		mmio_write_32(array->reg, array->val);

		mask = (array->val >> 16) & 0xFFFF;
		cmp = array->val & 0xFFFF;
		if (array->type == CPG_T_RST) {
			cmp = ~(cmp);
		}
#ifndef CONFIG_DEBUG_RZF_FPGA
		while ((mmio_read_32(array->mon) & mask) != (cmp & mask))
			;
#endif
	}
}

static void cpg_selector_on_off(uint32_t sel, uint8_t flag)
{
	uint32_t cnt;
	uint32_t tbl_num;
	CPG_REG_SETTING *ptr;

	switch (sel) {
	case CPG_SEL_PLL1_ON_OFF:
		tbl_num = ARRAY_SIZE(cpg_sel_pll1_on_off);
		ptr = &cpg_sel_pll1_on_off[0];
		break;
	case CPG_SEL_PLL2_1_ON_OFF:
		tbl_num = ARRAY_SIZE(cpg_sel_pll2_1_on_off);
		ptr = &cpg_sel_pll2_1_on_off[0];
		break;
	case CPG_SEL_PLL2_2_ON_OFF:
		tbl_num = ARRAY_SIZE(cpg_sel_pll2_2_on_off);
		ptr = &cpg_sel_pll2_2_on_off[0];
		break;
	case CPG_SEL_PLL3_1_ON_OFF:
		tbl_num = ARRAY_SIZE(cpg_sel_pll3_1_on_off);
		ptr = &cpg_sel_pll3_1_on_off[0];
		break;
	case CPG_SEL_PLL3_2_ON_OFF:
		tbl_num = ARRAY_SIZE(cpg_sel_pll3_2_on_off);
		ptr = &cpg_sel_pll3_2_on_off[0];
		break;
	case CPG_SEL_PLL3_3_ON_OFF:
	tbl_num = ARRAY_SIZE(cpg_sel_pll3_3_on_off);
	ptr = &cpg_sel_pll3_3_on_off[0];
		break;
	default:
		break;
	}

	for (cnt = 0; cnt < tbl_num; cnt++) {
		if (flag == CPG_ON) {
			mmio_write_32(ptr[cnt].reg, (mmio_read_32(ptr[cnt].reg) | ptr[cnt].val));
		} else {
			mmio_write_32(ptr[cnt].reg, (mmio_read_32(ptr[cnt].reg) | (ptr[cnt].val & 0xFFFF0000)));
		}
	}

}

static void cpg_pll_start_146(CPG_PLL_SETDATA_146 *pdata)
{
	mmio_write_32(pdata->clk1_dat.reg, pdata->clk1_dat.val);
	mmio_write_32(pdata->clk2_dat.reg, pdata->clk2_dat.val);
	mmio_write_32(pdata->stby_dat.reg, pdata->stby_dat.val);
}

/* It is assumed that the PLL has stopped by the time this function is executed. */
static void cpg_pll_setup(void)
{
#ifndef CONFIG_DEBUG_RZF_FPGA
	uint32_t val = 0;

	/* PLL4 startup */
	/* PLL4 standby mode transition confirmation */
	do {
		val = mmio_read_32(CPG_PLL4_MON);
	} while ((val & (PLL4_MON_PLL4_RESETB | PLL4_MON_PLL4_LOCK)) != 0);

	/* PLL6 startup */
	/* PLL6 standby mode transition confirmation */
	do {
		val = mmio_read_32(CPG_PLL6_MON);
	} while ((val & (PLL6_MON_PLL6_RESETB | PLL6_MON_PLL6_LOCK)) != 0);
#endif

	/* Set PLL4 to normal mode */
	cpg_pll_start_146(&cpg_pll4_setdata);
	/* Set PLL6 to normal mode */
	cpg_pll_start_146(&cpg_pll6_setdata);

#ifndef CONFIG_DEBUG_RZF_FPGA
	/* PLL4 normal mode transition confirmation */
	do {
		val = mmio_read_32(CPG_PLL4_MON);
	} while ((val & (PLL4_MON_PLL4_RESETB | PLL4_MON_PLL4_LOCK)) == 0);

	/* PLL6 normal mode transition confirmation */
	do {
		val = mmio_read_32(CPG_PLL6_MON);
	} while ((val & (PLL6_MON_PLL6_RESETB | PLL6_MON_PLL6_LOCK)) == 0);
#endif
}

static void cpg_div_sel_setup(CPG_REG_SETTING *tbl, uint32_t size)
{
	int cnt;

	for (cnt = 0; cnt < size; cnt++, tbl++) {
		mmio_write_32(tbl->reg, tbl->val);
	}

#ifndef CONFIG_DEBUG_RZF_FPGA
	/* Wait for completion of settings */
	while (mmio_read_32(CPG_CLKSTATUS) != 0)
		;
#endif
}

static void cpg_div_sel_static_setup(void)
{
	cpg_div_sel_setup(cpg_static_select_tbl, ARRAY_SIZE(cpg_static_select_tbl));
}

static void cpg_div_sel_dynamic_setup(void)
{
	cpg_div_sel_setup(cpg_dynamic_select_tbl, ARRAY_SIZE(cpg_dynamic_select_tbl));
}

static void cpg_clk_on_setup(void)
{
	cpg_ctrl_clkrst(&cpg_clk_on_tbl[0], ARRAY_SIZE(cpg_clk_on_tbl));
}

static void cpg_reset_setup(void)
{
	cpg_ctrl_clkrst(&cpg_reset_tbl[0], ARRAY_SIZE(cpg_reset_tbl));
}

void cpg_active_ddr(void (*disable_phy)(void))
{
	/* Assert the reset of DDRTOP */
	mmio_write_32(CPG_RST_DDR, 0x004F0000 | (CPG_RST_DDR_OPT_VALUE << 16));
	mmio_write_32(CPG_OTHERFUNC2_REG, 0x00010000);
#ifndef CONFIG_DEBUG_RZF_FPGA
	while ((mmio_read_32(CPG_RSTMON_DDR) & 0x0000004F) != 0x0000004F)
		;
#endif

	/* Start the clocks of DDRTOP */
	mmio_write_32(CPG_CLKON_DDR, 0x00030003);
#ifndef CONFIG_DEBUG_RZF_FPGA
	while ((mmio_read_32(CPG_CLKMON_DDR) & 0x00000003) != 0x00000003)
		;
#endif

	udelay(1);

	/* De-assert rst_n */
	mmio_write_32(CPG_OTHERFUNC2_REG, 0x00010001);

	udelay(1);

	/* De-assert PRESETN */
	mmio_write_32(CPG_RST_DDR, 0x00020002);
#ifndef CONFIG_DEBUG_RZF_FPGA
	while ((mmio_read_32(CPG_RSTMON_DDR) & 0x00000002) != 0x00000000)
		;
#endif

	udelay(1);

	disable_phy();

	/* De-assert axiY_ARESETn, regARESETn, reset_n */
	mmio_write_32(CPG_RST_DDR, 0x004D004D | (CPG_RST_DDR_OPT_VALUE << 16) | CPG_RST_DDR_OPT_VALUE);
#ifndef CONFIG_DEBUG_RZF_FPGA
	while ((mmio_read_32(CPG_RSTMON_DDR) & 0x0000004D) != 0x00000000)
		;
#endif

	udelay(1);
}

void cpg_reset_ddr_mc(void)
{
	/* Assert rst_n, axiY_ARESETn, regARESETn */
	mmio_write_32(CPG_RST_DDR, 0x004C0000 | (CPG_RST_DDR_OPT_VALUE << 16));
	mmio_write_32(CPG_OTHERFUNC2_REG, 0x00010000);
#ifndef CONFIG_DEBUG_RZF_FPGA
	while ((mmio_read_32(CPG_RSTMON_DDR) & 0x0000004C) != 0x0000004C)
		;
#endif

	udelay(1);

	/* De-assert rst_n */
	mmio_write_32(CPG_OTHERFUNC2_REG, 0x00010001);

	udelay(1);

	/* De-assert axiY_ARESETn, regARESETn */
	mmio_write_32(CPG_RST_DDR, 0x004C004C | (CPG_RST_DDR_OPT_VALUE << 16) | CPG_RST_DDR_OPT_VALUE);
#ifndef CONFIG_DEBUG_RZF_FPGA
	while ((mmio_read_32(CPG_RSTMON_DDR) & 0x0000004C) != 0x00000000)
		;
#endif

	udelay(1);
}

void cpu_cpg_setup(void)
{
	while ((mmio_read_32(CPG_CLKSTATUS) & CLKSTATUS_DIVPL1_STS) != 0x00000000)
		;
	mmio_write_32(CPG_PL1_DDIV, PL1_DDIV_DIVPL1_SET_WEN | PL1_DDIV_DIVPL1_SET_1_1);
	while ((mmio_read_32(CPG_CLKSTATUS) & CLKSTATUS_DIVPL1_STS) != 0x00000000)
		;
}

void cpg_wdtrst_sel_setup(void)
{
	uint32_t reg;
	reg = mmio_read_32(CPG_WDTRST_SEL);
	reg |= WDTRST_SEL_WDTRSTSEL0 | WDTRST_SEL_WDTRSTSEL0_WEN;
	mmio_write_32(CPG_WDTRST_SEL, reg);
}

void cpg_setup(void)
{
	cpg_selector_on_off(CPG_SEL_PLL3_3_ON_OFF, CPG_OFF);
	cpg_div_sel_static_setup();
	cpg_selector_on_off(CPG_SEL_PLL3_3_ON_OFF, CPG_ON);
	cpg_pll_setup();
	cpg_clk_on_setup();
	cpg_reset_setup();
	cpg_div_sel_dynamic_setup();
	cpg_wdtrst_sel_setup();
}
