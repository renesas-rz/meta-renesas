// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2022, Renesas Electronics
 */
#ifndef __PTA_SCE_RSA_H
#define __PTA_SCE_RSA_H

#include <r_sce_api.h>

#define PTA_SCE_RSA_UUID \
    { 0x5ad57120, 0xc447, 0x4b17, \
        { 0x90, 0x7b, 0x03, 0x1a, 0xd8, 0xd9, 0xb1, 0x7c } }

/*
 * [in]      memref[0] : Message
 * [in/out]  memref[1] : Signature (128byte)
 * [in]	     memref[2] : Wrapped key (sce_rsa1024_private_wrapped_key_t)
 */
#define PTA_CMD_RSASSA_PKCS1024_SignatureGenerate   (0x00040000)

/*
 * [in]      memref[0] : Signature (128byte)
 * [in]      memref[1] : Message
 * [in]	     memref[2] : Wrapped key (sce_rsa1024_public_wrapped_key_t)
 */
#define PTA_CMD_RSASSA_PKCS1024_SignatureVerify     (0x00040010)

/*
 * [in]      memref[0] : Message
 * [in/out]  memref[1] : Signature (256byte)
 * [in]	     memref[2] : Wrapped key (sce_rsa2048_private_wrapped_key_t)
 */
#define PTA_CMD_RSASSA_PKCS2048_SignatureGenerate   (0x00040100)

/*
 * [in]      memref[0] : Signature (256byte)
 * [in]      memref[1] : Message
 * [in]	     memref[2] : Wrapped key (sce_rsa2048_public_wrapped_key_t)
 */
#define PTA_CMD_RSASSA_PKCS2048_SignatureVerify     (0x00040110)

/*
 * [in]      memref[0] : Signature (512byte)
 * [in]      memref[1] : Message
 * [in]	     memref[2] : Wrapped key (sce_rsa4096_public_wrapped_key_t)
 */
#define PTA_CMD_RSASSA_PKCS4096_SignatureVerify     (0x00040210)

/*
 * [in]      memref[0] : plain (size <= public key n size - 11 byte)
 * [in/out]  memref[1] : cipher (size >= public key n byte)
 * [in]	     memref[2] : Wrapped key (sce_rsa1024_public_wrapped_key_t)
 */
#define PTA_CMD_RSAES_PKCS1024_Encrypt              (0x00041000)

/*
 * [in]      memref[0] : cipher (size == public key n byte)
 * [in/out]  memref[1] : plain (size >= public key n - 11 byte)
 * [in]	     memref[2] : Wrapped key (sce_rsa1024_private_wrapped_key_t)
 */
#define PTA_CMD_RSAES_PKCS1024_Decrypt              (0x00041010)

/*
 * [in]      memref[0] : plain (size <= public key n - 11 byte)
 * [in/out]  memref[1] : cipher (size >= public key n byte)
 * [in]      memref[2] : Wrapped key (sce_rsa2048_public_wrapped_key_t)
 */
#define PTA_CMD_RSAES_PKCS2048_Encrypt              (0x00041100)

/*
 * [in]      memref[0] : cipher (size == public key n byte)
 * [in/out]  memref[1] : plain (size >= public key n - 11 byte)
 * [in]      memref[2] : Wrapped key (sce_rsa2048_private_wrapped_key_t)
 */
#define PTA_CMD_RSAES_PKCS2048_Decrypt              (0x00041110)

/*
 * [in]      memref[0] : plain (size <= public key n - 11 byte)
 * [in/out]  memref[1] : cipher (size >= public key n byte)
 * [in]      memref[2] : Wrapped key (sce_rsa4096_public_wrapped_key_t)
 */
#define PTA_CMD_RSAES_PKCS4096_Encrypt              (0x00041200)

#endif /* __PTA_SCE_RSA_H */
