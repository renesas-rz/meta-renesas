// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2022, Renesas Electronics
 */
#ifndef __PTA_SCE_SHA_H
#define __PTA_SCE_SHA_H

#include <r_sce_api.h>

#define PTA_SCE_SHA_UUID \
    { 0x5b6cecf4, 0x12ae, 0x4c0f, \
        { 0x94, 0xb5, 0xce, 0xcc, 0x5f, 0x48, 0x62, 0xe4 } }

/*
 * [in/out] memref[0] : AES handler (sce_sha_md5_handle_t)
 */
#define PTA_CMD_SHA224_Init                 (0x00030000)

/*
 * [in/out] memref[0] : AES handler (sce_sha_md5_handle_t)
 * [in]	    memref[1] : Message
 */
#define PTA_CMD_SHA224_Update               (0x00030001)

/*
 * [in/out] memref[0] : AES handler (sce_sha_md5_handle_t)
 * [in/out] memref[1] : Digest (28byte)
 */
#define PTA_CMD_SHA224_Final                (0x00030002)

/*
 * [in/out] memref[0] : AES handler (sce_sha_md5_handle_t)
 */
#define PTA_CMD_SHA256_Init                 (0x00030100)

/*
 * [in/out] memref[0] : AES handler (sce_sha_md5_handle_t)
 * [in]	    memref[1] : Message
 */
#define PTA_CMD_SHA256_Update               (0x00030101)

/*
 * [in/out] memref[0] : AES handler (sce_sha_md5_handle_t)
 * [in/out] memref[1] : Digest (32byte)
 */
#define PTA_CMD_SHA256_Final                (0x00030102)

#endif /* __PTA_SCE_SHA_H */
