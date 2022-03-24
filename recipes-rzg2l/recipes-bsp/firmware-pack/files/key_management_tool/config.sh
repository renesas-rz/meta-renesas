#!/bin/sh

# RZ/G2L Tool Version
readonly TOOL_VERSION="1.00"

# Default Root directory path where the generated keys are stored
DIRPATH_KEYGEN_ROOT="${HOME}/rzg2l_key_mgr"

# Directory name where User Factory Programming Key is stored
readonly DIR_USER_FACTORY_PROG='user_factory_prog'

readonly FILE_USER_FACTORY_PROG_KEY='ufpk'
readonly USER_FACTORY_PROG_KEY_SIZE=32

readonly FILE_USER_FACTORY_PROG_IV0='ufpk_init_vec'
readonly USER_FACTORY_PROG_IV0_SIZE=16

# Boot program encryption key
readonly LIST_BOOTPRG_VERIFY_ENC_KEY='cmn_key_idx0 cmn_key_idx1 cmn_key_idx2 cmn_key_idx3 jtag_auth_code'
readonly BOOTPRG_VERIFY_ENC_KEY_TYPE='aes-128'
readonly BOOTPRG_VERIFY_ENC_KEY_SIZE=16

# Boot program signing key
readonly LIST_BOOTPRG_VERIFY_SIG_KEY='root_of_trust_key bl2_key bl31_key bl32_key bl33_key'
readonly BOOTPRG_VERIFY_SIG_KEY_TYPE='ecdsa-p256-pri'

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

# ECDSA-P256 Key for Basic cryptographic features
readonly FILE_ECDSA_P256_KEY='ecdsa_p256_key'
readonly ECDSA_P256_KEY_TYPE_PRI='ecdsa-p256-pri'
readonly ECDSA_P256_KEY_TYPE_PUB='ecdsa-p256-pub'
readonly ECDSA_P256_KEY_SIZE_PRI=32
readonly ECDSA_P256_KEY_SIZE_PUB=64

# List of keys generated for basic cryptographic features
readonly LIST_GENERATION_USERKEY="
	${AES_128_KEY_TYPE},${FILE_AES_128_KEY},0
	${AES_256_KEY_TYPE},${FILE_AES_256_KEY},0
	${HMAC_SHA1_KEY_TYPE},${FILE_HMAC_SHA1_KEY},0
	${HMAC_SHA256_KEY_TYPE},${FILE_HMAC_SHA256_KEY},0
	${RSA_1024_KEY_TYPE_PRI},${FILE_RSA_1024_KEY},0
	${RSA_1024_KEY_TYPE_PUB},${FILE_RSA_1024_KEY},0
	${RSA_2048_KEY_TYPE_PRI},${FILE_RSA_2048_KEY},0
	${RSA_2048_KEY_TYPE_PUB},${FILE_RSA_2048_KEY},0
	${ECDSA_P256_KEY_TYPE_PRI},${FILE_ECDSA_P256_KEY},0
	${ECDSA_P256_KEY_TYPE_PUB},${FILE_ECDSA_P256_KEY},0
"
