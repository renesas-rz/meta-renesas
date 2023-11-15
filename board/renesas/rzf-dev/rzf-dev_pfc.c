// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 */

#include <common.h>
#include <renesas/rzf-dev/rzf-dev_def.h>
#include <renesas/rzf-dev/rzf-dev_pfc_regs.h>
#include <renesas/rzf-dev/mmio.h>

static PFC_REGS pfc_scif_type1_reg_tbl[PFC_SCIF_TBL_NUM] = {
	{
		{ PFC_ON,  (uintptr_t)PFC_PMC16,  0x18 },					/* PMC */
		{ PFC_ON,  (uintptr_t)PFC_PFC16,  0x00066000 },				/* PFC */
		{ PFC_ON,  (uintptr_t)PFC_IOLH16, 0x0000000303000000 },		/* IOLH */
		{ PFC_OFF, (uintptr_t)PFC_PUPD16, 0x0000000000000000 },		/* PUPD */
		{ PFC_OFF, (uintptr_t)PFC_SR16,   0x0000000000000101 },		/* SR */
		{ PFC_OFF, (uintptr_t)NULL,       0 }						/* IEN */
	}
};

static PFC_REGS pfc_scif_type2_reg_tbl[PFC_SCIF_TBL_NUM] = {
	{
		{ PFC_ON,  (uintptr_t)PFC_PMC18,  0x06 },					/* PMC */
		{ PFC_ON,  (uintptr_t)PFC_PFC18,  0x00000220 },				/* PFC */
		{ PFC_OFF, (uintptr_t)PFC_IOLH18, 0x0000000303000000 },		/* IOLH */
		{ PFC_OFF, (uintptr_t)PFC_PUPD18, 0x0000000000000000 },		/* PUPD */
		{ PFC_OFF, (uintptr_t)PFC_SR18,   0x0000000000000101 },		/* SR */
		{ PFC_OFF, (uintptr_t)NULL,       0 }						/* IEN */
	}
};

static PFC_REGS  pfc_qspi_reg_tbl[PFC_QSPI_TBL_NUM] = {
	/* QSPI0 */
	{
		{ PFC_ON,  (uintptr_t)PFC_PMC0A,  0x3F },					/* PMC */
		{ PFC_ON,  (uintptr_t)PFC_PFC0A,  0x00000000 },				/* PFC */
		{ PFC_ON,  (uintptr_t)PFC_IOLH0A, 0x0000020202020202 },		/* IOLH */
		{ PFC_ON,  (uintptr_t)PFC_PUPD0A, 0x0000000000000000 },		/* PUPD */
		{ PFC_ON,  (uintptr_t)PFC_SR0A,   0x0000010101010101 },		/* SR */
		{ PFC_OFF, (uintptr_t)NULL,       0 }						/* IEN */
	},
	/* QSPIn */
	{
		{ PFC_ON,  (uintptr_t)PFC_PMC0C,  0x03 },					/* PMC */
		{ PFC_ON,  (uintptr_t)PFC_PFC0C,  0x00000000 },				/* PFC */
		{ PFC_ON,  (uintptr_t)PFC_IOLH0C, 0x0000000000000202 },		/* IOLH */
		{ PFC_OFF, (uintptr_t)PFC_PUPD0C, 0x0000000000000000 },		/* PUPD */
		{ PFC_ON,  (uintptr_t)PFC_SR0C,   0x0000000000000101 },		/* SR */
		{ PFC_OFF, (uintptr_t)NULL,       0 }						/* IEN */
	}
};

