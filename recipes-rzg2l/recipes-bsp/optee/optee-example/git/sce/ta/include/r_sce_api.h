/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_sce_api.h
 * Version      : 1.0
 * Description  : SCE API header file
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 03.31.2022 1.00     First Release
 *********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup SCE_PROTECTED_API SCE Interface
 * @brief Interface for Secure Crypto Engine (SCE) functions.
 *
 * @section SCE_PROTECTED_API_Summary Summary
 * The SCE interface provides SCE functionality.
 *
 * The SCE interface can be implemented by:
 * - @ref SCE_PROTECTED
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>

#ifndef R_SCE_API_H
#define R_SCE_API_H



/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define FSP_PARAMETER_NOT_USED(p)    ((void) ((p)))

/* For AES operation. */
#define HW_SCE_AES128_KEY_INDEX_WORD_SIZE                         (12U)
#define HW_SCE_AES256_KEY_INDEX_WORD_SIZE                         (16U)
#define HW_SCE_AES128_KEY_WORD_SIZE                               (4U)
#define HW_SCE_AES256_KEY_WORD_SIZE                               (8U)
#define HW_SCE_AES128_KEY_BYTE_SIZE                               (16U)
#define HW_SCE_AES256_KEY_BYTE_SIZE                               (32U)
#define HW_SCE_AES_BLOCK_BYTE_SIZE                                (16U)
#define HW_SCE_AES_BLOCK_BIT_SIZE                                 (128U)
#define HW_SCE_AES_CBC_IV_BYTE_SIZE                               (16U)

/* For SHA operation. */
#define HW_SCE_SHA224_HASH_LENGTH_BYTE_SIZE                       (28U)
#define HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE                       (32U)
#define HW_SCE_SHA512_HASH_LENGTH_BYTE_SIZE                       (64U)

/* For RSA operation. */
#define HW_SCE_RSA_1024_KEY_N_LENGTH_BYTE_SIZE                    (128U)
#define HW_SCE_RSA_1024_KEY_E_LENGTH_BYTE_SIZE                    (4U)
#define HW_SCE_RSA_1024_KEY_D_LENGTH_BYTE_SIZE                    (128U)
#define HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE                    (256U)
#define HW_SCE_RSA_2048_KEY_E_LENGTH_BYTE_SIZE                    (4U)
#define HW_SCE_RSA_2048_KEY_D_LENGTH_BYTE_SIZE                    (256U)
#define HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE                    (128 * 4U)
#define HW_SCE_RSA_4096_KEY_E_LENGTH_BYTE_SIZE                    (4U)
#define HW_SCE_RSA_4096_KEY_D_LENGTH_BYTE_SIZE                    (128 * 4U)
#define HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE     (4U)
#define HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE     (36U)
#define HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE    (4U)
#define HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE    (68U)
#define HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE     (4U)
#define HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE     (68U)
#define HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE    (4U)
#define HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE    (132U)
#define HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE     (4U)
#define HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE     (4U)
#define HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE                 (12U)
#define HW_SCE_RSA1024_NE_KEY_BYTE_SIZE                           (144U)
#define HW_SCE_RSA1024_ND_KEY_BYTE_SIZE                           (256U)
#define HW_SCE_RSA2048_NE_KEY_BYTE_SIZE                           (272U)
#define HW_SCE_RSA2048_ND_KEY_BYTE_SIZE                           (512U)
#define HW_SCE_RSA4096_NE_KEY_BYTE_SIZE                           (128 * 4 + 16U)
#define HW_SCE_RSA4096_ND_KEY_BYTE_SIZE                           (256 * 4U)
#define HW_SCE_RSA1024_NE_KEY_INDEX_WORD_SIZE                     (76U)
#define HW_SCE_RSA1024_ND_KEY_INDEX_WORD_SIZE                     (104U)
#define HW_SCE_RSA2048_NE_KEY_INDEX_WORD_SIZE                     (140U)
#define HW_SCE_RSA2048_ND_KEY_INDEX_WORD_SIZE                     (200U)
#define HW_SCE_RSA4096_NE_KEY_INDEX_WORD_SIZE                     (140U)
#define HW_SCE_RSA4096_ND_KEY_INDEX_WORD_SIZE                     (261U)
#define HW_SCE_RSA1024_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE          (76U)
#define HW_SCE_RSA1024_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE         (104U)
#define HW_SCE_RSA2048_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE          (140U)
#define HW_SCE_RSA2048_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE         (200U)

#define HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE    (11U)
#define HW_SCE_RSA_1024_DATA_BYTE_SIZE               (128U)
#define HW_SCE_RSA_2048_DATA_BYTE_SIZE               (256U)
#define HW_SCE_RSA_4096_DATA_BYTE_SIZE               (128 * 4U)

/* RSA HASH type. */
#define HW_SCE_RSA_HASH_SHA256                       (0x03) /* SHA-256 */

/* For ECC operation. */
#define HW_SCE_ECC_KEY_LENGTH_BYTE_SIZE                             (144U)
#define HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO_WORD_SIZE             (4U)
#define HW_SCE_ECC_PRIVATE_KEY_MANAGEMENT_INFO_WORD_SIZE            (24U)
#define HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE                             (64U)
#define HW_SCE_ECC_PRIVATE_KEY_BYTE_SIZE                            (32U)
#define HW_SCE_ECDSA_DATA_BYTE_SIZE                                 (64U)
#define HW_SCE_ECDSA_P512_DATA_BYTE_SIZE                            (128U)
#define HW_SCE_SHARED_SECRET_KEY_INDEX_WORD_SIZE                    (13U)

/* Key update. */
#define HW_SCE_UPDATE_KEY_RING_INDEX_WORD_SIZE                      (16U)

#define SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD                       (0)
#define SCE_OEM_KEY_SIZE_AES128_INST_DATA_WORD                      (8)
#define SCE_OEM_KEY_SIZE_AES256_INST_DATA_WORD                      (12)

#define SCE_OEM_KEY_SIZE_RSA1024_PUBLICK_KEY_INST_DATA_WORD         (40)
#define SCE_OEM_KEY_SIZE_RSA1024_PRIVATE_KEY_INST_DATA_WORD         (68)
#define SCE_OEM_KEY_SIZE_RSA2048_PUBLICK_KEY_INST_DATA_WORD         (72)
#define SCE_OEM_KEY_SIZE_RSA2048_PRIVATE_KEY_INST_DATA_WORD         (132)
#define SCE_OEM_KEY_SIZE_RSA4096_PUBLICK_KEY_INST_DATA_WORD         (136)
#define SCE_OEM_KEY_SIZE_RSA4096_PRIVATE_KEY_INST_DATA_WORD         (260)

#define SCE_OEM_KEY_SIZE_ECCP192_PUBLICK_KEY_INST_DATA_WORD         (20)
#define SCE_OEM_KEY_SIZE_ECCP192_PRIVATE_KEY_INST_DATA_WORD         (12)
#define SCE_OEM_KEY_SIZE_ECCP224_PUBLICK_KEY_INST_DATA_WORD         (20)
#define SCE_OEM_KEY_SIZE_ECCP224_PRIVATE_KEY_INST_DATA_WORD         (12)
#define SCE_OEM_KEY_SIZE_ECCP256_PUBLICK_KEY_INST_DATA_WORD         (20)
#define SCE_OEM_KEY_SIZE_ECCP256_PRIVATE_KEY_INST_DATA_WORD         (12)
#define SCE_OEM_KEY_SIZE_ECCP512_PUBLICK_KEY_INST_DATA_WORD         (36)
#define SCE_OEM_KEY_SIZE_ECCP512_PRIVATE_KEY_INST_DATA_WORD         (20)

