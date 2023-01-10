#!/bin/sh

# Default Root directory path where the generated keys are stored
DIRPATH_KEYGEN_ROOT="${HOME}/temp/otsuka/private/secure/Key/RZG2"

# Provisioning key used for temporary encryption to inject the keyring
readonly DIR_PROVISIONING_KEY='Provisioning'

readonly FILE_PROVISIONING_KEY='ProvisioningKey.bin'
readonly PROVISIONING_KEY_SIZE=32

readonly FILE_PROVISIONING_KEY_ENC='ProvisioningKey_Enc.bin'
readonly PROVISIONING_KEY_ENC_SIZE=36

# Keyring with temporary encryption keys bundled
readonly FILE_BOOT_KEYRING='Keyring.bin'
readonly BOOT_KEYRING_TYPE='keyring'
readonly BOOT_KEYRING_SIZE=672

# Temporary encryption key used for verification when installing the boot program
readonly FILE_BOOTPRG_VERIFY_ENC_KEY='E-Key.bin'
readonly BOOTPRG_VERIFY_ENC_KEY_SIZE=32
readonly FILE_BOOTPRG_VERIFY_SIG_KEY='SBS-Key.pem'
readonly BOOTPRG_VERIFY_SIG_KEY_SIZE=256
readonly FILE_BOOTPRG_VERIFY_VER_KEY='SBP-Key.pem'
readonly BOOTPRG_VERIFY_VER_KEY_SIZE=256

# Temporary encryption key used to update keyring
readonly FILE_KEYRING_UPDATE_ENC_KEY='SS_UP1-Key.bin'
readonly KEYRING_UPDATE_ENC_KEY_SIZE=16
readonly FILE_KEYRING_UPDATE_MAC_KEY='SS_UP2-Key.bin'
readonly KEYRING_UPDATE_MAC_KEY_SIZE=16

# Temporary encryption key used to inject user keys for Basic cryptographic features
readonly FILE_USERKEY_INJECT_ENC_KEY='BCF1-Key.bin'
readonly USERKEY_INJECT_ENC_KEY_SIZE=16
readonly FILE_USERKEY_INJECT_MAC_KEY='BCF2-Key.bin'
readonly USERKEY_INJECT_MAC_KEY_SIZE=16

readonly DIR_USER_KEY='UserKey'

# AES-128 Key for Basic cryptographic features
readonly FILE_AES_128_KEY='AES-128-Key.bin'
readonly AES_128_KEY_TYPE='aes-128'
readonly AES_128_KEY_SIZE=16

# AES-256 Key for Basic cryptographic features
readonly FILE_AES_256_KEY='AES-256-Key.bin'
readonly AES_256_KEY_TYPE='aes-256'
readonly AES_256_KEY_SIZE=32

# HMAC-SHA1 Key for Basic cryptographic features
readonly FILE_HMAC_SHA1_KEY='HMAC-SHA1-Key.bin'
readonly HMAC_SHA1_KEY_TYPE='hmac-sha1'
readonly HMAC_SHA1_KEY_SIZE=20

# HMAC-SHA256 Key for Basic cryptographic features
readonly FILE_HMAC_SHA256_KEY='HMAC-SHA256-Key.bin'
readonly HMAC_SHA256_KEY_TYPE='hmac-sha256'
readonly HMAC_SHA256_KEY_SIZE=32

# RSA-1024 Key for Basic cryptographic features
readonly FILE_RSA_1024_PRV_KEY='RSA-1024-Key.pem'
readonly FILE_RSA_1024_PUB_KEY='RSA-1024-Key-Pub.pem'
readonly RSA_1024_KEY_TYPE_PRV='rsa-1024-prv'
readonly RSA_1024_KEY_TYPE_PUB='rsa-1024-pub'
readonly RSA_1024_KEY_SIZE=128

# RSA-2048 Key for Basic cryptographic features
readonly FILE_RSA_2048_PRV_KEY='RSA-2048-Key.pem'
readonly FILE_RSA_2048_PUB_KEY='RSA-2048-Key-Pub.pem'
readonly RSA_2048_KEY_TYPE_PRV='rsa-2048-prv'
readonly RSA_2048_KEY_TYPE_PUB='rsa-2048-pub'
readonly RSA_2048_KEY_SIZE=256

# List of keys and numbers to generate for basic features
readonly LIST_GENERATION_USERKEY="
	${AES_128_KEY_TYPE},0
	${AES_256_KEY_TYPE},0
	${HMAC_SHA1_KEY_TYPE},0
	${HMAC_SHA256_KEY_TYPE},0
	${RSA_1024_KEY_TYPE_PRV},0
	${RSA_1024_KEY_TYPE_PUB},0
	${RSA_2048_KEY_TYPE_PRV},0
	${RSA_2048_KEY_TYPE_PUB},0
"
