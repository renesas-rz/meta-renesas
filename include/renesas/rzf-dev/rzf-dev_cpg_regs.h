// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 */

#ifndef __RZF_DEV_CPG_REGS_H__
#define __RZF_DEV_CPG_REGS_H__

#define	CPG_BASE					(0x11010000)		/* CPG base address */

#define CPG_PLL1_STBY				(CPG_BASE + 0x0000)	/* PLL1 (SSCG) standby control register */
#define CPG_PLL1_CLK1				(CPG_BASE + 0x0004)	/* PLL1 (SSCG) output clock setting register 1 */
#define CPG_PLL1_CLK2				(CPG_BASE + 0x0008)	/* PLL1 (SSCG) output clock setting register 2 */
#define CPG_PLL1_MON				(CPG_BASE + 0x000C)	/* PLL1 (SSCG) monitor register */
#define CPG_PLL4_STBY				(CPG_BASE + 0x0010)	/* PLL4 (SSCG) standby control register */
#define CPG_PLL4_CLK1				(CPG_BASE + 0x0014)	/* PLL4 (SSCG) output clock setting register 1 */
#define CPG_PLL4_CLK2				(CPG_BASE + 0x0018)	/* PLL4 (SSCG) output clock setting register 2 */
#define CPG_PLL4_MON				(CPG_BASE + 0x001C)	/* PLL4 (SSCG) monitor register */
#define CPG_PLL6_STBY				(CPG_BASE + 0x0020)	/* PLL6 (SSCG) standby control register */
#define CPG_PLL6_CLK1				(CPG_BASE + 0x0024)	/* PLL6 (SSCG) output clock setting register 1 */
#define CPG_PLL6_CLK2				(CPG_BASE + 0x0028)	/* PLL6 (SSCG) output clock setting register 2 */
#define CPG_PLL6_MON				(CPG_BASE + 0x002C)	/* PLL6 (SSCG) monitor register */
#define CPG_PLL1_SETTING			(CPG_BASE + 0x0040)	/* PLL1_SEL_SETTING */
#define CPG_OTPPLL0_MON				(CPG_BASE + 0x0044)	/* OTP_OTPPLL0 monitor register */
#define CPG_OTPPLL1_MON				(CPG_BASE + 0x0048)	/* OTP_OTPPLL1 monitor register */
#define CPG_OTPPLL2_MON				(CPG_BASE + 0x004C)	/* OTP_OTPPLL2 monitor register */

#define CPG_PLL2_STBY				(CPG_BASE + 0x0100)	/* PLL2 (SSCG) standby control register */
#define CPG_PLL2_CLK1				(CPG_BASE + 0x0104)	/* PLL2 (SSCG) output clock setting register 1 */
#define CPG_PLL2_CLK2				(CPG_BASE + 0x0108)	/* PLL2 (SSCG) output clock setting register 2 */
#define CPG_PLL2_CLK3				(CPG_BASE + 0x010C)	/* PLL2 (SSCG) output clock setting register 3 */
#define CPG_PLL2_CLK4				(CPG_BASE + 0x0110)	/* PLL2 (SSCG) output clock setting register 4 */
#define CPG_PLL2_CLK5				(CPG_BASE + 0x0114)	/* PLL2 (SSCG) output clock setting register 5 */
#define CPG_PLL2_CLK6				(CPG_BASE + 0x0118)	/* PLL2 (SSCG) output clock setting register 6 */
#define CPG_PLL2_MON				(CPG_BASE + 0x011C)	/* PLL2 (SSCG) monitor register */
#define CPG_PLL3_STBY				(CPG_BASE + 0x0120)	/* PLL3 (SSCG) standby control register */
#define CPG_PLL3_CLK1				(CPG_BASE + 0x0124)	/* PLL3 (SSCG) output clock setting register 1 */
#define CPG_PLL3_CLK2				(CPG_BASE + 0x0128)	/* PLL3 (SSCG) output clock setting register 2 */
#define CPG_PLL3_CLK3				(CPG_BASE + 0x012C)	/* PLL3 (SSCG) output clock setting register 3 */
#define CPG_PLL3_CLK4				(CPG_BASE + 0x0130)	/* PLL3 (SSCG) output clock setting register 4 */
#define CPG_PLL3_CLK5				(CPG_BASE + 0x0134)	/* PLL3 (SSCG) output clock setting register 5 */
#define CPG_PLL3_MON				(CPG_BASE + 0x013C)	/* PLL3 (SSCG) monitor register */
#define CPG_PLL5_STBY				(CPG_BASE + 0x0140)	/* PLL5 (SSCG) standby control register */
#define CPG_PLL5_CLK1				(CPG_BASE + 0x0144)	/* PLL5 (SSCG) output clock setting register 1 */
#define CPG_PLL5_CLK2				(CPG_BASE + 0x0148)	/* PLL5 (SSCG) output clock setting register 2 */
#define CPG_PLL5_CLK3				(CPG_BASE + 0x014C)	/* PLL5 (SSCG) output clock setting register 3 */
#define CPG_PLL5_CLK4				(CPG_BASE + 0x0150)	/* PLL5 (SSCG) output clock setting register 4 */
#define CPG_PLL5_CLK5				(CPG_BASE + 0x0154)	/* PLL5 (SSCG) output clock setting register 5 */
#define CPG_PLL5_MON				(CPG_BASE + 0x015C)	/* PLL5 (SSCG) monitor register */

#define CPG_PL1_DDIV				(CPG_BASE + 0x0200)	/* Division ratio setting register */
#define CPG_PL2_DDIV				(CPG_BASE + 0x0204)	/* Division ratio setting register */
#define CPG_PL3A_DDIV				(CPG_BASE + 0x0208)	/* Division ratio setting register */
#define CPG_PL3B_DDIV				(CPG_BASE + 0x020C)	/* Division ratio setting register */
#define CPG_PL6_DDIV				(CPG_BASE + 0x0210)	/* Division ratio setting register */

#define CPG_PL2SDHI_DSEL			(CPG_BASE + 0x0218)	/* Source clock setting register */
#define CPG_PL4_DSEL				(CPG_BASE + 0x021C)	/* Source clock setting register */
#define CPG_CLKSTATUS				(CPG_BASE + 0x0280)	/* CLK status register */

#define CPG_PL1_CA55_SSEL			(CPG_BASE + 0x0400)	/* Source clock setting register */
#define CPG_PL2_SSEL				(CPG_BASE + 0x0404)	/* Source clock setting register */
#define CPG_PL3_SSEL				(CPG_BASE + 0x0408)	/* Source clock setting register */
#define CPG_PL5_SSEL				(CPG_BASE + 0x0410)	/* Source clock setting register */
#define CPG_PL6_SSEL				(CPG_BASE + 0x0414)	/* Source clock setting register */
#define CPG_PL6_ETH_SSEL			(CPG_BASE + 0x0418)	/* Source clock setting register */
#define CPG_PL5_SDIV				(CPG_BASE + 0x0420)	/* Division ratio setting register */