static PFC_REGS  pfc_sd_reg_tbl[PFC_SD_TBL_NUM] = {
	/* SD0_CD/SD0_WP/SD1_CD/SD1_WP */
	{
		{ PFC_ON,  (uintptr_t)PFC_PMC10,  0x0F },					/* PMC */
		{ PFC_ON,  (uintptr_t)PFC_PFC10,  0x00001111 },				/* PFC */
		{ PFC_OFF, (uintptr_t)NULL,       0x0000000000000000 },		/* IOLH */
		{ PFC_OFF, (uintptr_t)NULL,       0x0000000000000000 },		/* PUPD */
		{ PFC_OFF, (uintptr_t)NULL,       0x0000000000000000 },		/* SR */
		{ PFC_OFF, (uintptr_t)NULL,       0x0000000000000000 }		/* IEN */
	},
	/* SD0_CLK */
	{
		{ PFC_ON,  (uintptr_t)PFC_PMC06,  0x07 },					/* PMC */
		{ PFC_ON,  (uintptr_t)PFC_PFC06,  0x00000000 },				/* PFC */
		{ PFC_ON,  (uintptr_t)PFC_IOLH06, 0x0000000000020202 },		/* IOLH */
		{ PFC_ON,  (uintptr_t)PFC_PUPD06, 0x0000000000000000 },		/* PUPD */
		{ PFC_ON,  (uintptr_t)PFC_SR06,   0x0000000000010101 },		/* SR */
		{ PFC_ON,  (uintptr_t)PFC_IEN06,  0x0000000000000100 }		/* IEN */
	},
	/* SD0_DATA */
	{
		{ PFC_ON, (uintptr_t)PFC_PMC07,  0xFF },					/* PMC */
		{ PFC_ON, (uintptr_t)PFC_PFC07,  0x00000000 },				/* PFC */
		{ PFC_ON, (uintptr_t)PFC_IOLH07, 0x0202020202020202 },		/* IOLH */
		{ PFC_ON, (uintptr_t)PFC_PUPD07, 0x0000000000000000 },		/* PUPD */
		{ PFC_ON, (uintptr_t)PFC_SR07,   0x0101010101010101 },		/* SR */
		{ PFC_ON, (uintptr_t)PFC_IEN07,  0x0101010101010101 }		/* IEN */
	},
	/* SD1_CLK */
	{
		{ PFC_ON, (uintptr_t)PFC_PMC08,  0x03 },					/* PMC */
		{ PFC_ON, (uintptr_t)PFC_PFC08,  0x00000000 },				/* PFC */
		{ PFC_ON, (uintptr_t)PFC_IOLH08, 0x0000000000000202 },		/* IOLH */
		{ PFC_ON, (uintptr_t)PFC_PUPD08, 0x0000000000000000 },		/* PUPD */
		{ PFC_ON, (uintptr_t)PFC_SR08,   0x0000000000000101 },		/* SR */
		{ PFC_ON, (uintptr_t)PFC_IEN08,  0x0000000000000100 }		/* IEN */
	},
	/* SD1_DATA */
	{
		{ PFC_ON, (uintptr_t)PFC_PMC09,  0x0F },					/* PMC */
		{ PFC_ON, (uintptr_t)PFC_PFC09,  0x00000000 },				/* PFC */
		{ PFC_ON, (uintptr_t)PFC_IOLH09, 0x0000000002020202 },		/* IOLH */
		{ PFC_ON, (uintptr_t)PFC_PUPD09, 0x0000000000000000 },		/* PUPD */
		{ PFC_ON, (uintptr_t)PFC_SR09,   0x0000000001010101 },		/* SR */
		{ PFC_ON, (uintptr_t)PFC_IEN09,  0x0000000001010101 }		/* IEN */
	}
};


static void pfc_scif_setup(void)
{
	int      cnt;
    uint32_t otp_otptmpa1;
    PFC_REGS *pfc_scif_reg_tbl;
    
    otp_otptmpa1 =  *(volatile uint32_t *)RZF_OTP_OTPTMPA1;
    if ((otp_otptmpa1 & OTPTMPA1_DEVICE_ID_MASK) != OTPTMPA1_DEVICE_ID_FIVE_2)
    {
        pfc_scif_reg_tbl = pfc_scif_type1_reg_tbl;
    }
    else
    {
        pfc_scif_reg_tbl = pfc_scif_type2_reg_tbl;
    }

	/* multiplexer terminal switching */
	mmio_write_32(PFC_PWPR, 0x0);
	mmio_write_32(PFC_PWPR, PWPR_PFCWE);

	for (cnt = 0; cnt < PFC_SCIF_TBL_NUM; cnt++) {
		/* PMC */
		if (pfc_scif_reg_tbl[cnt].pmc.flg == PFC_ON) {
			mmio_write_8(pfc_scif_reg_tbl[cnt].pmc.reg, pfc_scif_reg_tbl[cnt].pmc.val);
		}
		/* PFC */
		if (pfc_scif_reg_tbl[cnt].pfc.flg == PFC_ON) {
			mmio_write_32(pfc_scif_reg_tbl[cnt].pfc.reg, pfc_scif_reg_tbl[cnt].pfc.val);
		}
		/* IOLH */
		if (pfc_scif_reg_tbl[cnt].iolh.flg == PFC_ON) {
			mmio_write_64(pfc_scif_reg_tbl[cnt].iolh.reg, pfc_scif_reg_tbl[cnt].iolh.val);
		}
		/* PUPD */
		if (pfc_scif_reg_tbl[cnt].pupd.flg == PFC_ON) {
			mmio_write_64(pfc_scif_reg_tbl[cnt].pupd.reg, pfc_scif_reg_tbl[cnt].pupd.val);
		}
		/* SR */
		if (pfc_scif_reg_tbl[cnt].sr.flg == PFC_ON) {
			mmio_write_64(pfc_scif_reg_tbl[cnt].sr.reg, pfc_scif_reg_tbl[cnt].sr.val);
		}
	}

	mmio_write_32(PFC_PWPR, 0x0);
	mmio_write_32(PFC_PWPR, PWPR_B0Wl);
}