#define SCE_INSTALL_KEY_RING_INDEX (0) /* 0-15 */

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/* Return error codes fsp */
typedef enum e_fsp_err
{
    FSP_SUCCESS = 0,

    /* Start of Crypto specific (0x10000) @note Refer to sf_cryoto_err.h for Crypto error code. */
    FSP_ERR_CRYPTO_CONTINUE              = 0x10000,  ///< Continue executing function
    FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT = 0x10001,  ///< Hardware resource busy
    FSP_ERR_CRYPTO_SCE_FAIL              = 0x10002,  ///< Internal I/O buffer is not empty
    FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX = 0x10003,  ///< Invalid index
    FSP_ERR_CRYPTO_SCE_RETRY             = 0x10004,  ///< Retry
    FSP_ERR_CRYPTO_SCE_VERIFY_FAIL       = 0x10005,  ///< Verify is failed
    FSP_ERR_CRYPTO_SCE_ALREADY_OPEN      = 0x10006,  ///< HW SCE module is already opened
    FSP_ERR_CRYPTO_NOT_OPEN              = 0x10007,  ///< Hardware module is not initialized
    FSP_ERR_CRYPTO_UNKNOWN               = 0x10008,  ///< Some unknown error occurred
    FSP_ERR_CRYPTO_NULL_POINTER          = 0x10009,  ///< Null pointer input as a parameter
    FSP_ERR_CRYPTO_NOT_IMPLEMENTED       = 0x1000a,  ///< Algorithm/size not implemented
    FSP_ERR_CRYPTO_RNG_INVALID_PARAM     = 0x1000b,  ///< An invalid parameter is specified
    FSP_ERR_CRYPTO_RNG_FATAL_ERROR       = 0x1000c,  ///< A fatal error occurred
    FSP_ERR_CRYPTO_INVALID_SIZE          = 0x1000d,  ///< Size specified is invalid
    FSP_ERR_CRYPTO_INVALID_STATE         = 0x1000e,  ///< Function used in an valid state
    FSP_ERR_CRYPTO_ALREADY_OPEN          = 0x1000f,  ///< control block is already opened
    FSP_ERR_CRYPTO_INSTALL_KEY_FAILED    = 0x10010,  ///< Specified input key is invalid.
    FSP_ERR_CRYPTO_AUTHENTICATION_FAILED = 0x10011,  ///< Authentication failed
    FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      = 0x10012,  ///< Failure to Init Cipher
    FSP_ERR_CRYPTO_SCE_AUTHENTICATION    = 0x10013,  ///< Authentication failed
    FSP_ERR_CRYPTO_SCE_PARAMETER         = 0x10014,  ///< Input date is illegal.
    FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION = 0x10015,  ///< An invalid function call occurred.

    /* Start of SF_CRYPTO specific */
    FSP_ERR_CRYPTO_COMMON_NOT_OPENED      = 0x20000, ///< Crypto Framework Common is not opened
    FSP_ERR_CRYPTO_HAL_ERROR              = 0x20001, ///< Cryoto HAL module returned an error
    FSP_ERR_CRYPTO_KEY_BUF_NOT_ENOUGH     = 0x20002, ///< Key buffer size is not enough to generate a key
    FSP_ERR_CRYPTO_BUF_OVERFLOW           = 0x20003, ///< Attempt to write data larger than what the buffer can hold
    FSP_ERR_CRYPTO_INVALID_OPERATION_MODE = 0x20004, ///< Invalid operation mode.
    FSP_ERR_MESSAGE_TOO_LONG              = 0x20005, ///< Message for RSA encryption is too long.
    FSP_ERR_RSA_DECRYPTION_ERROR          = 0x20006, ///< RSA Decryption error.
} fsp_err_t;

/** Data lifecycle */
typedef enum
{
    SCE_CM = 1,
    SCE_SSD,
    SCE_NSECSD,
    SCE_DPL,
    SCE_LCK_DBG,
    SCE_LCK_BOOT,
    SCE_RMA_REQ,
    SCE_RMA_ACK,
} lifecycle_t;

/** Byte data structure */
typedef struct sce_byte_data
{
        uint8_t * pdata;                           ///< pointer
        uint32_t  data_length;                     ///< data_length
        uint32_t  data_type;                       ///< data type
} sce_byte_data_t;

/** RSA byte data structure */
typedef sce_byte_data_t sce_rsa_byte_data_t;   ///< byte data

/** ECDSA byte data structure */
typedef sce_byte_data_t sce_ecdsa_byte_data_t; ///< byte data

/** AES wrapped key data structure. DO NOT MODIFY. */
typedef struct sce_aes_wrapped_key
{
        uint32_t type;                                     ///< key type

        /* AES128, AES256 are supported */
        uint32_t value[HW_SCE_AES256_KEY_INDEX_WORD_SIZE]; ///< wrapped key value
} sce_aes_wrapped_key_t;

/** RSA 1024bit public wrapped key data structure. DO NOT MODIFY. */
typedef struct sce_rsa1024_public_wrapped_key
{
        uint32_t type;                                                                            ///< key type
        struct
        {
                /* key management information */
                uint32_t key_management_info1[HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE];
                /* RSA 1024-bit public key n (plaintext) */
                uint8_t  key_n[HW_SCE_RSA_1024_KEY_N_LENGTH_BYTE_SIZE];
                /* RSA 1024-bit public key e (plaintext) */
                uint8_t  key_e[HW_SCE_RSA_1024_KEY_E_LENGTH_BYTE_SIZE];
                /* dummy */
                uint8_t  dummy[HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE];
                /* key management information */
                uint32_t key_management_info2[HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE];
        } value;
} sce_rsa1024_public_wrapped_key_t;

/** RSA 1024bit private wrapped key data structure. DO NOT MODIFY. */
typedef struct sce_rsa1024_private_wrapped_key
{
        uint32_t type;                                                                             ///< key type
        struct
        {
                /* key management information */
                uint32_t key_management_info1[HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE];
                /* RSA 1024-bit private key n (plaintext) */
                uint8_t  key_n[HW_SCE_RSA_1024_KEY_N_LENGTH_BYTE_SIZE];
                /* key management information */
                uint32_t key_management_info2[HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE];
        } value;
} sce_rsa1024_private_wrapped_key_t;

/** RSA 2048bit public wrapped key data structure. DO NOT MODIFY. */
typedef struct sce_rsa2048_public_wrapped_key
{
        uint32_t type;                                                                            ///< Key type
        struct
        {
                /* key management information */
                uint32_t key_management_info1[HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE];
                /* RSA 2048-bit public key n (plaintext) */
                uint8_t  key_n[HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE];
                /* RSA 2048-bit public key e (plaintext) */
                uint8_t  key_e[HW_SCE_RSA_2048_KEY_E_LENGTH_BYTE_SIZE];
                /* dummy */
                uint8_t  dummy[HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE];
                /* key management information */
                uint32_t key_management_info2[HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE];
        } value;
} sce_rsa2048_public_wrapped_key_t;

/** RSA 2048bit private wrapped key data structure. DO NOT MODIFY. */
typedef struct sce_rsa2048_private_wrapped_key
{
        uint32_t type;                                                                             ///< key type
        struct
        {
                /* key management information */
                uint32_t key_management_info1[HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE];
                /* RSA 2048-bit private key n (plaintext) */
                uint8_t  key_n[HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE];
                /* key management information */
                uint32_t key_management_info2[HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE];
        } value;
} sce_rsa2048_private_wrapped_key_t;

/** RSA 4096bit public wrapped key data structure. DO NOT MODIFY. */
typedef struct sce_rsa4096_public_wrapped_key
{
        uint32_t type;                                                                            ///< Key type
        struct
        {
                /* key management information */
                uint32_t key_management_info1[HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE];
                /* RSA 4096-bit public key n (plaintext) */
                uint8_t  key_n[HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE];
                /* RSA 4096-bit public key e (plaintext) */
                uint8_t  key_e[HW_SCE_RSA_4096_KEY_E_LENGTH_BYTE_SIZE];
                /* dummy */
                uint8_t  dummy[HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE];
                /* key management information */
                uint32_t key_management_info2[HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE];
        } value;
} sce_rsa4096_public_wrapped_key_t;

