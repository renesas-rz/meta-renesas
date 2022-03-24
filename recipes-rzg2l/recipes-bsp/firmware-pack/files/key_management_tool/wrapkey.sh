#!/bin/sh

. ./utility.sh

#*******************************************************************************
# Function Name: func_encrypt_key
# Description  : Encrypt keys
# Arguments    : ${1} - key in hex string for wrapping
#              : ${2} - key in hex string for mac
#              : ${3} - iv0 in hex string for wrapping
#              : stdin - key in hex string to encrypt
#              : stdout - encrypted key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_encrypt_key ()
{
	local hex_tag_key="$(cat)"

	local hex_enc_key="${1}"
	local hex_mac_key="${2}"
	local hex_enc_iv0="${3}"

	local len_tag_key="$(expr ${#hex_tag_key} / 2)"
	local len_zero_pad=$(( ((len_tag_key + 15) & (~15)) - len_tag_key ))

	hex_tag_key="${hex_tag_key}$(func_zeropad "${len_zero_pad}")"

	func_hex_to_bin "${hex_tag_key}" | openssl enc -aes-128-cbc -e -nosalt -nopad -K "${hex_enc_key}" -iv "${hex_enc_iv0}" > "${TMP_FILE}"
	if [ 0 != $? ] || [ ! -s "${TMP_FILE}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to encrypt Key"
		return 1
	fi

	func_hex_to_bin "${hex_tag_key}" | openssl dgst -mac cmac -macopt cipher:aes-128-cbc -macopt hexkey:"${hex_mac_key}" -binary >> "${TMP_FILE}"
	if [ 0 != $? ] || [ ! -s "${TMP_FILE}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to generate MAC."
		return 1
	fi

	cat "${TMP_FILE}"

	return 0
}

#*******************************************************************************
# Function Name: func_wrap_cmnkey
# Description  : Wrap the common key.
# Arguments    : ${1} - key length
#              : stdout - encrypted common key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_cmnkey ()
{
	local len_tag_key="${1}"

	local hex_ufp_key=""; local hex_enc_key=""; local hex_mac_key=""; local hex_enc_iv0=""; local hex_cmn_key=""

	hex_ufp_key="$(func_load_cmnkey "${USER_FACTORY_PROG_KEY_SIZE}" < "${FILEPATH_USER_FACTORY_PROG_KEY}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load User Factory Programming Key."
		return 1
	fi

	hex_enc_key="$(echo "${hex_ufp_key}" | cut -c 1-32)"
	hex_mac_key="$(echo "${hex_ufp_key}" | cut -c 33-64)"

	hex_enc_iv0="$(func_load_cmnkey "${USER_FACTORY_PROG_IV0_SIZE}" < "${FILEPATH_UFPK_ENCRYPT_IV0}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load the initialization vector file."
		return 1
	fi

	if [ "true" != "${FLAG_HEX_COMMON}" ]; then
		hex_cmn_key="$(func_load_cmnkey "${len_tag_key}" < "${TMP_FILE}")"
	else
		hex_cmn_key="$(cat "${TMP_FILE}")"
		func_hex_to_bin "${hex_cmn_key}" > ${TMP_FILE}
		hex_cmn_key="$(func_load_cmnkey "${len_tag_key}" < "${TMP_FILE}")"
	fi

	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load Common Key."
		return 1
	fi

	echo "${hex_cmn_key}" | func_encrypt_key "${hex_enc_key}" "${hex_mac_key}" "${hex_enc_iv0}"
	if [ 0 != $? ];then
		errlog "[error] ${SCRIPT_NAME}: Failed to wrap Common Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_wrap_rsa_pub
# Description  : Wrap the rsa public key.
# Arguments    : ${1} - key length
#              : stdout - encrypted rsa public key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_rsa_pub ()
{
	local len_tag_key="${1}"

	local hex_ufp_key=""; local hex_enc_key=""; local hex_mac_key=""; local hex_enc_iv0=""; local hex_pub_key=""

	hex_ufp_key="$(func_load_cmnkey "${USER_FACTORY_PROG_KEY_SIZE}" < "${FILEPATH_USER_FACTORY_PROG_KEY}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load User Factory Programming Key."
		return 1
	fi

	hex_enc_key="$(echo "${hex_ufp_key}" | cut -c 1-32)"
	hex_mac_key="$(echo "${hex_ufp_key}" | cut -c 33-64)"

	hex_enc_iv0="$(func_load_cmnkey "${USER_FACTORY_PROG_IV0_SIZE}" < "${FILEPATH_UFPK_ENCRYPT_IV0}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load the initialization vector file."
		return 1
	fi

	hex_pub_key="$(func_load_rsa_pub "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load RSA Public Key."
		return 1
	fi

	echo "${hex_pub_key}" | func_encrypt_key "${hex_enc_key}" "${hex_mac_key}" "${hex_enc_iv0}"
	if [ 0 != $? ];then
		errlog "[error] ${SCRIPT_NAME}: Failed to wrap RSA Public Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_wrap_rsa_pri
# Description  : Wrap the rsa private key.
# Arguments    : ${1} - key length
#              : stdout - encrypted rsa private key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_rsa_pri ()
{
	local len_tag_key="${1}"

	local hex_ufp_key=""; local hex_enc_key=""; local hex_mac_key=""; local hex_enc_iv0=""; local hex_pri_key=""

	hex_ufp_key="$(func_load_cmnkey "${USER_FACTORY_PROG_KEY_SIZE}" < "${FILEPATH_USER_FACTORY_PROG_KEY}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load User Factory Programming Key."
		return 1
	fi

	hex_enc_key="$(echo "${hex_ufp_key}" | cut -c 1-32)"
	hex_mac_key="$(echo "${hex_ufp_key}" | cut -c 33-64)"

	hex_enc_iv0="$(func_load_cmnkey "${USER_FACTORY_PROG_IV0_SIZE}" < "${FILEPATH_UFPK_ENCRYPT_IV0}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load the initialization vector file."
		return 1
	fi

	hex_pri_key="$(func_load_rsa_pri "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load RSA Private Key."
		return 1
	fi

	echo "${hex_pri_key}" | func_encrypt_key "${hex_enc_key}" "${hex_mac_key}" "${hex_enc_iv0}"
	if [ 0 != $? ];then
		errlog "[error] ${SCRIPT_NAME}: Failed to wrap RSA Private Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_wrap_ecdsa_pri
# Description  : Wrap the ecdsa private key.
# Arguments    : ${1} - key length
#              : stdout - encrypted ecdsa private key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_ecdsa_pri ()
{
	local len_tag_key="${1}"

	local hex_ufp_key=""; local hex_enc_key=""; local hex_mac_key=""; local hex_enc_iv0=""; local hex_pri_key=""

	hex_ufp_key="$(func_load_cmnkey "${USER_FACTORY_PROG_KEY_SIZE}" < "${FILEPATH_USER_FACTORY_PROG_KEY}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load User Factory Programming Key."
		return 1
	fi

	hex_enc_key="$(echo "${hex_ufp_key}" | cut -c 1-32)"
	hex_mac_key="$(echo "${hex_ufp_key}" | cut -c 33-64)"

	hex_enc_iv0="$(func_load_cmnkey "${USER_FACTORY_PROG_IV0_SIZE}" < "${FILEPATH_UFPK_ENCRYPT_IV0}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load the initialization vector file."
		return 1
	fi

	hex_pri_key="$(func_load_ecdsa_pri "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load ECDSA Private Key."
		return 1
	fi

	echo "${hex_pri_key}" | func_encrypt_key "${hex_enc_key}" "${hex_mac_key}" "${hex_enc_iv0}"
	if [ 0 != $? ];then
		errlog "[error] ${SCRIPT_NAME}: Failed to wrap ECDSA Private Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_wrap_ecdsa_pub
# Description  : Wrap the ecdsa public key.
# Arguments    : ${1} - key length
#              : stdout - encrypted ecdsa public key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_ecdsa_pub ()
{
	local len_tag_key="${1}"

	local hex_ufp_key=""; local hex_enc_key=""; local hex_mac_key=""; local hex_enc_iv0=""; local hex_pub_key=""

	hex_ufp_key="$(func_load_cmnkey "${USER_FACTORY_PROG_KEY_SIZE}" < "${FILEPATH_USER_FACTORY_PROG_KEY}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load User Factory Programming Key."
		return 1
	fi

	hex_enc_key="$(echo "${hex_ufp_key}" | cut -c 1-32)"
	hex_mac_key="$(echo "${hex_ufp_key}" | cut -c 33-64)"

	hex_enc_iv0="$(func_load_cmnkey "${USER_FACTORY_PROG_IV0_SIZE}" < "${FILEPATH_UFPK_ENCRYPT_IV0}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load the initialization vector file."
		return 1
	fi

	hex_pub_key="$(func_load_ecdsa_pub "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load ECDSA Public Key."
		return 1
	fi

	echo "${hex_pub_key}" | func_encrypt_key "${hex_enc_key}" "${hex_mac_key}" "${hex_enc_iv0}"
	if [ 0 != $? ];then
		errlog "[error] ${SCRIPT_NAME}: Failed to wrap ECDSA Public Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_exists_keys
# Description  : Check if the user factory programming key and iv0 exists.
#              : If the key does not exist, create it.
# Arguments    : none
# Return Value : 0 or 1
#*******************************************************************************
func_exists_keys ()
{
	if [ ! -s "${FILEPATH_USER_FACTORY_PROG_KEY}" ]; then

		mkdir -p "$(dirname "${FILEPATH_USER_FACTORY_PROG_KEY}")"

		./genkey.sh -t "${AES_128_KEY_TYPE}" > "${FILEPATH_USER_FACTORY_PROG_KEY}"
		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to generate ${FILEPATH_USER_FACTORY_PROG_KEY}"
			return 1
		fi

		./genkey.sh -t "${AES_128_KEY_TYPE}" >> "${FILEPATH_USER_FACTORY_PROG_KEY}"
		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to generate ${FILEPATH_USER_FACTORY_PROG_KEY}"
			return 1
		fi
	fi

	if [ ! -s "${FILEPATH_UFPK_ENCRYPT_IV0}" ]; then

		mkdir -p "$(dirname "${FILEPATH_UFPK_ENCRYPT_IV0}")"

		./genkey.sh -t "${AES_128_KEY_TYPE}" > "${FILEPATH_UFPK_ENCRYPT_IV0}"
		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to generate ${FILEPATH_UFPK_ENCRYPT_IV0}"
			return 1
		fi
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_usage_exit
# Description  : Show usage and exit this script.
# Arguments    : none
# Return Value : none (exit)
#*******************************************************************************
func_usage_exit()
{
	errlog
	errlog "This script is for wrapping RZ/G2 security keys."
	errlog "Version ${TOOL_VERSION}"
	errlog
	errlog "Usage:"
	errlog "    ${SCRIPT_NAME} -t <type>"
	errlog
	errlog "Read the key from standard input or pipe and write the wrapped key to"
	errlog "standard output."
	errlog
	errlog "  -p <path>"
	errlog "     Path to the directory that contains the temporary encryption key for"
	errlog "     the provisioning."
	errlog "     If the key does not exist, it will be generated by this script."
	errlog "     The key for provisioning is ${FILE_USER_FACTORY_PROG_KEY}."
	errlog
	errlog "  -t <type>"
	errlog "     Type of user key to be wrapped."
	errlog "     The supported user key types are:"
	errlog "         ${AES_128_KEY_TYPE}"
	errlog "         ${AES_256_KEY_TYPE}"
	errlog "         ${HMAC_SHA1_KEY_TYPE}"
	errlog "         ${HMAC_SHA256_KEY_TYPE}"
	errlog "         ${RSA_1024_KEY_TYPE_PRI}"
	errlog "         ${RSA_1024_KEY_TYPE_PUB}"
	errlog "         ${RSA_2048_KEY_TYPE_PRI}"
	errlog "         ${RSA_2048_KEY_TYPE_PUB}"
	errlog "         ${ECDSA_P256_KEY_TYPE_PRI}"
	errlog "         ${ECDSA_P256_KEY_TYPE_PUB}"

	exit 1
}

#*******************************************************************************
# Function Name: func_main
# Description  : .
# Arguments    : .
# Return Value : .
#*******************************************************************************
func_main ()
{
	func_exists_keys
	if [ 0 != $? ]; then
		exit $?
	fi

	case "${TYPE_TARGET_KEY}" in

		"${AES_128_KEY_TYPE}")
			func_wrap_cmnkey "${AES_128_KEY_SIZE}"
			;;
		"${AES_256_KEY_TYPE}")
			func_wrap_cmnkey "${AES_256_KEY_SIZE}"
			;;
		"${HMAC_SHA1_KEY_TYPE}")
			func_wrap_cmnkey "${HMAC_SHA1_KEY_SIZE}"
			;;
		"${HMAC_SHA256_KEY_TYPE}")
			func_wrap_cmnkey "${HMAC_SHA256_KEY_SIZE}"
			;;
		"${RSA_1024_KEY_TYPE_PRI}")
			func_wrap_rsa_pri "${RSA_1024_KEY_SIZE}"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			func_wrap_rsa_pub "${RSA_1024_KEY_SIZE}"
			;;
		"${RSA_2048_KEY_TYPE_PRI}")
			func_wrap_rsa_pri "${RSA_2048_KEY_SIZE}"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			func_wrap_rsa_pub "${RSA_2048_KEY_SIZE}"
			;;
		"${ECDSA_P256_KEY_TYPE_PRI}")
			func_wrap_ecdsa_pri "${ECDSA_P256_KEY_SIZE_PRI}"
			;;
		"${ECDSA_P256_KEY_TYPE_PUB}")
			func_wrap_ecdsa_pub "${ECDSA_P256_KEY_SIZE_PUB}"
			;;
		*)  errlog "[error] ${SCRIPT_NAME}: Unsupported key type \"${TYPE_TARGET_KEY}\"."
			func_usage_exit
			;;
	esac

	exit $?
}