#define CPG_CLKON_CA55				(CPG_BASE + 0x0500)	/* Clock ON / OFF register CA55 */
#define CPG_CLKON_CM33				(CPG_BASE + 0x0504)	/* Clock ON / OFF register CM33 */
#define CPG_CLKON_SRAM_ACPU			(CPG_BASE + 0x0508)	/* Clock ON / OFF register SRAM_ACPU */
#define CPG_CLKON_SRAM_MCPU			(CPG_BASE + 0x050C)	/* Clock ON / OFF register SRAM_MCPU */
#define CPG_CLKON_ROM				(CPG_BASE + 0x0510)	/* Clock ON / OFF register ROM */
#define CPG_CLKON_GIC600			(CPG_BASE + 0x0514)	/* Clock ON / OFF register GIC600 */
#define CPG_CLKON_IA55				(CPG_BASE + 0x0518)	/* Clock ON / OFF register IA55 */
#define CPG_CLKON_IM33				(CPG_BASE + 0x051C)	/* Clock ON / OFF register IM33 */
#define CPG_CLKON_MHU				(CPG_BASE + 0x0520)	/* Clock ON / OFF register MHU */
#define CPG_CLKON_CST				(CPG_BASE + 0x0524)	/* Clock ON / OFF register CST */
#define CPG_CLKON_SYC				(CPG_BASE + 0x0528)	/* Clock ON / OFF register SYC */
#define CPG_CLKON_DAMC_REG			(CPG_BASE + 0x052C)	/* Clock ON / OFF register DAMC_REG */
#define CPG_CLKON_SYSC				(CPG_BASE + 0x0530)	/* Clock ON / OFF register SYSC */
#define CPG_CLKON_OSTM				(CPG_BASE + 0x0534)	/* Clock ON / OFF register OSTM */
#define CPG_CLKON_MTU				(CPG_BASE + 0x0538)	/* Clock ON / OFF register MTU */
#define CPG_CLKON_POE3				(CPG_BASE + 0x053C)	/* Clock ON / OFF register POE3 */
#define CPG_CLKON_GPT				(CPG_BASE + 0x0540)	/* Clock ON / OFF register GPT */
#define CPG_CLKON_POEG				(CPG_BASE + 0x0544)	/* Clock ON / OFF register POEG */
#define CPG_CLKON_WDT				(CPG_BASE + 0x0548)	/* Clock ON / OFF register WDT */
#define CPG_CLKON_DDR				(CPG_BASE + 0x054C)	/* Clock ON / OFF register DDR */
#define CPG_CLKON_SPI_MULTI			(CPG_BASE + 0x0550)	/* Clock ON / OFF register SPI_MULTI */
#define CPG_CLKON_SDHI				(CPG_BASE + 0x0554)	/* Clock ON / OFF register SDHI */
#define CPG_CLKON_GPU				(CPG_BASE + 0x0558)	/* Clock ON / OFF register GPU */
#define CPG_CLKON_ISU				(CPG_BASE + 0x055C)	/* Clock ON / OFF register ISU */
#define CPG_CLKON_H264				(CPG_BASE + 0x0560)	/* Clock ON / OFF register H264 */
#define CPG_CLKON_CRU				(CPG_BASE + 0x0564)	/* Clock ON / OFF register CRU */
#define CPG_CLKON_MIPI_DSI			(CPG_BASE + 0x0568)	/* Clock ON / OFF register MIPI_DSI */
#define CPG_CLKON_LCDC				(CPG_BASE + 0x056C)	/* Clock ON / OFF register LCDC */
#define CPG_CLKON_SSI				(CPG_BASE + 0x0570)	/* Clock ON / OFF register SSI */
#define CPG_CLKON_SRC				(CPG_BASE + 0x0574)	/* Clock ON / OFF register SRC */
#define CPG_CLKON_USB				(CPG_BASE + 0x0578)	/* Clock ON / OFF register USB */
#define CPG_CLKON_ETH				(CPG_BASE + 0x057C)	/* Clock ON / OFF register ETH */
#define CPG_CLKON_I2C				(CPG_BASE + 0x0580)	/* Clock ON / OFF register I2C */
#define CPG_CLKON_SCIF				(CPG_BASE + 0x0584)	/* Clock ON / OFF register SCIF */
#define CPG_CLKON_SCI				(CPG_BASE + 0x0588)	/* Clock ON / OFF register SCI */
#define CPG_CLKON_IRDA				(CPG_BASE + 0x058C)	/* Clock ON / OFF register IRDA */
#define CPG_CLKON_RSPI				(CPG_BASE + 0x0590)	/* Clock ON / OFF register RSPI */
#define CPG_CLKON_CANFD				(CPG_BASE + 0x0594)	/* Clock ON / OFF register CANFD */
#define CPG_CLKON_GPIO				(CPG_BASE + 0x0598)	/* Clock ON / OFF register GPIO */
#define CPG_CLKON_TSIPG				(CPG_BASE + 0x059C)	/* Clock ON / OFF register TSIPG */
#define CPG_CLKON_JAUTH				(CPG_BASE + 0x05A0)	/* Clock ON / OFF register JAUTH */
#define CPG_CLKON_OTP				(CPG_BASE + 0x05A4)	/* Clock ON / OFF register OTP */
#define CPG_CLKON_ADC				(CPG_BASE + 0x05A8)	/* Clock ON / OFF register ADC */
#define CPG_CLKON_TSU				(CPG_BASE + 0x05AC)	/* Clock ON / OFF register TSU */
#define CPG_CLKON_BBGU				(CPG_BASE + 0x05B0)	/* Clock ON / OFF register BBGU */
#define CPG_CLKON_AXI_ACPU_BUS		(CPG_BASE + 0x05B4)	/* Clock ON / OFF register AXI_ACPU_BUS */
#define CPG_CLKON_AXI_MCPU_BUS		(CPG_BASE + 0x05B8)	/* Clock ON / OFF register AXI_MCPU_BUS */
#define CPG_CLKON_AXI_COM_BUS		(CPG_BASE + 0x05BC)	/* Clock ON / OFF register AXI_COM_BUS */
#define CPG_CLKON_AXI_VIDEO_BUS		(CPG_BASE + 0x05C0)	/* Clock ON / OFF register AXI_VIDEO_BUS */
#define CPG_CLKON_PERI_COM			(CPG_BASE + 0x05C4)	/* Clock ON / OFF register PERI_COM */
#define CPG_CLKON_REG1_BUS			(CPG_BASE + 0x05C8)	/* Clock ON / OFF register REG1_BUS */
#define CPG_CLKON_REG0_BUS			(CPG_BASE + 0x05CC)	/* Clock ON / OFF register REG0_BUS */
#define CPG_CLKON_PERI_CPU			(CPG_BASE + 0x05D0)	/* Clock ON / OFF register PERI_CPU */
#define CPG_CLKON_PERI_VIDEO		(CPG_BASE + 0x05D4)	/* Clock ON / OFF register PERI_VIDEO */
#define CPG_CLKON_PERI_DDR			(CPG_BASE + 0x05D8)	/* Clock ON / OFF register PERI_DDR */
#define CPG_CLKON_AXI_TZCDDR		(CPG_BASE + 0x05DC)	/* Clock ON / OFF register AXI_TZCDDR */
#define CPG_CLKON_MTGPGS			(CPG_BASE + 0x05E0)	/* Clock ON / OFF register MTGPGS */
#define CPG_CLKON_AXI_DEFAULT_SLV	(CPG_BASE + 0x05E4)	/* Clock ON / OFF register AXI_DEFAULT_SLV */

