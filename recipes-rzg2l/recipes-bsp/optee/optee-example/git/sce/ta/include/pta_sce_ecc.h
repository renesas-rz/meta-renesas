// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2022, Renesas Electronics
 */
#ifndef __PTA_SCE_ECC_H
#define __PTA_SCE_ECC_H

#include <r_sce_api.h>

#define PTA_SCE_ECC_UUID \
    { 0xa0c74f91, 0xbaac, 0x4ba3, \
        { 0x96, 0xbe, 0x58, 0xe5, 0x1f, 0xb1, 0xd1, 0xba } }

/*
 * [in]      memref[0] : Message
 * [in/out]  memref[1] : Signature (64byte)
 * [in]	     memref[2] : Wrapped key (sce_ecc_private_wrapped_key_t)
 */
#define PTA_CMD_ECDSA_secp192r1_SignatureGenerate       (0x00050000)

/*
 * [in]      memref[0] : Signature (64byte)
 * [in]      memref[1] : Message
 * [in]	     memref[2] : Wrapped key (sce_ecc_public_wrapped_key_t)
 */
#define PTA_CMD_ECDSA_secp192r1_SignatureVerify         (0x00050010)

/*
 * [in]      memref[0] : Message
 * [in/out]  memref[1] : Signature (64byte)
 * [in]      memref[2] : Wrapped key (sce_ecc_private_wrapped_key_t)
 */
#define PTA_CMD_ECDSA_secp224r1_SignatureGenerate       (0x00050100)

/*
 * [in]      memref[0] : Signature (64byte)
 * [in]      memref[1] : Message
 * [in]      memref[2] : Wrapped key (sce_ecc_public_wrapped_key_t)
 */
#define PTA_CMD_ECDSA_secp224r1_SignatureVerify         (0x00050110)

/*
 * [in]      memref[0] : Message
 * [in/out]  memref[1] : Signature (64byte)
 * [in]      memref[2] : Wrapped key (sce_ecc_private_wrapped_key_t)
 */
#define PTA_CMD_ECDSA_secp256r1_SignatureGenerate       (0x00050200)

/*
 * [in]      memref[0] : Signature (64byte)
 * [in]      memref[1] : Message
 * [in]      memref[2] : Wrapped key (sce_ecc_public_wrapped_key_t)
 */
#define PTA_CMD_ECDSA_secp256r1_SignatureVerify         (0x00050210)

/*
 * [in]      memref[0] : Message
 * [in/out]  memref[1] : Signature (64byte)
 * [in]      memref[2] : Wrapped key (sce_ecc_private_wrapped_key_t)
 */
#define PTA_CMD_ECDSA_BrainpoolP512r1_SignatureGenerate (0x00051000)

/*
 * [in]      memref[0] : Signature (64byte)
 * [in]      memref[1] : Message
 * [in]      memref[2] : Wrapped key (sce_ecc_public_wrapped_key_t)
 */
#define PTA_CMD_ECDSA_BrainpoolP512r1_SignatureVerify   (0x00051010)

#endif /* __PTA_SCE_ECC_H */