static void pfc_qspi_setup(void)
{
	int      cnt;

	mmio_write_32(PFC_SD_ch0, 1);
	mmio_write_32(PFC_SD_ch1, 0);

	for (cnt = 0; cnt < PFC_QSPI_TBL_NUM; cnt++) {
		/* PMC */
		if (pfc_qspi_reg_tbl[cnt].pmc.flg == PFC_ON) {
			mmio_write_8(pfc_qspi_reg_tbl[cnt].pmc.reg, pfc_qspi_reg_tbl[cnt].pmc.val);
		}
		/* PFC */
		if (pfc_qspi_reg_tbl[cnt].pfc.flg == PFC_ON) {
			mmio_write_32(pfc_qspi_reg_tbl[cnt].pfc.reg, pfc_qspi_reg_tbl[cnt].pfc.val);
		}
		/* IOLH */
		if (pfc_qspi_reg_tbl[cnt].iolh.flg == PFC_ON) {
			mmio_write_64(pfc_qspi_reg_tbl[cnt].iolh.reg, pfc_qspi_reg_tbl[cnt].iolh.val);
		}
		/* PUPD */
		if (pfc_qspi_reg_tbl[cnt].pupd.flg == PFC_ON) {
			mmio_write_64(pfc_qspi_reg_tbl[cnt].pupd.reg, pfc_qspi_reg_tbl[cnt].pupd.val);
		}
		/* SR */
		if (pfc_qspi_reg_tbl[cnt].sr.flg == PFC_ON) {
			mmio_write_64(pfc_qspi_reg_tbl[cnt].sr.reg, pfc_qspi_reg_tbl[cnt].sr.val);
		}
	}

	mmio_write_32(PFC_PWPR, 0x0);
	mmio_write_32(PFC_PWPR, PWPR_B0Wl);
}

static void pfc_sd_setup(void)
{
	int      cnt;

	mmio_write_32(PFC_SD_ch0, 1);
	mmio_write_32(PFC_SD_ch1, 0);

	for (cnt = 0; cnt < PFC_SD_TBL_NUM; cnt++) {
		/* PMC */
		if (pfc_sd_reg_tbl[cnt].pmc.flg == PFC_ON) {
			mmio_write_8(pfc_sd_reg_tbl[cnt].pmc.reg, pfc_sd_reg_tbl[cnt].pmc.val);
		}
		/* PFC */
		if (pfc_sd_reg_tbl[cnt].pfc.flg == PFC_ON) {
			mmio_write_32(pfc_sd_reg_tbl[cnt].pfc.reg, pfc_sd_reg_tbl[cnt].pfc.val);
		}
		/* IOLH */
		if (pfc_sd_reg_tbl[cnt].iolh.flg == PFC_ON) {
			mmio_write_64(pfc_sd_reg_tbl[cnt].iolh.reg, pfc_sd_reg_tbl[cnt].iolh.val);
		}
		/* PUPD */
		if (pfc_sd_reg_tbl[cnt].pupd.flg == PFC_ON) {
			mmio_write_64(pfc_sd_reg_tbl[cnt].pupd.reg, pfc_sd_reg_tbl[cnt].pupd.val);
		}
		/* SR */
		if (pfc_sd_reg_tbl[cnt].sr.flg == PFC_ON) {
			mmio_write_64(pfc_sd_reg_tbl[cnt].sr.reg, pfc_sd_reg_tbl[cnt].sr.val);
		}
		/* IEN */
		if (pfc_sd_reg_tbl[cnt].ien.flg == PFC_ON) {
			mmio_write_64(pfc_sd_reg_tbl[cnt].ien.reg, pfc_sd_reg_tbl[cnt].ien.val);
		}
	}

	mmio_write_32(PFC_PWPR, 0x0);
	mmio_write_32(PFC_PWPR, PWPR_B0Wl);
}

void pfc_setup(void)
{
    pfc_scif_setup();
	pfc_qspi_setup();
	pfc_sd_setup();
}