#*******************************************************************************
# Startup
#*******************************************************************************
cd "$(dirname ${0})"

. ./config.sh

SCRIPT_NAME="$(basename ${0})"

if [ -f /dev/stdin ] || [ -p /dev/stdin ]; then
	cat "/dev/stdin" > "${TMP_FILE}"
fi

while getopts :t:p:x OPT
do
	case "${OPT}" in
		t) typ_tag_key="${OPTARG}"
			;;
		p) dirpath_prv="${OPTARG}"
			;;
		x) flg_hex_cmn="true"
			;;
		:|\?) func_usage_exit
			;;
	esac
done

if [ ! -s "${TMP_FILE}" ] || [ -z "${typ_tag_key}" ] || [ -z "${dirpath_prv}" ]; then
	func_usage_exit
fi

TYPE_TARGET_KEY="$(echo "${typ_tag_key}" | tr '[:upper:]' '[:lower:]')"

FILEPATH_USER_FACTORY_PROG_KEY="${dirpath_prv%/}/${FILE_USER_FACTORY_PROG_KEY}.bin"
FILEPATH_UFPK_ENCRYPT_IV0="${dirpath_prv%/}/${FILE_USER_FACTORY_PROG_IV0}.bin"

FLAG_HEX_COMMON="${flg_hex_cmn}"

# Call func_main
func_main