#define CPG_CLKMON_CA55				(CPG_BASE + 0x0680)	/* Clock monitor register CA55 */
#define CPG_CLKMON_CM33				(CPG_BASE + 0x0684)	/* Clock monitor register CM33 */
#define CPG_CLKMON_SRAM_ACPU		(CPG_BASE + 0x0688)	/* Clock monitor register SRAM_ACPU */
#define CPG_CLKMON_SRAM_MCPU		(CPG_BASE + 0x068C)	/* Clock monitor register SRAM_MCPU */
#define CPG_CLKMON_ROM				(CPG_BASE + 0x0690)	/* Clock monitor register ROM */
#define CPG_CLKMON_GIC600			(CPG_BASE + 0x0694)	/* Clock monitor register GIC600 */
#define CPG_CLKMON_IA55				(CPG_BASE + 0x0698)	/* Clock monitor register IA55 */
#define CPG_CLKMON_IM33				(CPG_BASE + 0x069C)	/* Clock monitor register IM33 */
#define CPG_CLKMON_MHU				(CPG_BASE + 0x06A0)	/* Clock monitor register MHU */
#define CPG_CLKMON_CST				(CPG_BASE + 0x06A4)	/* Clock monitor register CST */
#define CPG_CLKMON_SYC				(CPG_BASE + 0x06A8)	/* Clock monitor register SYC */
#define CPG_CLKMON_DAMC_REG			(CPG_BASE + 0x06AC)	/* Clock monitor register DAMC_REG */
#define CPG_CLKMON_SYSC				(CPG_BASE + 0x06B0)	/* Clock monitor register SYSC */
#define CPG_CLKMON_OSTM				(CPG_BASE + 0x06B4)	/* Clock monitor register OSTM */
#define CPG_CLKMON_MTU				(CPG_BASE + 0x06B8)	/* Clock monitor register MTU */
#define CPG_CLKMON_POE3				(CPG_BASE + 0x06BC)	/* Clock monitor register POE3 */
#define CPG_CLKMON_GPT				(CPG_BASE + 0x06C0)	/* Clock monitor register GPT */
#define CPG_CLKMON_POEG				(CPG_BASE + 0x06C4)	/* Clock monitor register POEG */
#define CPG_CLKMON_WDT				(CPG_BASE + 0x06C8)	/* Clock monitor register WDT */
#define CPG_CLKMON_DDR				(CPG_BASE + 0x06CC)	/* Clock monitor register DDR */
#define CPG_CLKMON_SPI_MULTI		(CPG_BASE + 0x06D0)	/* Clock monitor register SPI_MULTI */
#define CPG_CLKMON_SDHI				(CPG_BASE + 0x06D4)	/* Clock monitor register SDHI */
#define CPG_CLKMON_GPU				(CPG_BASE + 0x06D8)	/* Clock monitor register GPU */
#define CPG_CLKMON_ISU				(CPG_BASE + 0x06DC)	/* Clock monitor register ISU */
#define CPG_CLKMON_H264				(CPG_BASE + 0x06E0)	/* Clock monitor register H264 */
#define CPG_CLKMON_CRU				(CPG_BASE + 0x06E4)	/* Clock monitor register CRU */
#define CPG_CLKMON_MIPI_DSI			(CPG_BASE + 0x06E8)	/* Clock monitor register MIPI_DSI */
#define CPG_CLKMON_LCDC				(CPG_BASE + 0x06EC)	/* Clock monitor register LCDC */
#define CPG_CLKMON_SSI				(CPG_BASE + 0x06F0)	/* Clock monitor register SSI */
#define CPG_CLKMON_SRC				(CPG_BASE + 0x06F4)	/* Clock monitor register SRC */
#define CPG_CLKMON_USB				(CPG_BASE + 0x06F8)	/* Clock monitor register USB */
#define CPG_CLKMON_ETH				(CPG_BASE + 0x06FC)	/* Clock monitor register ETH */
#define CPG_CLKMON_I2C				(CPG_BASE + 0x0700)	/* Clock monitor register I2C */
#define CPG_CLKMON_SCIF				(CPG_BASE + 0x0704)	/* Clock monitor register SCIF */
#define CPG_CLKMON_SCI				(CPG_BASE + 0x0708)	/* Clock monitor register SCI */
#define CPG_CLKMON_IRDA				(CPG_BASE + 0x070C)	/* Clock monitor register IRDA */
#define CPG_CLKMON_RSPI				(CPG_BASE + 0x0710)	/* Clock monitor register RSPI */
#define CPG_CLKMON_CANFD			(CPG_BASE + 0x0714)	/* Clock monitor register CANFD */
#define CPG_CLKMON_GPIO				(CPG_BASE + 0x0718)	/* Clock monitor register GPIO */
#define CPG_CLKMON_TSIPG			(CPG_BASE + 0x071C)	/* Clock monitor register TSIPG */
#define CPG_CLKMON_JAUTH			(CPG_BASE + 0x0720)	/* Clock monitor register JAUTH */
#define CPG_CLKMON_OTP				(CPG_BASE + 0x0724)	/* Clock monitor register OTP */
#define CPG_CLKMON_ADC				(CPG_BASE + 0x0728)	/* Clock monitor register ADC */
#define CPG_CLKMON_TSU				(CPG_BASE + 0x072C)	/* Clock monitor register TSU */
#define CPG_CLKMON_BBGU				(CPG_BASE + 0x0730)	/* Clock monitor register BBGU */
#define CPG_CLKMON_AXI_ACPU_BUS		(CPG_BASE + 0x0734)	/* Clock monitor register AXI_ACPU_BUS */
#define CPG_CLKMON_AXI_MCPU_BUS		(CPG_BASE + 0x0738)	/* Clock monitor register AXI_MCPU_BUS */
#define CPG_CLKMON_AXI_COM_BUS		(CPG_BASE + 0x073C)	/* Clock monitor register AXI_COM_BUS */
#define CPG_CLKMON_AXI_VIDEO_BUS	(CPG_BASE + 0x0740)	/* Clock monitor register AXI_VIDEO_BUS */
#define CPG_CLKMON_PERI_COM			(CPG_BASE + 0x0744)	/* Clock monitor register PERI_COM */
#define CPG_CLKMON_REG1_BUS			(CPG_BASE + 0x0748)	/* Clock monitor register REG1_BUS */
#define CPG_CLKMON_REG0_BUS			(CPG_BASE + 0x074C)	/* Clock monitor register REG0_BUS */
#define CPG_CLKMON_PERI_CPU			(CPG_BASE + 0x0750)	/* Clock monitor register PERI_CPU */
#define CPG_CLKMON_PERI_VIDEO		(CPG_BASE + 0x0754)	/* Clock monitor register PERI_VIDEO */
#define CPG_CLKMON_PERI_DDR			(CPG_BASE + 0x0758)	/* Clock monitor register PERI_DDR */
#define CPG_CLKMON_AXI_TZCDDR		(CPG_BASE + 0x075C)	/* Clock monitor register AXI_TZCDDR */
#define CPG_CLKMON_MTGPGS			(CPG_BASE + 0x0760)	/* Clock monitor register MTGPGS */
#define CPG_CLKMON_AXI_DEFAULT_SLV	(CPG_BASE + 0x0764)	/* Clock monitor register AXI_DEFAULT_SLV */

