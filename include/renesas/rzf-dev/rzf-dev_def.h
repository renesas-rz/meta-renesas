// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 */

#ifndef __RZF_DEV_DEF_H__
#define __RZF_DEV_DEF_H__

#define RZF_BOOT_ROM_BASE         (0x00000000)
#define RZF_MSRAM_BASE            (0x00010000)
#define RZF_ASRAM_BASE            (0x00020000)
#define RZF_DEVICE_BASE           (0x10000000)
#define RZF_SCIF0_BASE            (0x1004B800)
#define RZF_SPIMULT_BASE          (0x10060000)
#define RZF_SPIMULT_WBUF_BASE     (0x10070000)
#define RZF_SYC_BASE              (0x11000000)
#define RZF_CPG_BASE              (0x11010000)
#define RZF_SYSC_BASE             (0x11020000)
#define RZF_GPIO_BASE             (0x11030000)
#define RZF_TZC_ASRAM_BASE        (0x11040000)
#define RZF_TZC_MSRAM_BASE        (0x11050000)
#define RZF_TZC_SPI_BASE          (0x11060000)
#define RZF_TZC_DDR_BASE          (0x11070000)
#define RZF_DDR_PHY_BASE          (0x11400000)
#define RZF_DDR_MEMC_BASE         (0x11410000)
#define RZF_OTP_REG               (0x11860000)
#define RZF_SD0_BASE              (0x11C00000)
#define RZF_SD1_BASE              (0x11C10000)
#define RZF_SPIROM_BASE           (0x20000000)
#define RZF_DDR1_BASE             (0x40000000)
#define RZF_DDR2_BASE             (0x80000000)
#define RZF_DDR3_BASE             (0x100000000)

#define RZF_OTP_OTPTMPA1          (RZF_OTP_REG + 0x1178)
#define OTPTMPA1_DEVICE_ID_FIVE_1 (0x00000000)
#define OTPTMPA1_DEVICE_ID_FIVE_2 (0x00000001)
#define OTPTMPA1_DEVICE_ID_MASK   (0x0000000F)

#define RZF_SRAM_BASE             (RZF_MSRAM_BASE)

#define RZF_BOOT_ROM_SIZE         (0x00010000 - RZF_BOOT_ROM_BASE)
#define RZF_MSRAM_SIZE            (0x00020000 - RZF_MSRAM_BASE)
#define RZF_ASRAM_SIZE            (0x00030000 - RZF_ASRAM_BASE)
#define RZF_SRAM_SIZE             (RZF_MSRAM_SIZE + RZF_ASRAM_SIZE)
#define RZF_DEVICE_SIZE           (0x15000000 - RZF_DEVICE_BASE)
#define RZF_SPIROM_SIZE           (0x30000000 - RZF_SPIROM_BASE)
#define RZF_DDR1_SIZE             (RZF_DDR2_BASE - RZF_DDR1_BASE)
#define RZF_DDR2_SIZE             (RZF_DDR3_BASE - RZF_DDR2_BASE)

#define RZF_SPIROM_FIP_BASE       (RZF_SPIROM_BASE + 0x0001D200)
#define RZF_SPIROM_FIP_SIZE       (0x30000000 - RZF_SPIROM_FIP_BASE)

/* Boot Info base address */
#define RZF_BOOTINFO_BASE         (RZF_SRAM_BASE)

/* Base address where parameters to BL31 are stored */
#define PARAMS_BASE                 (RZF_SRAM_BASE + 0x0001F000)
#define PARAMS_SIZE                 (0x1000)

#endif /* __RZF_DEV_DEF_H__ */