/** RSA 1024bit wrapped key pair structure. DO NOT MODIFY. */
typedef struct sce_rsa1024_wrapped_pair_key
{
        sce_rsa1024_private_wrapped_key_t priv_key; ///< RSA 1024-bit private wrapped key
        sce_rsa1024_public_wrapped_key_t pub_key;   ///< RSA 1024-bit public wrapped key
} sce_rsa1024_wrapped_pair_key_t;

/** RSA 2048bit wrapped key pair structure. DO NOT MODIFY. */
typedef struct sce_rsa2048_wrapped_pair_key
{
        sce_rsa2048_private_wrapped_key_t priv_key; ///< RSA 2048-bit private wrapped key
        sce_rsa2048_public_wrapped_key_t pub_key;   ///< RSA 2048-bit public wrapped key
} sce_rsa2048_wrapped_pair_key_t;

/** ECC P-192/224/256/512 public wrapped key data structure */
typedef struct sce_ecc_public_wrapped_key
{
        uint32_t type;                                                    ///< key type
        struct
        {
                /* key management information */
                uint32_t key_management_info[HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO_WORD_SIZE];
                /* ECC public key Q (plaintext) */
                uint8_t  key_q[HW_SCE_ECC_KEY_LENGTH_BYTE_SIZE];
        } value;
} sce_ecc_public_wrapped_key_t;

/** ECC P-192/224/256/512 private wrapped key data structure */
typedef struct sce_ecc_private_wrapped_key
{
        uint32_t type;                                                    ///< key type
        uint32_t value[HW_SCE_ECC_PRIVATE_KEY_MANAGEMENT_INFO_WORD_SIZE]; ///< wrapped key value
} sce_ecc_private_wrapped_key_t;

/** ECC P-192/224/256 wrapped key pair structure */
typedef struct sce_ecc_wrapped_pair_key
{
        sce_ecc_private_wrapped_key_t priv_key; ///< ECC private wrapped key
        sce_ecc_public_wrapped_key_t pub_key;   ///< ECC public wrapped key
} sce_ecc_wrapped_pair_key_t;

/** Update key ring index data structure. DO NOT MODIFY. */
typedef struct sce_key_update_key
{
        uint32_t type;                                          ///< key type
        uint32_t value[HW_SCE_UPDATE_KEY_RING_INDEX_WORD_SIZE]; ///< wrapped key value
} sce_key_update_key_t;

/** The work area for AES. DO NOT MODIFY. */
typedef struct sce_aes_handle
{
        /* serial number of this handle */
        uint32_t              id;
        /* wrapped key */
        sce_aes_wrapped_key_t wrapped_key;
        /* text size under encryption / decryption */
        uint32_t              current_input_data_size;
        /* text array less than the block long */
        uint8_t               last_1_block_as_fraction[HW_SCE_AES_BLOCK_BYTE_SIZE];
        /* reserved */
        uint8_t               last_2_block_as_fraction[HW_SCE_AES_BLOCK_BYTE_SIZE * 2];
        /* current initialization vector used in CBC/CTR mode */
        uint8_t               current_initial_vector[HW_SCE_AES_CBC_IV_BYTE_SIZE];
        /* control flag of calling function */
        uint8_t               flag_call_init;
} sce_aes_handle_t;

/** The work area for CMAC. DO NOT MODIFY. */
typedef struct sce_cmac_handle
{
        uint32_t              id;                                      ///< serial number of this handle
        sce_aes_wrapped_key_t wrapped_key;                             ///< wrapped key
        uint8_t               cmac_buffer[HW_SCE_AES_BLOCK_BYTE_SIZE]; ///< message array less than the block long
        uint32_t              all_received_length;                     ///< entire length of message
        /* message array length less than the block long */
        uint32_t              buffering_length;
        uint8_t               flag_call_init;                          ///< control flag of calling function
} sce_cmac_handle_t;

/** The work area for SHA. DO NOT MODIFY. */
typedef struct sce_sha_md5_handle
{
        uint32_t id;                                                 ///< serial number of this handle
        uint8_t  sha_buffer[HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE * 4];///< message array length less than the block long
        uint32_t all_received_length;                                ///< entire length of message
        uint32_t buffering_length;                                   ///< message array length less than the block long

        /* SHA1(20byte), SHA256(32byte), MD5(16byte) are supported */
        uint8_t current_hash[HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE];    ///< last hash value
        uint8_t flag_call_init;                                       ///< control flag of calling function
} sce_sha_md5_handle_t;

/** SCE Control block. Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - sce_instance_ctrl_t
 */
typedef void sce_ctrl_t;