#define CPG_RST_CA55				(CPG_BASE + 0x0800)	/* Reset ONOFF register CA55 */
#define CPG_RST_CM33				(CPG_BASE + 0x0804)	/* Reset ONOFF register CM33 */
#define CPG_RST_SRAM_ACPU			(CPG_BASE + 0x0808)	/* Reset ONOFF register SRAM_ACPU */
#define CPG_RST_SRAM_MCPU			(CPG_BASE + 0x080C)	/* Reset ONOFF register SRAM_MCPU */
#define CPG_RST_ROM					(CPG_BASE + 0x0810)	/* Reset ONOFF register ROM */
#define CPG_RST_GIC600				(CPG_BASE + 0x0814)	/* Reset ONOFF register GIC600 */
#define CPG_RST_IA55				(CPG_BASE + 0x0818)	/* Reset ONOFF register IA55 */
#define CPG_RST_IM33				(CPG_BASE + 0x081C)	/* Reset ONOFF register IM33 */
#define CPG_RST_MHU					(CPG_BASE + 0x0820)	/* Reset ONOFF register MHU */
#define CPG_RST_CST					(CPG_BASE + 0x0824)	/* Reset ONOFF register CST */
#define CPG_RST_SYC					(CPG_BASE + 0x0828)	/* Reset ONOFF register SYC */
#define CPG_RST_DMAC				(CPG_BASE + 0x082C)	/* Reset ONOFF register DMAC */
#define CPG_RST_SYSC				(CPG_BASE + 0x0830)	/* Reset ONOFF register SYSC */
#define CPG_RST_OSTM				(CPG_BASE + 0x0834)	/* Reset ONOFF register OSTM */
#define CPG_RST_MTU					(CPG_BASE + 0x0838)	/* Reset ONOFF register MTU */
#define CPG_RST_POE3				(CPG_BASE + 0x083C)	/* Reset ONOFF register POE3 */
#define CPG_RST_GPT					(CPG_BASE + 0x0840)	/* Reset ONOFF register GPT */
#define CPG_RST_POEG				(CPG_BASE + 0x0844)	/* Reset ONOFF register POEG */
#define CPG_RST_WDT					(CPG_BASE + 0x0848)	/* Reset ONOFF register WDT */
#define CPG_RST_DDR					(CPG_BASE + 0x084C)	/* Reset ONOFF register DDR */
#define CPG_RST_SPI					(CPG_BASE + 0x0850)	/* Reset ONOFF register SPI */
#define CPG_RST_SDHI				(CPG_BASE + 0x0854)	/* Reset ONOFF register SDHI */
#define CPG_RST_GPU					(CPG_BASE + 0x0858)	/* Reset ONOFF register GPU */
#define CPG_RST_ISU					(CPG_BASE + 0x085C)	/* Reset ONOFF register ISU */
#define CPG_RST_H264				(CPG_BASE + 0x0860)	/* Reset ONOFF register H264 */
#define CPG_RST_CRU					(CPG_BASE + 0x0864)	/* Reset ONOFF register CRU */
#define CPG_RST_MIPI_DSI			(CPG_BASE + 0x0868)	/* Reset ONOFF register MIPI_DSI */
#define CPG_RST_LCDC				(CPG_BASE + 0x086C)	/* Reset ONOFF register LCDC */
#define CPG_RST_SSIF				(CPG_BASE + 0x0870)	/* Reset ONOFF register SSIF */
#define CPG_RST_SRC					(CPG_BASE + 0x0874)	/* Reset ONOFF register SRC */
#define CPG_RST_USB					(CPG_BASE + 0x0878)	/* Reset ONOFF register USB */
#define CPG_RST_ETH					(CPG_BASE + 0x087C)	/* Reset ONOFF register ETH */
#define CPG_RST_I2C					(CPG_BASE + 0x0880)	/* Reset ONOFF register I2C */
#define CPG_RST_SCIF				(CPG_BASE + 0x0884)	/* Reset ONOFF register SCIF */
#define CPG_RST_SCI					(CPG_BASE + 0x0888)	/* Reset ONOFF register SCI */
#define CPG_RST_IRDA				(CPG_BASE + 0x088C)	/* Reset ONOFF register IRDA */
#define CPG_RST_RSPI				(CPG_BASE + 0x0890)	/* Reset ONOFF register RSPI */
#define CPG_RST_CANFD				(CPG_BASE + 0x0894)	/* Reset ONOFF register CANFD */
#define CPG_RST_GPIO				(CPG_BASE + 0x0898)	/* Reset ONOFF register GPIO */
#define CPG_RST_TSIPG				(CPG_BASE + 0x089C)	/* Reset ONOFF register TSIPG */
#define CPG_RST_JAUTH				(CPG_BASE + 0x08A0)	/* Reset ONOFF register JAUTH */
#define CPG_RST_OTP					(CPG_BASE + 0x08A4)	/* Reset ONOFF register OTP */
#define CPG_RST_ADC					(CPG_BASE + 0x08A8)	/* Reset ONOFF register ADC */
#define CPG_RST_TSU					(CPG_BASE + 0x08AC)	/* Reset ONOFF register TSU */
#define CPG_RST_BBGU				(CPG_BASE + 0x08B0)	/* Reset ONOFF register BBGU */
#define CPG_RST_AXI_ACPU_BUS		(CPG_BASE + 0x08B4)	/* Reset ONOFF register AXI_ACPU_BUS */
#define CPG_RST_AXI_MCPU_BUS		(CPG_BASE + 0x08B8)	/* Reset ONOFF register AXI_MCPU_BUS */
#define CPG_RST_AXI_COM_BUS			(CPG_BASE + 0x08BC)	/* Reset ONOFF register AXI_COM_BUS */
#define CPG_RST_AXI_VIDEO_BUS		(CPG_BASE + 0x08C0)	/* Reset ONOFF register AXI_VIDEO_BUS */
#define CPG_RST_PERI_COM			(CPG_BASE + 0x08C4)	/* Reset ONOFF register PERI_COM */
#define CPG_RST_REG1_BUS			(CPG_BASE + 0x08C8)	/* Reset ONOFF register REG1_BUS */
#define CPG_RST_REG0_BUS			(CPG_BASE + 0x08CC)	/* Reset ONOFF register REG0_BUS */
#define CPG_RST_PERI_CPU			(CPG_BASE + 0x08D0)	/* Reset ONOFF register PERI_CPU */
#define CPG_RST_PERI_VIDEO			(CPG_BASE + 0x08D4)	/* Reset ONOFF register PERI_VIDEO */
#define CPG_RST_PERI_DDR			(CPG_BASE + 0x08D8)	/* Reset ONOFF register PERI_DDR */
#define CPG_RST_AXI_TZCDDR			(CPG_BASE + 0x08DC)	/* Reset ONOFF register AXI_TZCDDR */
#define CPG_RST_MTGPGS				(CPG_BASE + 0x08E0)	/* Reset ONOFF register MTGPGS */
#define CPG_RST_AXI_DEFAULT_SLV		(CPG_BASE + 0x08E4)	/* Reset ONOFF register AXI_DEFAULT_SLV */

#define CPG_RSTMON_CA55				(CPG_BASE + 0x0980)	/* Reset monitor register CA55 */
#define CPG_RSTMON_CM33				(CPG_BASE + 0x0984)	/* Reset monitor register CM33 */
#define CPG_RSTMON_SRAM_ACPU		(CPG_BASE + 0x0988)	/* Reset monitor register SRAM_ACPU */
#define CPG_RSTMON_SRAM_MCPU		(CPG_BASE + 0x098C)	/* Reset monitor register SRAM_MCPU */
#define CPG_RSTMON_ROM				(CPG_BASE + 0x0990)	/* Reset monitor register ROM */
#define CPG_RSTMON_GIC600			(CPG_BASE + 0x0994)	/* Reset monitor register GIC600 */
#define CPG_RSTMON_IA55				(CPG_BASE + 0x0998)	/* Reset monitor register IA55 */
#define CPG_RSTMON_IM33				(CPG_BASE + 0x099C)	/* Reset monitor register IM33 */
#define CPG_RSTMON_MHU				(CPG_BASE + 0x09A0)	/* Reset monitor register MHU */
#define CPG_RSTMON_CST				(CPG_BASE + 0x09A4)	/* Reset monitor register CST */
#define CPG_RSTMON_SYC				(CPG_BASE + 0x09A8)	/* Reset monitor register SYC */
#define CPG_RSTMON_DMAC				(CPG_BASE + 0x09AC)	/* Reset monitor register DMAC */
#define CPG_RSTMON_SYSC				(CPG_BASE + 0x09B0)	/* Reset monitor register SYSC */
#define CPG_RSTMON_OSTM				(CPG_BASE + 0x09B4)	/* Reset monitor register OSTM */
#define CPG_RSTMON_MTU				(CPG_BASE + 0x09B8)	/* Reset monitor register MTU */
#define CPG_RSTMON_POE3				(CPG_BASE + 0x09BC)	/* Reset monitor register POE3 */
#define CPG_RSTMON_GPT				(CPG_BASE + 0x09C0)	/* Reset monitor register GPT */
#define CPG_RSTMON_POEG				(CPG_BASE + 0x09C4)	/* Reset monitor register POEG */
#define CPG_RSTMON_WDT				(CPG_BASE + 0x09C8)	/* Reset monitor register WDT */
#define CPG_RSTMON_DDR				(CPG_BASE + 0x09CC)	/* Reset monitor register DDR */
#define CPG_RSTMON_SPI				(CPG_BASE + 0x09D0)	/* Reset monitor register SPI */
#define CPG_RSTMON_SDHI				(CPG_BASE + 0x09D4)	/* Reset monitor register SDHI */
#define CPG_RSTMON_GPU				(CPG_BASE + 0x09D8)	/* Reset monitor register GPU */
#define CPG_RSTMON_ISU				(CPG_BASE + 0x09DC)	/* Reset monitor register ISU */
#define CPG_RSTMON_H264				(CPG_BASE + 0x09E0)	/* Reset monitor register H264 */
#define CPG_RSTMON_CRU				(CPG_BASE + 0x09E4)	/* Reset monitor register CRU */
#define CPG_RSTMON_MIPI_DSI			(CPG_BASE + 0x09E8)	/* Reset monitor register MIPI_DSI */
#define CPG_RSTMON_LCDC				(CPG_BASE + 0x09EC)	/* Reset monitor register LCDC */
#define CPG_RSTMON_SSIF				(CPG_BASE + 0x09F0)	/* Reset monitor register SSIF */
#define CPG_RSTMON_SRC				(CPG_BASE + 0x09F4)	/* Reset monitor register SRC */
#define CPG_RSTMON_USB				(CPG_BASE + 0x09F8)	/* Reset monitor register USB */
#define CPG_RSTMON_ETH				(CPG_BASE + 0x09FC)	/* Reset monitor register ETH */
#define CPG_RSTMON_I2C				(CPG_BASE + 0x0A00)	/* Reset monitor register I2C */
#define CPG_RSTMON_SCIF				(CPG_BASE + 0x0A04)	/* Reset monitor register SCIF */
#define CPG_RSTMON_SCI				(CPG_BASE + 0x0A08)	/* Reset monitor register SCI */
#define CPG_RSTMON_IRDA				(CPG_BASE + 0x0A0C)	/* Reset monitor register IRDA */
#define CPG_RSTMON_RSPI				(CPG_BASE + 0x0A10)	/* Reset monitor register RSPI */
#define CPG_RSTMON_CANFD			(CPG_BASE + 0x0A14)	/* Reset monitor register CANFD */
#define CPG_RSTMON_GPIO				(CPG_BASE + 0x0A18)	/* Reset monitor register GPIO */
#define CPG_RSTMON_TSIPG			(CPG_BASE + 0x0A1C)	/* Reset monitor register TSIPG */
#define CPG_RSTMON_JAUTH			(CPG_BASE + 0x0A20)	/* Reset monitor register JAUTH */
#define CPG_RSTMON_OTP				(CPG_BASE + 0x0A24)	/* Reset monitor register OTP */
#define CPG_RSTMON_ADC				(CPG_BASE + 0x0A28)	/* Reset monitor register ADC */
#define CPG_RSTMON_TSU				(CPG_BASE + 0x0A2C)	/* Reset monitor register TSU */
#define CPG_RSTMON_BBGU				(CPG_BASE + 0x0A30)	/* Reset monitor register BBGU */
#define CPG_RSTMON_AXI_ACPU_BUS		(CPG_BASE + 0x0A34)	/* Reset monitor register AXI_ACPU_BUS */
#define CPG_RSTMON_AXI_MCPU_BUS		(CPG_BASE + 0x0A38)	/* Reset monitor register AXI_MCPU_BUS */
#define CPG_RSTMON_AXI_COM_BUS		(CPG_BASE + 0x0A3C)	/* Reset monitor register AXI_COM_BUS */
#define CPG_RSTMON_AXI_VIDEO_BUS	(CPG_BASE + 0x0A40)	/* Reset monitor register AXI_VIDEO_BUS */
#define CPG_RSTMON_PERI_COM			(CPG_BASE + 0x0A44)	/* Reset monitor register PERI_COM */
#define CPG_RSTMON_REG1_BUS			(CPG_BASE + 0x0A48)	/* Reset monitor register REG1_BUS */
#define CPG_RSTMON_REG0_BUS			(CPG_BASE + 0x0A4C)	/* Reset monitor register REG0_BUS */
#define CPG_RSTMON_PERI_CPU			(CPG_BASE + 0x0A50)	/* Reset monitor register PERI_CPU */
#define CPG_RSTMON_PERI_VIDEO		(CPG_BASE + 0x0A54)	/* Reset monitor register PERI_VIDEO */
#define CPG_RSTMON_PERI_DDR			(CPG_BASE + 0x0A58)	/* Reset monitor register PERI_DDR */
#define CPG_RSTMON_AXI_TZCDDR		(CPG_BASE + 0x0A5C)	/* Reset monitor register AXI_TZCDDR */
#define CPG_RSTMON_MTGPGS			(CPG_BASE + 0x0A60)	/* Reset monitor register MTGPGS */
#define CPG_RSTMON_AXI_DEFAULT_SLV	(CPG_BASE + 0x0A64)	/* Reset monitor register AXI_DEFAULT_SLV */

