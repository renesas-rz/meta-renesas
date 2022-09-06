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

	local hex_ekey="${1}"; local hex_mkey="${2}"; local hex_eiv0="${3}"

	local len_tag_key="$(expr ${#hex_tag_key} / 2)"
	local len_zero_pad=$(( ((len_tag_key + 15) & (~15)) - len_tag_key ))

	hex_tag_key="${hex_tag_key}$(func_zeropad "${len_zero_pad}")"

	func_hex_to_bin "${hex_tag_key}" | openssl enc -aes-128-cbc -e -nosalt -nopad -K "${hex_ekey}" -iv "${hex_eiv0}" > "${TMP_FILE}"
	if [ 0 != $? ] || [ ! -s "${TMP_FILE}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to encrypt Key"
		return 1
	fi

	func_hex_to_bin "${hex_tag_key}" | openssl dgst -mac cmac -macopt cipher:aes-128-cbc -macopt hexkey:"${hex_mkey}" -binary >> "${TMP_FILE}"
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

	hex_cmn_key=""

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

	echo "${hex_cmn_key}" | func_encrypt_key "${HEX_ENC_KEY}" "${HEX_MAC_KEY}" "${HEX_ENC_IV0}"
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

	local hex_pub_key=""

	hex_pub_key="$(func_load_rsa_pub "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load RSA Public Key."
		return 1
	fi

	echo "${hex_pub_key}" | func_encrypt_key "${HEX_ENC_KEY}" "${HEX_MAC_KEY}" "${HEX_ENC_IV0}"
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
	local len_tag_key="${1}";

	local hex_pri_key=""

	hex_pri_key="$(func_load_rsa_pri "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load RSA Private Key."
		return 1
	fi

	echo "${hex_pri_key}" | func_encrypt_key "${HEX_ENC_KEY}" "${HEX_MAC_KEY}" "${HEX_ENC_IV0}"
	if [ 0 != $? ];then
		errlog "[error] ${SCRIPT_NAME}: Failed to wrap RSA Private Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_wrap_ecc_pub
# Description  : Wrap the ecc public key.
# Arguments    : ${1} - key length
#              : stdout - encrypted ecc public key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_ecc_pub ()
{
	local len_tag_key="${1}"; local len_txt_prm=""; local len_key_prm=""; 
	local len_zero_pad=""; 
	
	local hex_pub_key=""; local hex_key_qx=""; local hex_key_qy="";

	hex_pub_key="$(func_load_ecc_pub "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load ECC Public Key."
		return 1
	fi

	len_txt_prm="$(expr ${#hex_pub_key} / 2)"
	len_key_prm="$(expr ${len_tag_key} / 2)"
	len_zero_pad=$(( ((len_key_prm + 15) & (~15)) - len_key_prm ))

	errlog "${hex_pub_key}"

	hex_key_qx="$(echo "${hex_pub_key}" | cut -c -${len_txt_prm})"
	hex_key_qy="$(echo "${hex_pub_key}" | rev | cut -c -${len_txt_prm} | rev)"

	hex_key_qx="$(func_zeropad "${len_zero_pad}")${hex_key_qx}"
	hex_key_qy="$(func_zeropad "${len_zero_pad}")${hex_key_qy}"

	hex_pub_key="${hex_key_qx}${hex_key_qy}"
	
	errlog "${hex_pub_key}"
	echo "${hex_pub_key}" | func_encrypt_key "${HEX_ENC_KEY}" "${HEX_MAC_KEY}" "${HEX_ENC_IV0}"
	if [ 0 != $? ];then
		errlog "[error] ${SCRIPT_NAME}: Failed to wrap ECC Public Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_wrap_ecc_pri
# Description  : Wrap the ecc private key.
# Arguments    : ${1} - key length
#              : stdout - encrypted ecc private key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_ecc_pri ()
{
	local len_tag_key="${1}"; local len_key_prm=""; local len_zero_pad="";

	local hex_pri_key=""

	hex_pri_key="$(func_load_ecc_pri "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to load ECC Private Key."
		return 1
	fi

	len_key_prm="$(expr ${#hex_pri_key} / 2)"
	len_zero_pad=$(( ((len_key_prm + 15) & (~15)) - len_key_prm ))

	hex_pri_key="$(func_zeropad "${len_zero_pad}")${hex_pri_key}"

	echo "${hex_pri_key}" | func_encrypt_key "${HEX_ENC_KEY}" "${HEX_MAC_KEY}" "${HEX_ENC_IV0}"
	if [ 0 != $? ];then
		errlog "[error] ${SCRIPT_NAME}: Failed to wrap ECC Private Key."
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
	if [ ! -s "${FILEPATH_KEY_ENCRYPTION_KEY}" ]; then

		mkdir -p "$(dirname "${FILEPATH_KEY_ENCRYPTION_KEY}")"

		./genkey.sh -t "${AES_128_KEY_TYPE}" > "${FILEPATH_KEY_ENCRYPTION_KEY}"
		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to generate ${FILEPATH_KEY_ENCRYPTION_KEY}"
			return 1
		fi

		./genkey.sh -t "${AES_128_KEY_TYPE}" >> "${FILEPATH_KEY_ENCRYPTION_KEY}"
		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to generate ${FILEPATH_KEY_ENCRYPTION_KEY}"
			return 1
		fi
	fi

	if [ ! -s "${FILEPATH_KEY_ENCRYPTION_IV0}" ]; then

		mkdir -p "$(dirname "${FILEPATH_KEY_ENCRYPTION_IV0}")"

		./genkey.sh -t "${AES_128_KEY_TYPE}" > "${FILEPATH_KEY_ENCRYPTION_IV0}"
		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to generate ${FILEPATH_KEY_ENCRYPTION_IV0}"
			return 1
		fi
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_load_enc_key
# Description  : 
# Arguments    : none
# Return Value : 0 or 1
#*******************************************************************************
func_load_enc_key ()
{
	local hex_key_enc_key=""; local txt_key_enc_key="";

	if [ "true" != "${FLAG_KEY_UPDATE}" ]; then
	
		func_exists_keys
		if [ 0 != $? ]; then
			return 1
		fi
		
		hex_key_enc_key="$(func_load_cmnkey "${USER_FACTORY_PROG_KEY_SIZE}" < "${FILEPATH_KEY_ENCRYPTION_KEY}")"
		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to load User Factory Programming Key."
			return 1
		fi

		HEX_ENC_KEY="$(echo "${hex_key_enc_key}" | cut -c 1-32)"
		HEX_MAC_KEY="$(echo "${hex_key_enc_key}" | cut -c 33-64)"

		HEX_ENC_IV0="$(func_load_cmnkey "${USER_FACTORY_PROG_IV0_SIZE}" < "${FILEPATH_KEY_ENCRYPTION_IV0}")"
		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to load the initialization vector file."
			return 1
		fi
	else

		if [ ! -s "${FILEPATH_KEY_ENCRYPTION_KEY}" ] || [ ! -s "${FILEPATH_KEY_ENCRYPTION_IV0}" ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to load ${FILEPATH_KEY_ENCRYPTION_KEY} or ${FILEPATH_KEY_ENCRYPTION_IV0}."
			return 1
		fi
		
		txt_key_enc_key="$(cat "${FILEPATH_KEY_ENCRYPTION_KEY}")"
		hex_key_enc_key="$(func_hex_to_bin "${txt_key_enc_key}" | func_load_cmnkey "${KEY_UPDATE_KEY_SIZE}")"

		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to load Key Update Key file."
			return 1
		fi

		HEX_ENC_KEY="$(echo "${hex_key_enc_key}" | cut -c 1-32)"
		HEX_MAC_KEY="$(echo "${hex_key_enc_key}" | cut -c 33-64)"

		txt_key_enc_key="$(cat "${FILEPATH_KEY_ENCRYPTION_IV0}")"
		HEX_ENC_IV0="$(func_hex_to_bin "${txt_key_enc_key}" | func_load_cmnkey "${KEY_UPDATE_IV0_SIZE}")"

		if [ 0 != $? ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to load the Key Update IV file."
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
	errlog "    ${SCRIPT_NAME} -t <type> [-p <path> | -u <path>]"
	errlog
	errlog "Read the key from standard input or pipe and write the wrapped key to"
	errlog "standard output."
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
	errlog "         ${RSA_4096_KEY_TYPE_PRI}"
	errlog "         ${RSA_4096_KEY_TYPE_PUB}"
	errlog "         ${ECC_P256_KEY_TYPE_PRI}"
	errlog "         ${ECC_P256_KEY_TYPE_PUB}"
	errlog
	errlog "  -p <path>"
	errlog "     Path to the directory that contains the temporary encryption key for"
	errlog "     the provisioning."
	errlog "     If the key does not exist, it will be generated by this script."
	errlog "     The key for provisioning is ${FILE_USER_FACTORY_PROG_KEY}."
	errlog
	errlog "  -u <path>"
	errlog "     Path to the directory that contains the key update key."
	errlog "     The key update key is ${FILE_KEY_UPDATE_KEY}."
	errlog

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
	func_load_enc_key
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
		"${RSA_4096_KEY_TYPE_PRI}")
			func_wrap_rsa_pri "${RSA_4096_KEY_SIZE}"
			;;
		"${RSA_4096_KEY_TYPE_PUB}")
			func_wrap_rsa_pub "${RSA_4096_KEY_SIZE}"
			;;
		"${ECC_P192_KEY_TYPE_PRI}")
			func_wrap_ecc_pri "${ECC_P192_KEY_SIZE_PRI}"
			;;
		"${ECC_P192_KEY_TYPE_PUB}")
			func_wrap_ecc_pub "${ECC_P192_KEY_SIZE_PUB}"
			;;
		"${ECC_P224_KEY_TYPE_PRI}")
			func_wrap_ecc_pri "${ECC_P224_KEY_SIZE_PRI}"
			;;
		"${ECC_P224_KEY_TYPE_PUB}")
			func_wrap_ecc_pub "${ECC_P224_KEY_SIZE_PUB}"
			;;
		"${ECC_P256_KEY_TYPE_PRI}")
			func_wrap_ecc_pri "${ECC_P256_KEY_SIZE_PRI}"
			;;
		"${ECC_P256_KEY_TYPE_PUB}")
			func_wrap_ecc_pub "${ECC_P256_KEY_SIZE_PUB}"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PRI}")
			func_wrap_ecc_pri "${ECC_BSI_P512_KEY_SIZE_PRI}"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PUB}")
			func_wrap_ecc_pub "${ECC_BSI_P512_KEY_SIZE_PUB}"
			;;
		"${KEY_UPDATE_KEY_TYPE}")
			func_wrap_cmnkey "${KEY_UPDATE_KEY_SIZE}"
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