/** User configuration structure, used in open function */
typedef struct st_sce_cfg
{
        lifecycle_t lifecycle;             ///< Data lifecycle
} sce_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_sce_api
{
        /** Enables use of SCE functionality.
         * @par Implemented as
         * - @ref R_SCE_Open()
         *
         * @param[in]     p_ctrl       Pointer to control structure.
         * @param[in]     p_cfg        Pointer to pin configuration structure.
         */

        /***** TODO: Replace "struct st_sce_ctrl" to  "void" *****/
        fsp_err_t (* open)(sce_ctrl_t * const p_ctrl, sce_cfg_t const * const p_cfg);

        /** Stops supply of power to the SCE.
         * @par Implemented as
         * - @ref R_SCE_Close()
         *
         * @param[in]     p_ctrl       Pointer to control structure.
         */
        fsp_err_t (* close)(sce_ctrl_t * const p_ctrl);

        /** Software reset to SCE.
         * @par Implemented as
         * - @ref R_SCE_SoftwareReset()
         *
         */
        fsp_err_t (* softwareReset)(void);

        /** Generates 4 words random number.
         * @par Implemented as
         * - @ref R_SCE_RandomNumberGenerate()
         *
         * @param[in,out] random Stores 4words (16 bytes) random data.
         */
        fsp_err_t (* randomNumberGenerate)(uint32_t * random);

        /** This API outputs 128-bit AES wrapped key.
         * @par Implemented as
         * - @ref R_SCE_AES128_WrappedKeyGenerate()
         *
         * @param[in,out] wrapped_key 128-bit AES wrapped key
         */
        fsp_err_t (* AES128_WrappedKeyGenerate)(sce_aes_wrapped_key_t * wrapped_key);

        /** This API outputs 256-bit AES wrapped key.
         * @par Implemented as
         * - @ref R_SCE_AES256_WrappedKeyGenerate()
         *
         * @param[in,out] wrapped_key 256-bit AES wrapped key
         */
        fsp_err_t (* AES256_WrappedKeyGenerate)(sce_aes_wrapped_key_t * wrapped_key);

        /** This API outputs 128-bit AES wrapped key.
         * @par Implemented as
         * - @ref R_SCE_AES128_EncryptedKeyWrap()
         *
         * @param[in]     initial_vector Initialization vector when generating encrypted_key
         * @param[in]     encrypted_key  User key encryptedand MAC appended
         * @param[in]     key_update_key Key update keyring
         * @param[in,out] wrapped_key    128-bit AES wrapped key
         */
        fsp_err_t (* AES128_EncryptedKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key, sce_aes_wrapped_key_t * wrapped_key);

        /** This API outputs 256-bit AES wrapped key.
         * @par Implemented as
         * - @ref R_SCE_AES256_EncryptedKeyWrap()
         *
         * @param[in]     initial_vector Initialization vector when generating encrypted_key
         * @param[in]     encrypted_key  User key encryptedand MAC appended
         * @param[in]     key_update_key Key update keyring
         * @param[in,out] wrapped_key    256-bit AES wrapped key
         */
        fsp_err_t (* AES256_EncryptedKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key, sce_aes_wrapped_key_t * wrapped_key);

        /** Initialize AES128ECB encryption.
         * @par Implemented as
         * - @ref R_SCE_AES128ECB_EncryptInit()
         *
         * @param[in,out] handle      AES handler (work area)
         * @param[in]     wrapped_key 128-bit AES wrapped key
         */
        fsp_err_t (* AES128ECB_EncryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);

        /** Update AES128ECB encryption.
         * @par Implemented as
         * - @ref R_SCE_AES128ECB_EncryptUpdate()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in]     plain        plaintext data area
         * @param[in,out] cipher       ciphertext data area
         * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES128ECB_EncryptUpdate)(sce_aes_handle_t * handle, uint8_t * plain, uint8_t * cipher,
                uint32_t plain_length);

        /** Finalize AES128ECB encryption.
         * @par Implemented as
         * - @ref R_SCE_AES128ECB_EncryptFinal()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in,out] cipher        ciphertext data area (nothing ever written here)
         * @param[in,out] cipher_length ciphertext data length (0 always written here)
         */
        fsp_err_t (* AES128ECB_EncryptFinal)(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);

        /** Initialize AES128ECB decryption.
         * @par Implemented as
         * - @ref R_SCE_AES128ECB_DecryptInit()
         *
         * @param[in,out] handle      AES handler (work area)
         * @param[in]     wrapped_key 128-bit AES wrapped key
         */
        fsp_err_t (* AES128ECB_DecryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);

        /** Update AES128ECB decryption.
         * @par Implemented as
         * - @ref R_SCE_AES128ECB_DecryptUpdate()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in]     cipher        ciphertext data area
         * @param[in,out] plain         plaintext data area
         * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES128ECB_DecryptUpdate)(sce_aes_handle_t * handle, uint8_t * cipher, uint8_t * plain,
                uint32_t cipher_length);

        /** Finalize AES128ECB decryption.
         * @par Implemented as
         * - @ref R_SCE_AES128ECB_DecryptFinal()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in,out] plain        plaintext data area (nothing ever written here)
         * @param[in,out] plain_length plaintext data length (0 always written here)
         */
        fsp_err_t (* AES128ECB_DecryptFinal)(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);

        /** Initialize AES256ECB encryption.
         * @par Implemented as
         * - @ref R_SCE_AES256ECB_EncryptInit()
         *
         * @param[in,out] handle      AES handler (work area)
         * @param[in]     wrapped_key 256-bit AES wrapped key
         */
        fsp_err_t (* AES256ECB_EncryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);

        /** Update AES256ECB encryption.
         * @par Implemented as
         * - @ref R_SCE_AES256ECB_EncryptUpdate()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in]     plain        plaintext data area
         * @param[in,out] cipher       ciphertext data area
         * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES256ECB_EncryptUpdate)(sce_aes_handle_t * handle, uint8_t * plain, uint8_t * cipher,
                uint32_t plain_length);

        /** Finalize AES256ECB encryption.
         * @par Implemented as
         * - @ref R_SCE_AES256ECB_EncryptFinal()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in,out] cipher        ciphertext data area (nothing ever written here)
         * @param[in,out] cipher_length ciphertext data length (0 always written here)
         */
        fsp_err_t (* AES256ECB_EncryptFinal)(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);

        /** Initialize AES256ECB decryption.
         * @par Implemented as
         * - @ref R_SCE_AES256ECB_DecryptInit()
         *
         * @param[in,out] handle      AES handler (work area)
         * @param[in]     wrapped_key 256-bit AES wrapped key
         */
        fsp_err_t (* AES256ECB_DecryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);

        /** Update AES256ECB decryption.
         * @par Implemented as
         * - @ref R_SCE_AES256ECB_DecryptUpdate()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in]     cipher        ciphertext data area
         * @param[in,out] plain         plaintext data area
         * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES256ECB_DecryptUpdate)(sce_aes_handle_t * handle, uint8_t * cipher, uint8_t * plain,
                uint32_t cipher_length);

        /** Finalize AES256ECB decryption.
         * @par Implemented as
         * - @ref R_SCE_AES256ECB_DecryptFinal()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in,out] plain        plaintext data area (nothing ever written here)
         * @param[in,out] plain_length plaintext data length (0 always written here)
         */
        fsp_err_t (* AES256ECB_DecryptFinal)(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);

        /** Initialize AES128CBC encryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CBC_EncryptInit()
         *
         * @param[in,out] handle         AES handler (work area)
         * @param[in]     wrapped_key    128-bit AES wrapped key
         * @param[in]     initial_vector initial vector area (16byte)
         */
        fsp_err_t (* AES128CBC_EncryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key,
                uint8_t * initial_vector);

        /** Update AES128CBC encryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CBC_EncryptUpdate()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in]     plain        plaintext data area
         * @param[in,out] cipher       ciphertext data area
         * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES128CBC_EncryptUpdate)(sce_aes_handle_t * handle, uint8_t * plain, uint8_t * cipher,
                uint32_t plain_length);

        /** Finalize AES128CBC encryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CBC_EncryptFinal()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in,out] cipher        ciphertext data area (nothing ever written here)
         * @param[in,out] cipher_length ciphertext data length (0 always written here)
         */
        fsp_err_t (* AES128CBC_EncryptFinal)(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);

        /** Initialize AES128CBC decryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CBC_DecryptInit()
         *
         * @param[in,out] handle         AES handler (work area)
         * @param[in]     wrapped_key    128-bit AES wrapped key
         * @param[in]     initial_vector initial vector area (16byte)
         */
        fsp_err_t (* AES128CBC_DecryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key,
                uint8_t * initial_vector);

        /** Update AES128CBC decryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CBC_DecryptUpdate()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in]     cipher        ciphertext data area
         * @param[in,out] plain         plaintext data area
         * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES128CBC_DecryptUpdate)(sce_aes_handle_t * handle, uint8_t * cipher, uint8_t * plain,
                uint32_t cipher_length);

        /** Finalize AES128CBC decryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CBC_DecryptFinal()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in,out] plain        plaintext data area (nothing ever written here)
         * @param[in,out] plain_length plaintext data length (0 always written here)
         */
        fsp_err_t (* AES128CBC_DecryptFinal)(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);

        /** Initialize AES256CBC encryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CBC_EncryptInit()
         *
         * @param[in,out] handle         AES handler (work area)
         * @param[in]     wrapped_key    256-bit AES wrapped key
         * @param[in]     initial_vector initial vector area (16byte)
         */
        fsp_err_t (* AES256CBC_EncryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key,
                uint8_t * initial_vector);

        /** Update AES256CBC encryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CBC_EncryptUpdate()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in]     plain        plaintext data area
         * @param[in,out] cipher       ciphertext data area
         * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES256CBC_EncryptUpdate)(sce_aes_handle_t * handle, uint8_t * plain, uint8_t * cipher,
                uint32_t plain_length);

        /** Finalize AES256CBC encryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CBC_EncryptFinal()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in,out] cipher        ciphertext data area (nothing ever written here)
         * @param[in,out] cipher_length ciphertext data length (0 always written here)
         */
        fsp_err_t (* AES256CBC_EncryptFinal)(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);

        /** Initialize AES256CBC decryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CBC_DecryptInit()
         *
         * @param[in,out] handle         AES handler (work area)
         * @param[in]     wrapped_key    256-bit AES wrapped key
         * @param[in]     initial_vector initial vector area (16byte)
         */
        fsp_err_t (* AES256CBC_DecryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key,
                uint8_t * initial_vector);

        /** Update AES256CBC decryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CBC_DecryptUpdate()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in]     cipher        ciphertext data area
         * @param[in,out] plain         plaintext data area
         * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES256CBC_DecryptUpdate)(sce_aes_handle_t * handle, uint8_t * cipher, uint8_t * plain,
                uint32_t cipher_length);

        /** Finalize AES256CBC decryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CBC_DecryptFinal()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in,out] plain        plaintext data area (nothing ever written here)
         * @param[in,out] plain_length plaintext data length (0 always written here)
         */
        fsp_err_t (* AES256CBC_DecryptFinal)(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);

        /** Initialize AES128CTR encryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CTR_EncryptInit()
         *
         * @param[in,out] handle         AES handler (work area)
         * @param[in]     wrapped_key    128-bit AES wrapped key
         * @param[in]     initial_vector initial vector area (16byte)
         */
        fsp_err_t (* AES128CTR_EncryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key,
                uint8_t * initial_vector);

        /** Update AES128CTR encryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CTR_EncryptUpdate()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in]     plain        plaintext data area
         * @param[in,out] cipher       ciphertext data area
         * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES128CTR_EncryptUpdate)(sce_aes_handle_t * handle, uint8_t * plain, uint8_t * cipher,
                uint32_t plain_length);

        /** Finalize AES128CTR encryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CTR_EncryptFinal()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in,out] cipher        ciphertext data area (nothing ever written here)
         * @param[in,out] cipher_length ciphertext data length (0 always written here)
         */
        fsp_err_t (* AES128CTR_EncryptFinal)(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);

        /** Initialize AES128CTR decryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CTR_DecryptInit()
         *
         * @param[in,out] handle         AES handler (work area)
         * @param[in]     wrapped_key    128-bit AES wrapped key
         * @param[in]     initial_vector initial vector area (16byte)
         */
        fsp_err_t (* AES128CTR_DecryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key,
                uint8_t * initial_vector);

        /** Update AES128CTR decryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CTR_DecryptUpdate()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in]     cipher        ciphertext data area
         * @param[in,out] plain         plaintext data area
         * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES128CTR_DecryptUpdate)(sce_aes_handle_t * handle, uint8_t * cipher, uint8_t * plain,
                uint32_t cipher_length);

        /** Finalize AES128CTR decryption.
         * @par Implemented as
         * - @ref R_SCE_AES128CTR_DecryptFinal()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in,out] plain        plaintext data area (nothing ever written here)
         * @param[in,out] plain_length plaintext data length (0 always written here)
         */
        fsp_err_t (* AES128CTR_DecryptFinal)(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);

        /** Initialize AES256CTR encryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CTR_EncryptInit()
         *
         * @param[in,out] handle         AES handler (work area)
         * @param[in]     wrapped_key    256-bit AES wrapped key
         * @param[in]     initial_vector initial vector area (16byte)
         */
        fsp_err_t (* AES256CTR_EncryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key,
                uint8_t * initial_vector);

        /** Update AES256CTR encryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CTR_EncryptUpdate()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in]     plain        plaintext data area
         * @param[in,out] cipher       ciphertext data area
         * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES256CTR_EncryptUpdate)(sce_aes_handle_t * handle, uint8_t * plain, uint8_t * cipher,
                uint32_t plain_length);

        /** Finalize AES256CTR encryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CTR_EncryptFinal()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in,out] cipher        ciphertext data area (nothing ever written here)
         * @param[in,out] cipher_length ciphertext data length (0 always written here)
         */
        fsp_err_t (* AES256CTR_EncryptFinal)(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);

        /** Initialize AES256CTR decryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CTR_DecryptInit()
         *
         * @param[in,out] handle         AES handler (work area)
         * @param[in]     wrapped_key    256-bit AES wrapped key
         * @param[in]     initial_vector initial vector area (16byte)
         */
        fsp_err_t (* AES256CTR_DecryptInit)(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key,
                uint8_t * initial_vector);

        /** Update AES256CTR decryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CTR_DecryptUpdate()
         *
         * @param[in,out] handle        AES handler (work area)
         * @param[in]     cipher        ciphertext data area
         * @param[in,out] plain         plaintext data area
         * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
         */
        fsp_err_t (* AES256CTR_DecryptUpdate)(sce_aes_handle_t * handle, uint8_t * cipher, uint8_t * plain,
                uint32_t cipher_length);

        /** Finalize AES256CTR decryption.
         * @par Implemented as
         * - @ref R_SCE_AES256CTR_DecryptFinal()
         *
         * @param[in,out] handle       AES handler (work area)
         * @param[in,out] plain        plaintext data area (nothing ever written here)
         * @param[in,out] plain_length plaintext data length (0 always written here)
         */
        fsp_err_t (* AES256CTR_DecryptFinal)(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);

        /** Initialize AES128CMAC generation.
         * @par Implemented as
         * - @ref R_SCE_AES128CMAC_GenerateInit()
         *
         * @param[in,out] handle      AES-CMAC handler (work area)
         * @param[in]     wrapped_key 128-bit AES wrapped key
         */
        fsp_err_t (* AES128CMAC_GenerateInit)(sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);

        /** Update AES128CMAC generation.
         * @par Implemented as
         * - @ref R_SCE_AES128CMAC_GenerateUpdate()
         *
         * @param[in,out] handle         AES-CMAC handler (work area)
         * @param[in]     message        message data area (message_length byte)
         * @param[in]     message_length message data length (0 or more bytes)
         */
        fsp_err_t (* AES128CMAC_GenerateUpdate)(sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length);

        /** Finalize AES128CMAC generation.
         * @par Implemented as
         * - @ref R_SCE_AES128CMAC_GenerateFinal()
         *
         * @param[in,out] handle AES-CMAC handler (work area)
         * @param[in,out] mac    MAC data area (16byte)
         */
        fsp_err_t (* AES128CMAC_GenerateFinal)(sce_cmac_handle_t * handle, uint8_t * mac);

        /** Initialize AES128CMAC verification.
         * @par Implemented as
         * - @ref R_SCE_AES128CMAC_VerifyInit()
         *
         * @param[in,out] handle      AES-CMAC handler (work area)
         * @param[in]     wrapped_key 128-bit AES wrapped key
         */
        fsp_err_t (* AES128CMAC_VerifyInit)(sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);

        /** Update AES128CMAC verification.
         * @par Implemented as
         * - @ref R_SCE_AES128CMAC_VerifyUpdate()
         *
         * @param[in,out] handle         AES-CMAC handler (work area)
         * @param[in]     message        message data area (message_length byte)
         * @param[in]     message_length message data length (0 or more bytes)
         */
        fsp_err_t (* AES128CMAC_VerifyUpdate)(sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length);

        /** Finalize AES128CMAC verification.
         * @par Implemented as
         * - @ref R_SCE_AES128CMAC_VerifyFinal()
         *
         * @param[in,out] handle     AES-CMAC handler (work area)
         * @param[in,out] mac        MAC data area (mac_length byte)
         * @param[in,out] mac_length MAC data length (2 to 16 bytes)
         */
        fsp_err_t (* AES128CMAC_VerifyFinal)(sce_cmac_handle_t * handle, uint8_t * mac, uint32_t mac_length);

        /** Initialize AES256CMAC generation.
         * @par Implemented as
         * - @ref R_SCE_AES256CMAC_GenerateInit()
         *
         * @param[in,out] handle      AES-CMAC handler (work area)
         * @param[in]     wrapped_key 256-bit AES wrapped key
         */
        fsp_err_t (* AES256CMAC_GenerateInit)(sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);

        /** Update AES256CMAC generation.
         * @par Implemented as
         * - @ref R_SCE_AES256CMAC_GenerateUpdate()
         *
         * @param[in,out] handle         AES-CMAC handler (work area)
         * @param[in]     message        message data area (message_length byte)
         * @param[in]     message_length message data length (0 or more bytes)
         */
        fsp_err_t (* AES256CMAC_GenerateUpdate)(sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length);

        /** Finalize AES256CMAC generation.
         * @par Implemented as
         * - @ref R_SCE_AES256CMAC_GenerateFinal()
         *
         * @param[in,out] handle AES-CMAC handler (work area)
         * @param[in,out] mac    MAC data area (16byte)
         */
        fsp_err_t (* AES256CMAC_GenerateFinal)(sce_cmac_handle_t * handle, uint8_t * mac);

        /** Initialize AES256CMAC verification.
         * @par Implemented as
         * - @ref R_SCE_AES256CMAC_VerifyInit()
         *
         * @param[in,out] handle      AES-CMAC handler (work area)
         * @param[in]     wrapped_key 256-bit AES wrapped key
         */
        fsp_err_t (* AES256CMAC_VerifyInit)(sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);

        /** Update AES256CMAC verification.
         * @par Implemented as
         * - @ref R_SCE_AES256CMAC_VerifyUpdate()
         *
         * @param[in,out] handle         AES-CMAC handler (work area)
         * @param[in]     message        message data area (message_length byte)
         * @param[in]     message_length message data length (0 or more bytes)
         */
        fsp_err_t (* AES256CMAC_VerifyUpdate)(sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length);

        /** Finalize AES256CMAC verification.
         * @par Implemented as
         * - @ref R_SCE_AES256CMAC_VerifyFinal()
         *
         * @param[in,out] handle     AES-CMAC handler (work area)
         * @param[in,out] mac        MAC data area (mac_length byte)
         * @param[in,out] mac_length MAC data length (2 to 16 bytes)
         */
        fsp_err_t (* AES256CMAC_VerifyFinal)(sce_cmac_handle_t * handle, uint8_t * mac, uint32_t mac_length);

        /** Initialize SHA-256 Calculation.
         * @par Implemented as
         * - @ref R_SCE_SHA256_Init()
         *
         * @param[in,out] handle SHA handler (work area)
         */
        fsp_err_t (* SHA256_Init)(sce_sha_md5_handle_t * handle);

        /** Update SHA-256 Calculation.
         * @par Implemented as
         * - @ref R_SCE_SHA256_Update()
         *
         * @param[in,out] handle         SHA handler (work area)
         * @param[in]     message        message data area
         * @param[in]     message_length message data length
         */
        fsp_err_t (* SHA256_Update)(sce_sha_md5_handle_t * handle, uint8_t * message, uint32_t message_length);

        /** Finalize SHA-256 Calculation.
         * @par Implemented as
         * - @ref R_SCE_SHA256_Final()
         *
         * @param[in,out] handle        SHA handler (work area)
         * @param[in,out] digest        hasha data area
         * @param[in,out] digest_length hash data length (32bytes)
         */
        fsp_err_t (* SHA256_Final)(sce_sha_md5_handle_t * handle, uint8_t * digest, uint32_t * digest_length);

        /** Initialize SHA-224 Calculation.
         * @par Implemented as
         * - @ref R_SCE_SHA224_Init()
         *
         * @param[in,out] handle SHA handler (work area)
         */
        fsp_err_t (* SHA224_Init)(sce_sha_md5_handle_t * handle);

        /** Update SHA-224 Calculation.
         * @par Implemented as
         * - @ref R_SCE_SHA224_Update()
         *
         * @param[in,out] handle         SHA handler (work area)
         * @param[in]     message        message data area
         * @param[in]     message_length message data length
         */
        fsp_err_t (* SHA224_Update)(sce_sha_md5_handle_t * handle, uint8_t * message, uint32_t message_length);

        /** Finalize SHA-224 Calculation.
         * @par Implemented as
         * - @ref R_SCE_SHA224_Final()
         *
         * @param[in,out] handle        SHA handler (work area)
         * @param[in,out] digest        hasha data area
         * @param[in,out] digest_length hash data length (32bytes)
         */
        fsp_err_t (* SHA224_Final)(sce_sha_md5_handle_t * handle, uint8_t * digest, uint32_t * digest_length);

        /** This API outputs 1024-bit RSA wrapped pair key.
         * @par Implemented as
         * - @ref R_SCE_RSA1024_WrappedKeyPairGenerate()
         *
         * @param[in,out] wrapped_key 128-bit AES wrapped key
         */
        fsp_err_t (* RSA1024_WrappedKeyPairGenerate)(sce_rsa1024_wrapped_pair_key_t * wrapped_pair_key);

        /** This API outputs 2048-bit RSA wrapped pair key.
         * @par Implemented as
         * - @ref R_SCE_RSA2048_WrappedKeyPairGenerate()
         *
         * @param[in,out] wrapped_key 128-bit AES wrapped key
         */
        fsp_err_t (* RSA2048_WrappedKeyPairGenerate)(sce_rsa2048_wrapped_pair_key_t * wrapped_pair_key);

        /** This API outputs 1024-bit RSA public wrapped key.
         * @par Implemented as
         * - @ref R_SCE_RSA1024_EncryptedPublicKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key 1024-bit RSA public wrapped key
         */
        fsp_err_t (* RSA1024_EncryptedPublicKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_rsa1024_public_wrapped_key_t * wrapped_key);

        /** This API outputs 1024-bit RSA private wrapped key.
         * @par Implemented as
         * - @ref R_SCE_RSA1024_EncryptedPrivateKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key 1024-bit RSA private wrapped key
         */
        fsp_err_t (* RSA1024_EncryptedPrivateKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_rsa1024_private_wrapped_key_t * wrapped_key);

        /** This API outputs 2048-bit RSA public wrapped key.
         * @par Implemented as
         * - @ref R_SCE_RSA2048_EncryptedPublicKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key 2048-bit RSA public wrapped key
         */
        fsp_err_t (* RSA2048_EncryptedPublicKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_rsa2048_public_wrapped_key_t * wrapped_key);

        /** This API outputs 2048-bit RSA private wrapped key.
         * @par Implemented as
         * - @ref R_SCE_RSA2048_EncryptedPrivateKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key 2048-bit RSA private wrapped key
         */
        fsp_err_t (* RSA2048_EncryptedPrivateKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_rsa2048_private_wrapped_key_t * wrapped_key);

        /** This API outputs 4096-bit RSA public wrapped key.
         * @par Implemented as
         * - @ref R_SCE_RSA4096_EncryptedPublicKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key 4096-bit RSA public wrapped key
         */
        fsp_err_t (* RSA4096_EncryptedPublicKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_rsa4096_public_wrapped_key_t * wrapped_key);

        /** RSASSA-PKCS1-V1_5 signature generation.
         * @par Implemented as
         * - @ref R_SCE_RSASSA_PKCS1024_SignatureGenerate()
         *
         * @param[in]     message_hash Message or hash value to which to attach signature
         * @param[in,out] signature    Signature text storage destination information
         * @param[in]     wrapped_key  Inputs the 1024-bit RSA private wrapped key.
         * @param[in]     hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
         */
        fsp_err_t (* RSASSA_PKCS1024_SignatureGenerate)(sce_rsa_byte_data_t * message_hash,
                sce_rsa_byte_data_t * signature, sce_rsa1024_private_wrapped_key_t * wrapped_key, uint8_t hash_type);

        /** RSASSA-PKCS1-V1_5 signature generation.
         * @par Implemented as
         * - @ref R_SCE_RSASSA_PKCS2048_SignatureGenerate()
         *
         * @param[in]     message_hash Message or hash value to which to attach signature
         * @param[in,out] signature    Signature text storage destination information
         * @param[in]     wrapped_key  Inputs the 2048-bit RSA private wrapped key.
         * @param[in]     hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
         */
        fsp_err_t (* RSASSA_PKCS2048_SignatureGenerate)(sce_rsa_byte_data_t * message_hash,
                sce_rsa_byte_data_t * signature, sce_rsa2048_private_wrapped_key_t * wrapped_key, uint8_t hash_type);

        /** RSASSA-PKCS1-V1_5 signature verification.
         * @par Implemented as
         * - @ref R_SCE_RSASSA_PKCS1024_SignatureVerify()
         *
         * @param[in] signature    Signature text information to verify
         * @param[in] message_hash Message text or hash value to verify
         * @param[in] wrapped_key  Inputs the 1024-bit RSA public wrapped key.
         * @param[in] hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
         */
        fsp_err_t (* RSASSA_PKCS1024_SignatureVerify)(sce_rsa_byte_data_t * signature,
                sce_rsa_byte_data_t * message_hash, sce_rsa1024_public_wrapped_key_t * wrapped_key, uint8_t hash_type);

        /** RSASSA-PKCS1-V1_5 signature verification.
         * @par Implemented as
         * - @ref R_SCE_RSASSA_PKCS2048_SignatureVerify()
         *
         * @param[in] signature    Signature text information to verify
         * @param[in] message_hash Message text or hash value to verify
         * @param[in] wrapped_key  Inputs the 2048-bit RSA public wrapped key.
         * @param[in] hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
         */
        fsp_err_t (* RSASSA_PKCS2048_SignatureVerify)(sce_rsa_byte_data_t * signature,
                sce_rsa_byte_data_t * message_hash, sce_rsa2048_public_wrapped_key_t * wrapped_key, uint8_t hash_type);

        /** RSASSA-PKCS1-V1_5 signature verification.
         * @par Implemented as
         * - @ref R_SCE_RSASSA_PKCS4096_SignatureVerify()
         *
         * @param[in] signature    Signature text information to verify
         * @param[in] message_hash Message text or hash value to verify
         * @param[in] wrapped_key  Inputs the 4096-bit RSA public wrapped key.
         * @param[in] hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
         */
        fsp_err_t (* RSASSA_PKCS4096_SignatureVerify)(sce_rsa_byte_data_t * signature,
                sce_rsa_byte_data_t * message_hash, sce_rsa4096_public_wrapped_key_t * wrapped_key, uint8_t hash_type);

        /** RSAES-PKCS1-V1_5 encryption.
         * @par Implemented as
         * - @ref R_SCE_RSAES_PKCS1024_Encrypt()
         *
         * @param[in]     plain       plaintext
         * @param[in,out] cipher      ciphertext
         * @param[in]     wrapped_key Inputs the 1024-bit RSA public wrapped key.
         */
        fsp_err_t (* RSAES_PKCS1024_Encrypt)(sce_rsa_byte_data_t * plain, sce_rsa_byte_data_t * cipher,
                sce_rsa1024_public_wrapped_key_t * wrapped_key);

        /** RSAES-PKCS1-V1_5 encryption.
         * @par Implemented as
         * - @ref R_SCE_RSAES_PKCS2048_Encrypt()
         *
         * @param[in]     plain       plaintext
         * @param[in,out] cipher      ciphertext
         * @param[in]     wrapped_key Inputs the 2048-bit RSA public wrapped key.
         */
        fsp_err_t (* RSAES_PKCS2048_Encrypt)(sce_rsa_byte_data_t * plain, sce_rsa_byte_data_t * cipher,
                sce_rsa2048_public_wrapped_key_t * wrapped_key);

        /** RSAES-PKCS1-V1_5 encryption.
         * @par Implemented as
         * - @ref R_SCE_RSAES_PKCS4096_Encrypt()
         *
         * @param[in]     plain       plaintext
         * @param[in,out] cipher      ciphertext
         * @param[in]     wrapped_key Inputs the 4096-bit RSA public wrapped key.
         */
        fsp_err_t (* RSAES_PKCS4096_Encrypt)(sce_rsa_byte_data_t * plain, sce_rsa_byte_data_t * cipher,
                sce_rsa4096_public_wrapped_key_t * wrapped_key);

        /** RSAES-PKCS1-V1_5 decryption.
         * @par Implemented as
         * - @ref R_SCE_RSAES_PKCS1024_Decrypt()
         *
         * @param[in]     cipher      ciphertext
         * @param[in,out] plain       plaintext
         * @param[in]     wrapped_key Inputs the 1024-bit RSA private wrapped key.
         */
        fsp_err_t (* RSAES_PKCS1024_Decrypt)(sce_rsa_byte_data_t * cipher, sce_rsa_byte_data_t * plain,
                sce_rsa1024_private_wrapped_key_t * wrapped_key);

        /** RSAES-PKCS1-V1_5 decryption.
         * @par Implemented as
         * - @ref R_SCE_RSAES_PKCS2048_Decrypt()
         *
         * @param[in]     cipher      ciphertext
         * @param[in,out] plain       plaintext
         * @param[in]     wrapped_key Inputs the 2048-bit RSA private wrapped key.
         */
        fsp_err_t (* RSAES_PKCS2048_Decrypt)(sce_rsa_byte_data_t * cipher, sce_rsa_byte_data_t * plain,
                sce_rsa2048_private_wrapped_key_t * wrapped_key);

        /** This API outputs secp192r1 wrapped pair key.
         * @par Implemented as
         * - @ref R_SCE_ECC_secp192r1_WrappedKeyPairGenerate()
         *
         * @param[in,out] wrapped_pair_key Wrapped pair key for secp192r1 public key and private key pair
         */
        fsp_err_t (* ECC_secp192r1_WrappedKeyPairGenerate)(sce_ecc_wrapped_pair_key_t * wrapped_pair_key);

        /** This API outputs secp224r1 wrapped pair key.
         * @par Implemented as
         * - @ref R_SCE_ECC_secp224r1_WrappedKeyPairGenerate()
         *
         * @param[in,out] wrapped_pair_key Wrapped pair key for secp224r1 public key and private key pair
         */
        fsp_err_t (* ECC_secp224r1_WrappedKeyPairGenerate)(sce_ecc_wrapped_pair_key_t * wrapped_pair_key);

        /** This API outputs secp256r1 wrapped pair key.
         * @par Implemented as
         * - @ref R_SCE_ECC_secp256r1_WrappedKeyPairGenerate()
         *
         * @param[in,out] wrapped_pair_key Wrapped pair key for secp256r1 public key and private key pair
         */
        fsp_err_t (* ECC_secp256r1_WrappedKeyPairGenerate)(sce_ecc_wrapped_pair_key_t * wrapped_pair_key);

        /** This API outputs BrainpoolP512r1 wrapped pair key.
         * @par Implemented as
         * - @ref R_SCE_ECC_BrainpoolP512r1_WrappedKeyPairGenerate()
         *
         * @param[in,out] wrapped_pair_key Wrapped pair key for BrainpoolP512r1 public key and private key pair
         */
        fsp_err_t (* ECC_BrainpoolP512r1_WrappedKeyPairGenerate)(sce_ecc_wrapped_pair_key_t * wrapped_pair_key);

        /** This API outputs secp192r1 public wrapped key.
         * @par Implemented as
         * - @ref R_SCE_ECC_secp192r1_EncryptedPublicKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key secp192r1 public wrapped key
         */
        fsp_err_t (* ECC_secp192r1_EncryptedPublicKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_ecc_public_wrapped_key_t * wrapped_key);

        /** This API outputs secp224r1 public wrapped key.
         * @par Implemented as
         * - @ref R_SCE_ECC_secp224r1_EncryptedPublicKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key secp224r1 public wrapped key
         */
        fsp_err_t (* ECC_secp224r1_EncryptedPublicKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_ecc_public_wrapped_key_t * wrapped_key);

        /** This API outputs secp256r1 public wrapped key.
         * @par Implemented as
         * - @ref R_SCE_ECC_secp256r1_EncryptedPublicKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key secp256r1 public wrapped key
         */
        fsp_err_t (* ECC_secp256r1_EncryptedPublicKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_ecc_public_wrapped_key_t * wrapped_key);

        /** This API outputs BrainpoolP512r1 public wrapped key.
         * @par Implemented as
         * - @ref R_SCE_ECC_BrainpoolP512r1_EncryptedPublicKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key BrainpoolP512r1 public wrapped key
         */
        fsp_err_t (* ECC_BrainpoolP512r1_EncryptedPublicKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_ecc_public_wrapped_key_t * wrapped_key);

        /** This API outputs secp192r1 private wrapped key.
         * @par Implemented as
         * - @ref R_SCE_ECC_secp192r1_EncryptedPrivateKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key secp192r1 private wrapped key
         */
        fsp_err_t (* ECC_secp192r1_EncryptedPrivateKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_ecc_private_wrapped_key_t * wrapped_key);

        /** This API outputs secp224r1 private wrapped key.
         * @par Implemented as
         * - @ref R_SCE_ECC_secp224r1_EncryptedPrivateKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key secp224r1 private wrapped key
         */
        fsp_err_t (* ECC_secp224r1_EncryptedPrivateKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_ecc_private_wrapped_key_t * wrapped_key);

        /** This API outputs secp256r1 private wrapped key.
         * @par Implemented as
         * - @ref R_SCE_ECC_secp256r1_EncryptedPrivateKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key secp256r1 private wrapped key
         */
        fsp_err_t (* ECC_secp256r1_EncryptedPrivateKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_ecc_private_wrapped_key_t * wrapped_key);

        /** This API outputs BrainpoolP512r1 private wrapped key.
         * @par Implemented as
         * - @ref R_SCE_ECC_BrainpoolP512r1_EncryptedPrivateKeyWrap()
         *
         * @param[in] initial_vector  Initialization vector when generating encrypted_key
         * @param[in] encrypted_key   User key encryptedand MAC appended
         * @param[in] key_update_key  Key update keyring
         * @param[in,out] wrapped_key BrainpoolP512r1 private wrapped key
         */
        fsp_err_t (* ECC_BrainpoolP512r1_EncryptedPrivateKeyWrap)(uint8_t * initial_vector, uint8_t * encrypted_key,
                sce_key_update_key_t * key_update_key,
                sce_ecc_private_wrapped_key_t * wrapped_key);

        /** ECDSA signature generation.
         * @par Implemented as
         * - @ref R_SCE_ECDSA_secp192r1_SignatureGenerate()
         *
         * @param[in]     message_hash Message or hash value to which to attach signature
         * @param[in,out] signature    Signature text storage destination information
         * @param[in]     wrapped_key  Input wrapped key of secp192r1 private key.
         */
        fsp_err_t (* ECDSA_secp192r1_SignatureGenerate)(sce_ecdsa_byte_data_t         * message_hash,
                sce_ecdsa_byte_data_t         * signature,
                sce_ecc_private_wrapped_key_t * wrapped_key);

        /** ECDSA signature generation.
         * @par Implemented as
         * - @ref R_SCE_ECDSA_secp224r1_SignatureGenerate()
         *
         * @param[in]     message_hash Message or hash value to which to attach signature
         * @param[in,out] signature    Signature text storage destination information
         * @param[in]     wrapped_key  Input wrapped key of secp224r1 private key.
         */
        fsp_err_t (* ECDSA_secp224r1_SignatureGenerate)(sce_ecdsa_byte_data_t         * message_hash,
                sce_ecdsa_byte_data_t         * signature,
                sce_ecc_private_wrapped_key_t * wrapped_key);

        /** ECDSA signature generation.
         * @par Implemented as
         * - @ref R_SCE_ECDSA_secp256r1_SignatureGenerate()
         *
         * @param[in]     message_hash Message or hash value to which to attach signature
         * @param[in,out] signature    Signature text storage destination information
         * @param[in]     wrapped_key  Input wrapped key of secp256r1 private key.
         */
        fsp_err_t (* ECDSA_secp256r1_SignatureGenerate)(sce_ecdsa_byte_data_t         * message_hash,
                sce_ecdsa_byte_data_t         * signature,
                sce_ecc_private_wrapped_key_t * wrapped_key);

        /** ECDSA signature generation.
         * @par Implemented as
         * - @ref R_SCE_ECDSA_BrainpoolP512r1_SignatureGenerate()
         *
         * @param[in]     message_hash Message or hash value to which to attach signature
         * @param[in,out] signature    Signature text storage destination information
         * @param[in]     wrapped_key  Input wrapped key of BrainpoolP512r1 private key.
         */
        fsp_err_t (* ECDSA_BrainpoolP512r1_SignatureGenerate)(sce_ecdsa_byte_data_t         * message_hash,
                sce_ecdsa_byte_data_t         * signature,
                sce_ecc_private_wrapped_key_t * wrapped_key);

        /** ECDSA signature verification.
         * @par Implemented as
         * - @ref R_SCE_ECDSA_secp192r1_SignatureVerify()
         *
         * @param[in]     signature    Signature text information to be verified
         * @param[in,out] message_hash Message or hash value to be verified
         * @param[in]     wrapped_key  Input wrapped key of secp192r1 public key.
         */
        fsp_err_t (* ECDSA_secp192r1_SignatureVerify)(sce_ecdsa_byte_data_t        * signature,
                sce_ecdsa_byte_data_t        * message_hash,
                sce_ecc_public_wrapped_key_t * wrapped_key);

        /** ECDSA signature verification.
         * @par Implemented as
         * - @ref R_SCE_ECDSA_secp224r1_SignatureVerify()
         *
         * @param[in]     signature    Signature text information to be verified
         * @param[in,out] message_hash Message or hash value to be verified
         * @param[in]     wrapped_key  Input wrapped key of secp224r1 public key.
         */
        fsp_err_t (* ECDSA_secp224r1_SignatureVerify)(sce_ecdsa_byte_data_t        * signature,
                sce_ecdsa_byte_data_t        * message_hash,
                sce_ecc_public_wrapped_key_t * wrapped_key);

        /** ECDSA signature verification.
         * @par Implemented as
         * - @ref R_SCE_ECDSA_secp256r1_SignatureVerify()
         *
         * @param[in]     signature    Signature text information to be verified
         * @param[in,out] message_hash Message or hash value to be verified
         * @param[in]     wrapped_key  Input wrapped key of secp256r1 public key.
         */
        fsp_err_t (* ECDSA_secp256r1_SignatureVerify)(sce_ecdsa_byte_data_t        * signature,
                sce_ecdsa_byte_data_t        * message_hash,
                sce_ecc_public_wrapped_key_t * wrapped_key);

        /** ECDSA signature verification.
         * @par Implemented as
         * - @ref R_SCE_ECDSA_BrainpoolP512r1_SignatureVerify()
         *
         * @param[in]     signature    Signature text information to be verified
         * @param[in,out] message_hash Message or hash value to be verified
         * @param[in]     wrapped_key  Input wrapped key of BrainpoolP512r1 public key.
         */
        fsp_err_t (* ECDSA_BrainpoolP512r1_SignatureVerify)(sce_ecdsa_byte_data_t        * signature,
                sce_ecdsa_byte_data_t        * message_hash,
                sce_ecc_public_wrapped_key_t * wrapped_key);

} sce_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_sce_instance
{
        sce_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
        sce_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
        sce_api_t const * p_api;           ///< Pointer to the API structure for this instance
} sce_instance_t;

#endif                                 /* R_SCE_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROTECTED_API)
 **********************************************************************************************************************/