#define CPG_EN_OSTM					(CPG_BASE + 0x0B00)	/* Enable ONOFF register_OSTM */
#define CPG_WDTOVF_RST				(CPG_BASE + 0x0B10)	/* WDT overflow system reset register */
#define CPG_WDTRST_SEL				(CPG_BASE + 0x0B14)	/* WDT reset selector register */
#define CPG_DBGRST					(CPG_BASE + 0x0B20)	/* Reset ONOFF register DBGRST */
#define CPG_CLUSTER_PCHMON			(CPG_BASE + 0x0B30)	/* CA55 Cluster Power Status Monitor Register */
#define CPG_CLUSTER_PCHCTL			(CPG_BASE + 0x0B34)	/* CA55 Cluster Power Status Control Register */
#define CPG_CORE0_PCHMON			(CPG_BASE + 0x0B38)	/* CA55 Core0 Power Status Monitor Register */
#define CPG_CORE0_PCHCTL			(CPG_BASE + 0x0B3C)	/* CA55 Core0 Power Status Control Register */
#define CPG_CORE1_PCHMON			(CPG_BASE + 0x0B40)	/* CA55 Core1 Power Status Monitor Register */
#define CPG_CORE1_PCHCTL			(CPG_BASE + 0x0B44)	/* CA55 Core1 Power Status Control Register */
#define CPG_BUS_ACPU_MSTOP			(CPG_BASE + 0x0B60)	/* MSTOP registerBUS_ACPU */
#define CPG_BUS_MCPU1_MSTOP			(CPG_BASE + 0x0B64)	/* MSTOP registerBUS_MCPU1 */
#define CPG_BUS_MCPU2_MSTOP			(CPG_BASE + 0x0B68)	/* MSTOP registerBUS_MCPU2 */
#define CPG_BUS_PERI_COM_MSTOP		(CPG_BASE + 0x0B6C)	/* MSTOP registerBUS_PERI_COM */
#define CPG_BUS_PERI_CPU_MSTOP		(CPG_BASE + 0x0B70)	/* MSTOP registerBUS_PERI_CPU */
#define CPG_BUS_PERI_DDR_MSTOP		(CPG_BASE + 0x0B74)	/* MSTOP registerBUS_PERI_DDR */
#define CPG_BUS_PERI_VIDEO_MSTOP	(CPG_BASE + 0x0B78)	/* MSTOP registerBUS_PERI_VIDEO */
#define CPG_BUS_REG0_MSTOP			(CPG_BASE + 0x0B7C)	/* MSTOP registerBUS_REG0 */
#define CPG_BUS_REG1_MSTOP			(CPG_BASE + 0x0B80)	/* MSTOP registerBUS_REG1 */
#define CPG_BUS_TZCDDR_MSTOP		(CPG_BASE + 0x0B84)	/* MSTOP registerBUS_TZCDDR */
#define CPG_MHU_MSTOP				(CPG_BASE + 0x0B88)	/* MSTOP registerMHU */
#define CPG_BUS_PERI_STP_MSTOP		(CPG_BASE + 0x0B8C)	/* MSTOP registerBUS_PERI_STP */

#define CPG_OTHERFUNC1_REG			(CPG_BASE + 0x0BE8)	/* Other function registers1 */
#define CPG_OTHERFUNC2_REG			(CPG_BASE + 0x0BEC)	/* Other function registers2 */

#define PLL1_STBY_RESETB							(1 << 0)
#define PLL1_STBY_SSC_EN							(1 << 2)
#define PLL1_STBY_SSC_MODE0							(1 << 4)
#define PLL1_STBY_SSC_MODE1							(1 << 5)
#define PLL1_STBY_RESETB_WEN						(1 << 16)
#define PLL1_STBY_SSC_EN_WEN						(1 << 18)
#define PLL1_STBY_SSC_MODE_WEN						(1 << 20)
#define PLL1_CLK1_DIV_P_24M							(1 << 0)
#define PLL1_CLK1_DIV_P_12M							(2 << 0)
#define PLL1_CLK1_DIV_P_8M							(3 << 0)
#define PLL1_CLK1_DIV_P_6M							(4 << 0)
#define PLL1_CLK2_DIV_S_RATIO1						(0 << 0)
#define PLL1_CLK2_DIV_S_RATIO2						(1 << 0)
#define PLL1_CLK2_DIV_S_RATIO4						(2 << 0)
#define PLL1_CLK2_DIV_S_RATIO8						(3 << 0)
#define PLL1_CLK2_DIV_S_RATIO16						(4 << 0)
#define PLL1_CLK2_DIV_S_RATIO32						(5 << 0)
#define PLL1_CLK2_DIV_S_RATIO64						(6 << 0)
#define PLL1_MON_PLL1_RESETB						(1 << 0)
#define PLL1_MON_PLL1_LOCK							(1 << 4)
#define PLL4_STBY_RESETB							(1 << 0)
#define PLL4_STBY_SSC_EN							(1 << 2)
#define PLL4_STBY_SSC_MODE0							(1 << 4)
#define PLL4_STBY_SSC_MODE1							(1 << 5)
#define PLL4_STBY_RESETB_WEN						(1 << 16)
#define PLL4_STBY_SSC_EN_WEN						(1 << 18)
#define PLL4_STBY_SSC_MODE_WEN						(1 << 20)
#define PLL4_CLK1_DIV_P_24M							(1 << 0)
#define PLL4_CLK1_DIV_P_12M							(2 << 0)
#define PLL4_CLK1_DIV_P_8M							(3 << 0)
#define PLL4_CLK1_DIV_P_6M							(4 << 0)
#define PLL4_CLK2_DIV_S_RATIO1						(0 << 0)
#define PLL4_CLK2_DIV_S_RATIO2						(1 << 0)
#define PLL4_CLK2_DIV_S_RATIO4						(2 << 0)
#define PLL4_CLK2_DIV_S_RATIO8						(3 << 0)
#define PLL4_CLK2_DIV_S_RATIO16						(4 << 0)
#define PLL4_CLK2_DIV_S_RATIO32						(5 << 0)
#define PLL4_CLK2_DIV_S_RATIO64						(6 << 0)
#define PLL4_MON_PLL4_RESETB						(1 << 0)
#define PLL4_MON_PLL4_LOCK							(1 << 4)
#define PLL6_STBY_RESETB							(1 << 0)
#define PLL6_STBY_SSC_EN							(1 << 2)
#define PLL6_STBY_SSC_MODE0							(1 << 4)
#define PLL6_STBY_SSC_MODE1							(1 << 5)
#define PLL6_STBY_RESETB_WEN						(1 << 16)
#define PLL6_STBY_SSC_EN_WEN						(1 << 18)
#define PLL6_STBY_SSC_MODE_WEN						(1 << 20)
#define PLL6_CLK1_DIV_P_24M							(1 << 0)
#define PLL6_CLK1_DIV_P_12M							(2 << 0)
#define PLL6_CLK1_DIV_P_8M							(3 << 0)
#define PLL6_CLK1_DIV_P_6M							(4 << 0)
#define PLL6_CLK2_DIV_S_RATIO1						(0 << 0)
#define PLL6_CLK2_DIV_S_RATIO2						(1 << 0)
#define PLL6_CLK2_DIV_S_RATIO4						(2 << 0)
#define PLL6_CLK2_DIV_S_RATIO8						(3 << 0)
#define PLL6_CLK2_DIV_S_RATIO16						(4 << 0)
#define PLL6_CLK2_DIV_S_RATIO32						(5 << 0)
#define PLL6_CLK2_DIV_S_RATIO64						(6 << 0)
#define PLL6_MON_PLL6_RESETB						(1 << 0)
#define PLL6_MON_PLL6_LOCK							(1 << 4)
#define PLL1_SETTING_SEL_PLL1						(1 << 0)
#define PLL1_SETTING_SEL_PLL1_WEN					(1 << 16)
#define PLL_CLK_DIV_M_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 6))))
#define PLL_CLK_DIV_K_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 16))))
#define PLL_CLK_MRR_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 8))))
#define PLL_CLK_MFR_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 16))))