while getopts :t:p:u:x OPT
do
	case "${OPT}" in
		t) typ_tag_key="${OPTARG}"
			;;
		p) flg_key_upd="false"
		   dirpath_prv="${OPTARG}"
			;;
		u) flg_key_upd="true"
		   dirpath_prv="${OPTARG}"
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

FLAG_HEX_COMMON="${flg_hex_cmn}"
FLAG_KEY_UPDATE="${flg_key_upd}"

if [ "true" != "${FLAG_KEY_UPDATE}" ]; then
	FILEPATH_KEY_ENCRYPTION_KEY="${dirpath_prv%/}/${FILE_USER_FACTORY_PROG_KEY}.bin"
	FILEPATH_KEY_ENCRYPTION_IV0="${dirpath_prv%/}/${FILE_USER_FACTORY_PROG_IV0}.bin"
else
	FILEPATH_KEY_ENCRYPTION_KEY="${dirpath_prv%/}/${FILE_KEY_UPDATE_KEY}.txt"
	FILEPATH_KEY_ENCRYPTION_IV0="${dirpath_prv%/}/${FILE_KEY_UPDATE_IV0}.txt"
fi

HEX_ENC_KEY=
HEX_MAC_KEY=
HEX_ENC_IV0=

# Call func_main
func_main
