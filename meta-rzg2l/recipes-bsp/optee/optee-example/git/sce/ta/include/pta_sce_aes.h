// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2022, Renesas Electronics
 */
#ifndef __PTA_SCE_AES_H
#define __PTA_SCE_AES_H

#include <r_sce_api.h>

#define PTA_SCE_AES_UUID \
    { 0x4be7b9c4, 0x4951, 0x4105, \
        { 0xa3, 0xd3, 0x08, 0x1b, 0x50, 0x98, 0x10, 0xef } }

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 */
#define PTA_CMD_AES128ECB_EncryptInit       (0x00020001)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : plain (length must be a multiple of 16)
 * [in/out] memref[2] : cipher
 */
#define PTA_CMD_AES128ECB_EncryptUpdate     (0x00020002)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES128ECB_EncryptFinal      (0x00020003)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 */
#define PTA_CMD_AES128ECB_DecryptInit       (0x00020011)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : cipher (length must be a multiple of 16)
 * [in/out] memref[2] : plain
 */
#define PTA_CMD_AES128ECB_DecryptUpdate     (0x00020012)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES128ECB_DecryptFinal      (0x00020013)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 */
#define PTA_CMD_AES256ECB_EncryptInit       (0x00020101)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : plain (length must be a multiple of 16)
 * [in/out] memref[2] : cipher
 */
#define PTA_CMD_AES256ECB_EncryptUpdate     (0x00020102)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES256ECB_EncryptFinal      (0x00020103)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 */
#define PTA_CMD_AES256ECB_DecryptInit       (0x00020111)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : cipher (length must be a multiple of 16)
 * [in/out] memref[2] : plain
 */
#define PTA_CMD_AES256ECB_DecryptUpdate     (0x00020112)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES256ECB_DecryptFinal      (0x00020113)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 * [in]     memref[2] : Initial Vector(16byte)
 */
#define PTA_CMD_AES128CBC_EncryptInit       (0x00021001)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : plain (length must be a multiple of 16)
 * [in/out] memref[2] : cipher
 */
#define PTA_CMD_AES128CBC_EncryptUpdate     (0x00021002)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES128CBC_EncryptFinal      (0x00021003)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 * [in]     memref[2] : Initial Vector(16byte)
 */
#define PTA_CMD_AES128CBC_DecryptInit       (0x00021011)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : cipher (length must be a multiple of 16)
 * [in/out] memref[2] : plain
 */
#define PTA_CMD_AES128CBC_DecryptUpdate     (0x00021012)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES128CBC_DecryptFinal      (0x00021013)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 * [in]     memref[2] : Initial Vector(16byte)
 */
#define PTA_CMD_AES256CBC_EncryptInit       (0x00021101)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : plain (length must be a multiple of 16)
 * [in/out] memref[2] : cipher
 */
#define PTA_CMD_AES256CBC_EncryptUpdate     (0x00021102)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES256CBC_EncryptFinal      (0x00021103)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 * [in]     memref[2] : Initial Vector(16byte)
 */
#define PTA_CMD_AES256CBC_DecryptInit       (0x00021111)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : cipher (length must be a multiple of 16)
 * [in/out] memref[2] : plain
 */
#define PTA_CMD_AES256CBC_DecryptUpdate     (0x00021112)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES256CBC_DecryptFinal      (0x00021113)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 * [in]     memref[2] : Initial Vector(16byte)
 */
#define PTA_CMD_AES128CTR_EncryptInit       (0x00022001)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : plain (length must be a multiple of 16)
 * [in/out] memref[2] : cipher
 */
#define PTA_CMD_AES128CTR_EncryptUpdate     (0x00022002)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES128CTR_EncryptFinal      (0x00022003)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 * [in]     memref[2] : Initial Vector(16byte)
 */
#define PTA_CMD_AES128CTR_DecryptInit       (0x00022011)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : cipher (length must be a multiple of 16)
 * [in/out] memref[2] : plain
 */
#define PTA_CMD_AES128CTR_DecryptUpdate     (0x00022012)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES128CTR_DecryptFinal      (0x00022013)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 * [in]     memref[2] : Initial Vector(16byte)
 */
#define PTA_CMD_AES256CTR_EncryptInit       (0x00022101)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : plain (length must be a multiple of 16)
 * [in/out] memref[2] : cipher
 */
#define PTA_CMD_AES256CTR_EncryptUpdate     (0x00022102)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES256CTR_EncryptFinal      (0x00022103)

/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 * [in]     memref[2] : Initial Vector(16byte)
 */
#define PTA_CMD_AES256CTR_DecryptInit       (0x00022111)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 * [in]     memref[1] : cipher (length must be a multiple of 16)
 * [in/out] memref[2] : plain
 */
#define PTA_CMD_AES256CTR_DecryptUpdate     (0x00022112)
/*
 * [in/out] memref[0] : AES handler (sce_aes_handle_t)
 */
#define PTA_CMD_AES256CTR_DecryptFinal      (0x00022113)

/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 */
#define PTA_CMD_AES128CMAC_GenerateInit     (0x00023001)
/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : message
 */
#define PTA_CMD_AES128CMAC_GenerateUpdate   (0x00023002)
/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in/out] memref[1] : mac (16byte)
 */
#define PTA_CMD_AES128CMAC_GenerateFinal    (0x00023003)

/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 */
#define PTA_CMD_AES128CMAC_VerifyInit       (0x00023011)
/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : message
 */
#define PTA_CMD_AES128CMAC_VerifyUpdate     (0x00023012)
/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : mac (2 to 16bytes)
 */
#define PTA_CMD_AES128CMAC_VerifyFinal      (0x00023013)

/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 */
#define PTA_CMD_AES256CMAC_GenerateInit     (0x00023101)
/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : message
 */
#define PTA_CMD_AES256CMAC_GenerateUpdate   (0x00023102)
/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in/out] memref[1] : mac (16byte)
 */
#define PTA_CMD_AES256CMAC_GenerateFinal    (0x00023103)

/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : Wrapped key (sce_aes_wrapped_key_t)
 */
#define PTA_CMD_AES256CMAC_VerifyInit       (0x00023111)
/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : message
 */
#define PTA_CMD_AES256CMAC_VerifyUpdate     (0x00023112)
/*
 * [in/out] memref[0] : CMAC handler (sce_cmac_handle_t)
 * [in]     memref[1] : mac (2 to 16bytes)
 */
#define PTA_CMD_AES256CMAC_VerifyFinal      (0x00023113)


#endif /* __PTA_SCE_AES_H */
