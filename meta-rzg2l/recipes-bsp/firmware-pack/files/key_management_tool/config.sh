#!/bin/sh

# RZ/G2L Tool Version
readonly TOOL_VERSION="1.00"

# Default Root directory path where the generated keys are stored
DIRPATH_KEYGEN_ROOT="${HOME}/rz_key_mgr"

# Directory name where User Factory Programming Key is stored
readonly DIR_USER_FACTORY_PROG='user_factory_prog'

readonly FILE_USER_FACTORY_PROG_KEY='ufpk'
readonly USER_FACTORY_PROG_KEY_SIZE=32

readonly FILE_USER_FACTORY_PROG_IV0='ufpk_init_vec'
readonly USER_FACTORY_PROG_IV0_SIZE=16

# Boot program encryption key
readonly LIST_BOOTPRG_VERIFY_ENC_KEY='cmn_key_idx0 cmn_key_idx1 cmn_key_idx2 cmn_key_idx3 jtag_auth_code'
readonly BOOTPRG_VERIFY_ENC_KEY_TYPE='aes-128'

# Boot program signing key
readonly LIST_BOOTPRG_VERIFY_SIG_KEY='root_of_trust_key bl2_key bl31_key bl32_key bl33_key'
readonly BOOTPRG_VERIFY_SIG_KEY_TYPE='ecc-p256-pri'

# Key update key
readonly FILE_KEY_UPDATE_KEY='key_update_key'
readonly KEY_UPDATE_KEY_TYPE='kuk'
readonly KEY_UPDATE_KEY_SIZE=32
readonly FILE_KEY_UPDATE_IV0='kuk_init_vec'
readonly KEY_UPDATE_IV0_TYPE='kui'
readonly KEY_UPDATE_IV0_SIZE=16

# Directory name where the generated user keys are stored
readonly DIR_USER_KEY='user_keys'

# AES-128 Key for Basic cryptographic features
readonly FILE_AES_128_KEY='aes_128_key'
readonly AES_128_KEY_TYPE='aes-128'
readonly AES_128_KEY_SIZE=16

# AES-256 Key for Basic cryptographic features
readonly FILE_AES_256_KEY='aes_256_key'
readonly AES_256_KEY_TYPE='aes-256'
readonly AES_256_KEY_SIZE=32

# HMAC-SHA1 Key for Basic cryptographic features
readonly FILE_HMAC_SHA1_KEY='hmac_sha1_key'
readonly HMAC_SHA1_KEY_TYPE='hmac-sha1'
readonly HMAC_SHA1_KEY_SIZE=20

# HMAC-SHA256 Key for Basic cryptographic features
readonly FILE_HMAC_SHA256_KEY='hmac_sha256_key'
readonly HMAC_SHA256_KEY_TYPE='hmac-sha256'
readonly HMAC_SHA256_KEY_SIZE=32

# RSA-1024 Key for Basic cryptographic features
readonly FILE_RSA_1024_KEY='rsa_1024_key'
readonly RSA_1024_KEY_TYPE_PRI='rsa-1024-pri'
readonly RSA_1024_KEY_TYPE_PUB='rsa-1024-pub'
readonly RSA_1024_KEY_SIZE=128

# RSA-2048 Key for Basic cryptographic features
readonly FILE_RSA_2048_KEY='rsa_2048_key'
readonly RSA_2048_KEY_TYPE_PRI='rsa-2048-pri'
readonly RSA_2048_KEY_TYPE_PUB='rsa-2048-pub'
readonly RSA_2048_KEY_SIZE=256

# RSA-4096 Key for Basic cryptographic features
readonly FILE_RSA_4096_KEY='rsa_4096_key'
readonly RSA_4096_KEY_TYPE_PRI='rsa-4096-pri'
readonly RSA_4096_KEY_TYPE_PUB='rsa-4096-pub'
readonly RSA_4096_KEY_SIZE=512

# ECC NIST-P192 Key for Basic cryptographic features
readonly FILE_ECC_P192_KEY='ecc_p192_key'
readonly ECC_P192_KEY_TYPE_PRI='ecc-p192-pri'
readonly ECC_P192_KEY_TYPE_PUB='ecc-p192-pub'
readonly ECC_P192_KEY_SIZE_PRI=24
readonly ECC_P192_KEY_SIZE_PUB=48

# ECC NIST-P224 Key for Basic cryptographic features
readonly FILE_ECC_P224_KEY='ecc_p224_key'
readonly ECC_P224_KEY_TYPE_PRI='ecc-p224-pri'
readonly ECC_P224_KEY_TYPE_PUB='ecc-p224-pub'
readonly ECC_P224_KEY_SIZE_PRI=28
readonly ECC_P224_KEY_SIZE_PUB=56

# ECC NIST-P256 Key for Basic cryptographic features
readonly FILE_ECC_P256_KEY='ecc_p256_key'
readonly ECC_P256_KEY_TYPE_PRI='ecc-p256-pri'
readonly ECC_P256_KEY_TYPE_PUB='ecc-p256-pub'
readonly ECC_P256_KEY_SIZE_PRI=32
readonly ECC_P256_KEY_SIZE_PUB=64

# ECC Brainpool-P512r1 Key for Basic cryptographic features
readonly FILE_ECC_BSI_P512_KEY='ecc_bsi_p512_key'
readonly ECC_BSI_P512_KEY_TYPE_PRI='ecc-bsi_p512-pri'
readonly ECC_BSI_P512_KEY_TYPE_PUB='ecc-bsi_p512-pub'
readonly ECC_BSI_P512_KEY_SIZE_PRI=64
readonly ECC_BSI_P512_KEY_SIZE_PUB=128

# List of keys generated for basic cryptographic features
readonly LIST_GENERATION_USERKEY="
	${AES_128_KEY_TYPE},${FILE_AES_128_KEY},2
	${AES_256_KEY_TYPE},${FILE_AES_256_KEY},2
	${HMAC_SHA1_KEY_TYPE},${FILE_HMAC_SHA1_KEY},0
	${HMAC_SHA256_KEY_TYPE},${FILE_HMAC_SHA256_KEY},0
	${RSA_1024_KEY_TYPE_PRI},${FILE_RSA_1024_KEY},2
	${RSA_1024_KEY_TYPE_PUB},${FILE_RSA_1024_KEY},2
	${RSA_2048_KEY_TYPE_PRI},${FILE_RSA_2048_KEY},2
	${RSA_2048_KEY_TYPE_PUB},${FILE_RSA_2048_KEY},2
	${RSA_4096_KEY_TYPE_PRI},${FILE_RSA_4096_KEY},2
	${RSA_4096_KEY_TYPE_PUB},${FILE_RSA_4096_KEY},2
	${ECC_P192_KEY_TYPE_PRI},${FILE_ECC_P192_KEY},2
	${ECC_P192_KEY_TYPE_PUB},${FILE_ECC_P192_KEY},2
	${ECC_P224_KEY_TYPE_PRI},${FILE_ECC_P224_KEY},2
	${ECC_P224_KEY_TYPE_PUB},${FILE_ECC_P224_KEY},2
	${ECC_P256_KEY_TYPE_PRI},${FILE_ECC_P256_KEY},2
	${ECC_P256_KEY_TYPE_PUB},${FILE_ECC_P256_KEY},2
	${ECC_BSI_P512_KEY_TYPE_PRI},${FILE_ECC_BSI_P512_KEY},2
	${ECC_BSI_P512_KEY_TYPE_PUB},${FILE_ECC_BSI_P512_KEY},2
"
