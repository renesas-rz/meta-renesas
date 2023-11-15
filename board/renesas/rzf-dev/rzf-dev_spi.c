// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 */

#include <common.h>
#include <renesas/rzf-dev/rzf-dev_def.h>
#include "rzf-dev_spi_multi.h"
#include <renesas/rzf-dev/rzf-dev_spi_multi_regs.h>
#include <renesas/rzf-dev/mmio.h>
#include <asm/io.h>

static uint32_t spi_multi_cmd_tbl[2][3] = {
	{
		DRCMR_CMD_FAST_READ_3B,
		DRCMR_CMD_QUAD_OUTPUT_FAST_READ_3B,
		DRCMR_CMD_QUAD_INPUT_OUTPUT_FAST_READ_3B
	},
	{
		DRCMR_CMD_FAST_READ_4B,
		DRCMR_CMD_QUAD_OUTPUT_FAST_READ_4B,
		DRCMR_CMD_QUAD_INPUT_OUTPUT_FAST_READ_4B
	}
};

typedef struct {
	uint32_t  adr_width;
	uint32_t  data_width;
} SPI_MULTI_BIT_WIDE_PTN;

static SPI_MULTI_BIT_WIDE_PTN spi_multi_bit_ptn[3] = {
	{ DRENR_ADB_1BIT, DRENR_DRDB_1BIT },
	{ DRENR_ADB_1BIT, DRENR_DRDB_4BIT },
	{ DRENR_ADB_4BIT, DRENR_DRDB_4BIT },
};

typedef struct {
	uint32_t  addr_width;
	uint32_t  flash_width;
} SPI_MULTI_ADDR_WIDE_PTN;

static SPI_MULTI_ADDR_WIDE_PTN spi_multi_addr_ptn[2] = {
	{ DRENR_ADE_ADD23_OUT, DREAR_EAC_EXADDR24 },
	{ DRENR_ADE_ADD31_OUT, DREAR_EAC_EXADDR25 }
};

static void spi_multi_timing_set(void)
{
	/* Timing adjustment register setting */
	mmio_write_32(SPIM_PHYADJ2, 0xA5390000);
	mmio_write_32(SPIM_PHYADJ1, 0x80000000);
	mmio_write_32(SPIM_PHYADJ2, 0x00008080);
	mmio_write_32(SPIM_PHYADJ1, 0x80000022);
	mmio_write_32(SPIM_PHYADJ2, 0x00008080);
	mmio_write_32(SPIM_PHYADJ1, 0x80000024);

	/* SDR mode serial flash settings */
	mmio_write_32(SPIM_PHYCNT, (PHYCNT_DEF_DATA | PHYCNT_CKSEL_FAST));

	/* Timing adjustment register setting */
	mmio_write_32(SPIM_PHYADJ2, 0x00000030);
	mmio_write_32(SPIM_PHYADJ1, 0x80000032);
    
    wmb();
}

int spi_multi_setup(uint32_t addr_width, uint32_t dq_width, uint32_t dummy_cycle)
{
	uint32_t val;

	/* parameter check */
	if ((addr_width > SPI_MULTI_ADDR_WIDES_32) ||
		(dq_width > SPI_MULTI_DQ_WIDES_1_4_4)  ||
		(0 == dummy_cycle)                     ||
		(dummy_cycle > SPI_MULTI_DUMMY_20CYCLE))
		return -1;

	/* Wait until the transfer is complete */
	do {
		val = mmio_read_32(SPIM_CMNSR);
	} while ((val & CMNSR_TEND) == 0);

	/* SDR mode serial flash settings */
	mmio_write_32(SPIM_PHYCNT, PHYCNT_DEF_DATA);

	/* Read timing setting */
	val = PHYOFFSET1_DEF_DATA | PHYOFFSET1_DDRTMG_SPIDRE_0;
	mmio_write_32(SPIM_PHYOFFSET1, val);
	mmio_write_32(SPIM_PHYOFFSET2, PHYOFFSET2_DEF_DATA);

	/* Set the QSPIn_SSL setting value */
	val = CMNCR_IO0FV_OUT_PREV | CMNCR_IO2FV_OUT_PREV |
		  CMNCR_IO3FV_OUT_PREV | CMNCR_MOIIO0_OUT1 |
		  CMNCR_MOIIO1_OUT1    | CMNCR_MOIIO2_OUT1 |
		  CMNCR_MOIIO3_OUT1    | CMNCR_DEF_DATA;
	mmio_write_32(SPIM_CMNCR, val);

	val = SSLDR_SCKDL_4_5 | SSLDR_SLNDL_4QSPIn | SSLDR_SPNDL_4QSPIn;
	mmio_write_32(SPIM_SSLDR, val);

	/* Clear the RBE bit */
	val = DRCR_RBE | DRCR_RCF | DRCR_RBURST_32_DATALEN;
	mmio_write_32(SPIM_DRCR, val);
	mmio_read_32(SPIM_DRCR);

	/* Set the data read command */
	mmio_write_32(SPIM_DRCMR, spi_multi_cmd_tbl[addr_width][dq_width]);

	/* Extended external address setting */
	mmio_write_32(SPIM_DREAR, spi_multi_addr_ptn[addr_width].flash_width);

	/* Set the bit width of command and address output to 1 bit and	*/
	/* the address size to 4 byte									*/
	val = DRENR_CDB_1BIT | DRENR_OCDB_1BIT | spi_multi_bit_ptn[dq_width].adr_width |
		  DRENR_OPDB_1BIT | spi_multi_bit_ptn[dq_width].data_width | DRENR_CDE | DRENR_DME |
		  spi_multi_addr_ptn[addr_width].addr_width | DRENR_OPDE_NO_OUT;
	mmio_write_32(SPIM_DRENR, val);

	/* Dummy cycle setting */
	mmio_write_32(SPIM_DRDMCR, dummy_cycle);

	/* Change to SPI flash mode */
	mmio_write_32(SPIM_DRDRENR, 0x00000000);

	/* Timing adjustment register setting */
	spi_multi_timing_set();

	return 0;
}