#define PLL2_STBY_RESETB							(1 << 0)
#define PLL2_STBY_SSC_EN							(1 << 2)
#define PLL2_STBY_DOWNSPREAD						(1 << 4)
#define PLL2_STBY_RESETB_WEN						(1 << 16)
#define PLL2_STBY_SSC_EN_WEN						(1 << 18)
#define PLL2_STBY_DOWNSPREAD_WEN					(1 << 20)
#define PLL2_CLK1_POSTDIV1_WEN						(1 << 16)
#define PLL2_CLK1_POSTDIV2_WEN						(1 << 20)
#define PLL2_CLK1_REFDIV_WEN						(1 << 24)
#define PLL2_CLK2_DACPD								(1 << 0)
#define PLL2_CLK2_DSMPD								(1 << 2)
#define PLL2_CLK2_FOUT4PHASEPD						(1 << 4)
#define PLL2_CLK2_FOUTPOSTDIVPD						(1 << 6)
#define PLL2_CLK2_FOUTVCOPD							(1 << 8)
#define PLL2_CLK2_DACPD_WEN							(1 << 16)
#define PLL2_CLK2_DSMPD_WEN							(1 << 18)
#define PLL2_CLK2_FOUT4PHASEPD_WEN					(1 << 20)
#define PLL2_CLK2_FOUTPOSTDIVPD_WEN					(1 << 22)
#define PLL2_CLK2_FOUTVCOPD_WEN						(1 << 24)
#define PLL2_CLK6_SEL_EXTWAVE						(1 << 0)
#define PLL2_CLK6_SEL_EXTWAVE_WEN					(1 << 16)
#define PLL2_MON_PLL2_RESETB						(1 << 0)
#define PLL2_MON_PLL2_LOCK							(1 << 4)
#define PLL3_STBY_RESETB							(1 << 0)
#define PLL3_STBY_SSC_EN							(1 << 2)
#define PLL3_STBY_DOWNSPREAD						(1 << 4)
#define PLL3_STBY_RESETB_WEN						(1 << 16)
#define PLL3_STBY_SSC_EN_WEN						(1 << 18)
#define PLL3_STBY_DOWNSPREAD_WEN					(1 << 20)
#define PLL3_CLK1_POSTDIV1_WEN						(1 << 16)
#define PLL3_CLK1_POSTDIV2_WEN						(1 << 20)
#define PLL3_CLK1_REFDIV_WEN						(1 << 24)
#define PLL3_CLK2_DACPD								(1 << 0)
#define PLL3_CLK2_DSMPD								(1 << 2)
#define PLL3_CLK2_FOUT4PHASEPD						(1 << 4)
#define PLL3_CLK2_FOUTPOSTDIVPD						(1 << 6)
#define PLL3_CLK2_FOUTVCOPD							(1 << 8)
#define PLL3_CLK2_DACPD_WEN							(1 << 16)
#define PLL3_CLK2_DSMPD_WEN							(1 << 18)
#define PLL3_CLK2_FOUT4PHASEPD_WEN					(1 << 20)
#define PLL3_CLK2_FOUTPOSTDIVPD_WEN					(1 << 22)
#define PLL3_CLK2_FOUTVCOPD_WEN						(1 << 24)
#define PLL3_CLK6_SEL_EXTWAVE						(1 << 0)
#define PLL3_CLK6_SEL_EXTWAVE_WEN					(1 << 16)
#define PLL3_MON_PLL3_RESETB						(1 << 0)
#define PLL3_MON_PLL3_LOCK							(1 << 4)
#define PLL5_STBY_RESETB							(1 << 0)
#define PLL5_STBY_SSC_EN							(1 << 2)
#define PLL5_STBY_DOWNSPREAD						(1 << 4)
#define PLL5_STBY_RESETB_WEN						(1 << 16)
#define PLL5_STBY_SSC_EN_WEN						(1 << 18)
#define PLL5_STBY_DOWNSPREAD_WEN					(1 << 20)
#define PLL5_CLK1_POSTDIV1_WEN						(1 << 16)
#define PLL5_CLK1_POSTDIV2_WEN						(1 << 20)
#define PLL5_CLK1_REFDIV_WEN						(1 << 24)
#define PLL5_CLK2_DACPD								(1 << 0)
#define PLL5_CLK2_DSMPD								(1 << 2)
#define PLL5_CLK2_FOUT4PHASEPD						(1 << 4)
#define PLL5_CLK2_FOUTPOSTDIVPD						(1 << 6)
#define PLL5_CLK2_FOUTVCOPD							(1 << 8)
#define PLL5_CLK2_DACPD_WEN							(1 << 16)
#define PLL5_CLK2_DSMPD_WEN							(1 << 18)
#define PLL5_CLK2_FOUT4PHASEPD_WEN					(1 << 20)
#define PLL5_CLK2_FOUTPOSTDIVPD_WEN					(1 << 22)
#define PLL5_CLK2_FOUTVCOPD_WEN						(1 << 24)
#define PLL5_CLK6_SEL_EXTWAVE						(1 << 0)
#define PLL5_CLK6_SEL_EXTWAVE_WEN					(1 << 16)
#define PLL5_MON_PLL5_RESETB						(1 << 0)
#define PLL5_MON_PLL5_LOCK							(1 << 4)

#define PLL_CLK_POSTDIV1_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 0))))
#define PLL_CLK_POSTDIV2_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 4))))
#define PLL_CLK_REFDIV_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 8))))
#define PLL_CLK_DIVVAL_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 0))))
#define PLL_CLK_FRACIN_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 8))))
#define PLL_CLK_EXT_MAXADDR_SET(a, b)	(mmio_write_32(a, ((mmio_read_32(a)) | (b << 0))))
#define PLL_CLK_INITIN_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 16))))
#define PLL_CLK_SPREAD_SET(a, b)		(mmio_write_32(a, ((mmio_read_32(a)) | (b << 0))))

