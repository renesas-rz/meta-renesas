// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 */

#ifndef __RZF_DEV_SYS_H__
#define __RZF_DEV_SYS_H__

#define MASK_BOOTM_DEVICE		(0x0F)
#define MASK_BOOTM_SECURE		(0x10)

#define BOOT_MODE_ESD           (0)
#define BOOT_MODE_EMMC_1_8      (1)
#define BOOT_MODE_EMMC_3_3      (2)
#define BOOT_MODE_SPI_1_8       (3)
#define BOOT_MODE_SPI_3_3       (4)
#define BOOT_MODE_SCIF          (5)

#endif	/* __RZF_DEV_SYS_H__ */