#define PL1_DDIV_DIVPL1_SET_1_1						(0 << 0)
#define PL1_DDIV_DIVPL1_SET_1_2						(1 << 0)
#define PL1_DDIV_DIVPL1_SET_1_4						(2 << 0)
#define PL1_DDIV_DIVPL1_SET_1_8						(3 << 0)
#define PL1_DDIV_DIVPL1_SET_WEN						(1 << 16)
#define PL2_DDIV_DIVPL2A_SET_1_1					(0 << 0)
#define PL2_DDIV_DIVPL2A_SET_1_2					(1 << 0)
#define PL2_DDIV_DIVPL2A_SET_1_4					(2 << 0)
#define PL2_DDIV_DIVPL2A_SET_1_8					(3 << 0)
#define PL2_DDIV_DIVPL2A_SET_1_32					(4 << 0)
#define PL2_DDIV_DIVPL2B_SET_1_1					(0 << 4)
#define PL2_DDIV_DIVPL2B_SET_1_2					(1 << 4)
#define PL2_DDIV_DIVPL2B_SET_1_4					(2 << 4)
#define PL2_DDIV_DIVPL2B_SET_1_8					(3 << 4)
#define PL2_DDIV_DIVPL2B_SET_1_32					(4 << 4)
#define PL2_DDIV_DIVPL2C_SET_1_1					(0 << 4)
#define PL2_DDIV_DIVPL2C_SET_1_2					(1 << 4)
#define PL2_DDIV_DIVPL2C_SET_1_4					(2 << 4)
#define PL2_DDIV_DIVPL2C_SET_1_8					(3 << 4)
#define PL2_DDIV_DIVPL2C_SET_1_32					(4 << 4)
#define PL2_DDIV_DIVDSILPCLK_SET_1_16				(0 << 12)
#define PL2_DDIV_DIVDSILPCLK_SET_1_32				(1 << 12)
#define PL2_DDIV_DIVDSILPCLK_SET_1_64				(2 << 12)
#define PL2_DDIV_DIVDSILPCLK_SET_1_128				(3 << 12)
#define PL2_DDIV_DIVPL2A_WEN						(1 << 16)
#define PL2_DDIV_DIVPL2B_WEN						(1 << 20)
#define PL2_DDIV_DIVPL2C_WEN						(1 << 24)
#define PL2_DDIV_DIVDSILPCLK_WEN					(1 << 28)
#define PL3A_DDIV_DIVPL3A_SET_1_1					(0 << 0)
#define PL3A_DDIV_DIVPL3A_SET_1_2					(1 << 0)
#define PL3A_DDIV_DIVPL3A_SET_1_4					(2 << 0)
#define PL3A_DDIV_DIVPL3A_SET_1_8					(3 << 0)
#define PL3A_DDIV_DIVPL3A_SET_1_32					(4 << 0)
#define PL3A_DDIV_DIVPL3B_SET_1_1					(0 << 0)
#define PL3A_DDIV_DIVPL3B_SET_1_2					(1 << 0)
#define PL3A_DDIV_DIVPL3B_SET_1_4					(2 << 0)
#define PL3A_DDIV_DIVPL3B_SET_1_8					(3 << 0)
#define PL3A_DDIV_DIVPL3B_SET_1_32					(4 << 0)
#define PL3A_DDIV_DIVPL3C_SET_1_1					(0 << 0)
#define PL3A_DDIV_DIVPL3C_SET_1_2					(1 << 0)
#define PL3A_DDIV_DIVPL3C_SET_1_4					(2 << 0)
#define PL3A_DDIV_DIVPL3C_SET_1_8					(3 << 0)
#define PL3A_DDIV_DIVPL3C_SET_1_32					(4 << 0)
#define PL3A_DDIV_DIVPL3A_WEN						(1 << 16)
#define PL3A_DDIV_DIVPL3B_WEN						(1 << 20)
#define PL3A_DDIV_DIVPL3C_WEN						(1 << 24)
#define PL3B_DDIV_DIVPL3CLK200FIX_SET_1_1			(0 << 0)
#define PL3B_DDIV_DIVPL3CLK200FIX_SET_1_2			(1 << 0)
#define PL3B_DDIV_DIVPL3CLK200FIX_SET_1_4			(2 << 0)
#define PL3B_DDIV_DIVPL3CLK200FIX_SET_1_8			(3 << 0)
#define PL3B_DDIV_DIVPL3CLK200FIX_SET_1_32			(4 << 0)
#define PL3B_DDIV_DIVPL3CLK200FIX_WEN				(1 << 16)
#define PL6_DDIV_DIVGPU_SET_1_1						(0 << 0)
#define PL6_DDIV_DIVGPU_SET_1_2						(1 << 0)
#define PL6_DDIV_DIVGPU_SET_1_4						(2 << 0)
#define PL6_DDIV_DIVGPU_SET_1_8						(3 << 0)
#define PL6_DDIV_DIVGPU_WEN							(1 << 16)
#define PL2SDHI_DSEL_SEL_SDHI0_SET_CLK533FIX_C		(1 << 0)
#define PL2SDHI_DSEL_SEL_SDHI0_SET_DIV_PLL2_DIV8	(2 << 0)
#define PL2SDHI_DSEL_SEL_SDHI0_SET_DIV_PLL2_DIV12	(3 << 0)
#define PL2SDHI_DSEL_SEL_SDHI1_SET_CLK533FIX_C		(1 << 4)
#define PL2SDHI_DSEL_SEL_SDHI1_SET_DIV_PLL2_DIV8	(2 << 4)
#define PL2SDHI_DSEL_SEL_SDHI1_SET_DIV_PLL2_DIV12	(3 << 4)
#define PL2SDHI_DSEL_SEL_SDHI0_WEN					(1 << 16)
#define PL2SDHI_DSEL_SEL_SDHI1_WEN					(1 << 20)
#define PL4_DSEL_SEL_PLL4_SET						(1 << 0)
#define PL4_DSEL_SEL_PLL4_WEN						(1 << 16)
#define CLKSTATUS_DIVPL1_STS						(1 << 0)
#define CLKSTATUS_DIVPL2A_STS						(1 << 4)
#define CLKSTATUS_DIVPL2B_STS						(1 << 5)
#define CLKSTATUS_DIVPL2C_STS						(1 << 6)
#define CLKSTATUS_DIVDSILPCLK_STS					(1 << 7)
#define CLKSTATUS_DIVPL3A_STS						(1 << 8)
#define CLKSTATUS_DIVPL3B_STS						(1 << 9)
#define CLKSTATUS_DIVPL3C_STS						(1 << 10)
#define CLKSTATUS_DIVPL3CLK200FIX_STS				(1 << 11)
#define CLKSTATUS_DIVGPU_STS						(1 << 20)
#define CLKSTATUS_SELSDHI0_STS						(1 << 28)
#define CLKSTATUS_SELSDHI1_STS						(1 << 29)
#define CLKSTATUS_SELPLL4_STS						(1 << 31)
#define PL1_CA55_SSEL_SEL_PLL1_SET					(1 << 0)
#define PL1_CA55_SSEL_SEL_PLL1_WEN					(1 << 16)
#define PL2_SSEL_SEL_PLL2_1_SET						(1 << 0)
#define PL2_SSEL_SEL_PLL2_2_SET						(1 << 4)
#define PL2_SSEL_SEL_PLL2_1_WEN						(1 << 16)
#define PL2_SSEL_SEL_PLL2_2_WEN						(1 << 20)
#define PL3_SSEL_SEL_PLL3_1_SET						(1 << 0)
#define PL3_SSEL_SEL_PLL3_2_SET						(1 << 4)
#define PL3_SSEL_SEL_PLL3_3_SET						(1 << 8)
#define PL3_SSEL_SEL_PLL3_1_WEN						(1 << 16)
#define PL3_SSEL_SEL_PLL3_2_WEN						(1 << 20)
#define PL3_SSEL_SEL_PLL3_3_WEN						(1 << 24)
#define PL5_SSEL_SEL_PLL5_1_SET						(1 << 0)
#define PL5_SSEL_SEL_PLL5_2_SET						(1 << 4)
#define PL5_SSEL_SEL_PLL5_1_WEN						(1 << 16)
#define PL5_SSEL_SEL_PLL5_2_WEN						(1 << 20)
#define PL6_SSEL_SEL_PLL6_1_SET						(1 << 0)
#define PL6_SSEL_SEL_GPU1_1_SET						(1 << 4)
#define PL6_SSEL_SEL_GPU1_2_SET						(1 << 8)
#define PL6_SSEL_SEL_GPU2_SET						(1 << 12)
#define PL6_SSEL_SEL_PLL6_1_WEN						(1 << 16)
#define PL6_SSEL_SEL_GPU1_1_WEN						(1 << 20)
#define PL6_SSEL_SEL_GPU1_2_WEN						(1 << 24)
#define PL6_SSEL_SEL_GPU2_WEN						(1 << 28)
#define PL6_ETH_SSEL_SEL_PLL6_2_SET					(1 << 0)
#define PL6_ETH_SSEL_SEL_ETH_SET					(1 << 4)
#define PL6_ETH_SSEL_SEL_PLL6_2_WEN					(1 << 16)
#define PL6_ETH_SSEL_SEL_ETH_WEN					(1 << 20)
#define PL5_SDIV_DIVDSIA_SET_1_1					(0 << 0)
#define PL5_SDIV_DIVDSIA_SET_1_2					(1 << 0)
#define PL5_SDIV_DIVDSIA_SET_1_4					(2 << 0)
#define PL5_SDIV_DIVDSIA_SET_1_8					(3 << 0)
#define PL5_SDIV_DIVDSIB_SET_1_1					(0 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_2					(1 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_3					(2 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_4					(3 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_5					(4 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_6					(5 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_7					(6 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_8					(7 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_9					(8 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_10					(9 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_11					(10 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_12					(11 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_13					(12 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_14					(13 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_15					(14 << 8)
#define PL5_SDIV_DIVDSIB_SET_1_16					(15 << 8)
#define PL5_SDIV_DIVDSA_WEN							(1 << 16)
#define PL5_SDIV_DIVSDIB_WEN						(1 << 24)
#define CLKON_CLK0_ON								(1 << 0)
#define CLKON_CLK0_ON_WEN							(1 << 16)
#define CLKMON_UNIT0_CLK_MON						(1 << 0)
#define RST_UNIT0_RSTB								(1 << 0)
#define RST_UNIT0_RST_WEN							(1 << 16)
#define RSTMON_UNIT0_RST_MON						(1 << 0)
#define EN_OSTM_EN0_ON								(1 << 0)
#define EN_OSTM_EN1_ON								(1 << 1)
#define EN_OSTM_EN2_ON								(1 << 2)
#define EN_OSTM_EN0_WEN								(1 << 16)
#define EN_OSTM_EN1_WEN								(1 << 17)
#define EN_OSTM_EN2_WEN								(1 << 18)
#define WDTOVF_RST_WDTOVF0							(1 << 0)
#define WDTOVF_RST_WDTOVF1							(1 << 1)
#define WDTOVF_RST_WDTOVF2							(1 << 2)
#define WDTOVF_RST_WDTOVF3							(1 << 3)
#define WDTOVF_RST_WDTOVF0_WEN						(1 << 16)
#define WDTOVF_RST_WDTOVF1_WEN						(1 << 17)
#define WDTOVF_RST_WDTOVF2_WEN						(1 << 18)
#define WDTOVF_RST_WDTOVF3_WEN						(1 << 19)
#define WDTRST_SEL_WDTRSTSEL0						(1 << 0)
#define WDTRST_SEL_WDTRSTSEL1						(1 << 1)
#define WDTRST_SEL_WDTRSTSEL2						(1 << 2)
#define WDTRST_SEL_WDTRSTSEL3						(1 << 3)
#define WDTRST_SEL_WDTRSTSEL4						(1 << 4)
#define WDTRST_SEL_WDTRSTSEL5						(1 << 5)
#define WDTRST_SEL_WDTRSTSEL6						(1 << 6)
#define WDTRST_SEL_WDTRSTSEL7						(1 << 7)
#define WDTRST_SEL_WDTRSTSEL8						(1 << 8)
#define WDTRST_SEL_WDTRSTSEL9						(1 << 9)
#define WDTRST_SEL_WDTRSTSEL10						(1 << 10)
#define WDTRST_SEL_WDTRSTSEL0_WEN					(1 << 16)
#define WDTRST_SEL_WDTRSTSEL1_WEN					(1 << 17)
#define WDTRST_SEL_WDTRSTSEL2_WEN					(1 << 18)
#define WDTRST_SEL_WDTRSTSEL3_WEN					(1 << 19)
#define WDTRST_SEL_WDTRSTSEL4_WEN					(1 << 20)
#define WDTRST_SEL_WDTRSTSEL5_WEN					(1 << 21)
#define WDTRST_SEL_WDTRSTSEL6_WEN					(1 << 22)
#define WDTRST_SEL_WDTRSTSEL7_WEN					(1 << 23)
#define WDTRST_SEL_WDTRSTSEL8_WEN					(1 << 24)
#define WDTRST_SEL_WDTRSTSEL9_WEN					(1 << 25)
#define WDTRST_SEL_WDTRSTSEL10_WEN					(1 << 26)
#define DBGRST_UNIT0_RSTB							(1 << 0)
#define DBGRST_UNIT0_RST_WEN						(1 << 16)
#define CLUSTER_PCHMON_PACCEPT_MON					(1 << 0)
#define CLUSTER_PCHMON_PDENY_MON					(1 << 1)
#define CLUSTER_PCHCTL_PREQ_SET						(1 << 0)
#define CLUSTER_PCHCTL_PSTATE0_SET_ON				(0x48 << 16)
#define CLUSTER_PCHCTL_PSTATE0_SET_OFF				(0x00 << 16)
#define CORE0_PCHMON_PACCEPT0_MON					(1 << 0)
#define CORE0_PCHMON_PDENY0_MON						(1 << 1)
#define CORE0_PCHCTL_PREQ0_SET						(1 << 0)
#define CORE0_PCHCTL_PSTATE0_SET_ON					(0x08 << 16)
#define CORE0_PCHCTL_PSTATE0_SET_OFF_EMULATED		(0x01 << 16)
#define CORE0_PCHCTL_PSTATE0_SET_OFF				(0x00 << 16)
#define CORE1_PCHMON_PACCEPT1_MON					(1 << 0)
#define CORE1_PCHMON_PDENY1_MON						(1 << 1)
#define CORE1_PCHCTL_PREQ1_SET						(1 << 0)
#define CORE1_PCHCTL_PSTATE1_SET_ON					(0x08 << 16)
#define CORE1_PCHCTL_PSTATE1_SET_OFF_EMULATED		(0x01 << 16)
#define CORE1_PCHCTL_PSTATE1_SET_OFF				(0x00 << 16)
#define BUS_MSTOP_MSTOPMODE_SET						(1 << 0)
#define BUS_MSTOP_MSTOPMODE_SET_WEN					(1 << 16)
#define OTHERFUNC1_REG_RES0_SET						(1 << 0)
#define OTHERFUNC1_REG_RES0_ON_WEN					(1 << 16)
#define OTHERFUNC2_REG_RES0_SET						(1 << 0)
#define OTHERFUNC2_REG_RES0_ON_WEN					(1 << 16)

#define BIT0_ON										(1 << 0)
#define BIT1_ON										(1 << 1)
#define BIT2_ON										(1 << 2)
#define BIT3_ON										(1 << 3)
#define BIT4_ON										(1 << 4)
#define BIT5_ON										(1 << 5)
#define BIT6_ON										(1 << 6)
#define BIT7_ON										(1 << 7)
#define BIT8_ON										(1 << 8)
#define BIT9_ON										(1 << 9)
#define BIT10_ON									(1 << 10)
#define BIT11_ON									(1 << 11)
#define BIT12_ON									(1 << 12)
#define BIT13_ON									(1 << 13)
#define BIT14_ON									(1 << 14)
#define BIT15_ON									(1 << 15)
#define BIT16_ON									(1 << 16)
#define BIT17_ON									(1 << 17)
#define BIT18_ON									(1 << 18)
#define BIT19_ON									(1 << 19)
#define BIT20_ON									(1 << 20)
#define BIT21_ON									(1 << 21)
#define BIT22_ON									(1 << 22)
#define BIT23_ON									(1 << 23)
#define BIT24_ON									(1 << 24)
#define BIT25_ON									(1 << 25)
#define BIT26_ON									(1 << 26)
#define BIT27_ON									(1 << 27)
#define BIT28_ON									(1 << 28)
#define BIT29_ON									(1 << 29)
#define BIT30_ON									(1 << 30)
#define BIT31_ON									(1 << 31)

#endif	/* __RZF_DEV_CPG_REGS_H__ */
