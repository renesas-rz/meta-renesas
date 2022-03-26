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
	
	local hex_mac_val="00000000000000000000000000000000"
	
	func_hex_to_bin "${hex_tag_key}" | openssl enc -aes-128-cbc -e -nosalt -nopad -K "${hex_mac_key}" -iv "${hex_mac_val}" -out "${TMP_FILE}"
	if [ 0 != $? ] || [ ! -s "${TMP_FILE}" ]; then
		errlog "[error] ${file_script}: Failed to generate MAC."
		return 1
	fi
	
	hex_mac_val="$(xxd -p -s -16 -l 16 < "${TMP_FILE}" 2>/dev/null)"
	if [ 0 != $? ] || [ -z "${hex_mac_val}" ]; then
		errlog "[error] ${file_script}: Failed to extract MAC."
		return 1
	fi
	
	hex_tag_key="${hex_tag_key}${hex_mac_val}"
	
	func_hex_to_bin "${hex_tag_key}" | openssl enc -aes-128-cbc -e -nosalt -nopad -K "${hex_enc_key}" -iv "${hex_enc_iv0}"
	if [ 0 != $? ] || [ ! -s "${TMP_FILE}" ]; then
		errlog "[error] ${file_script}: Failed to encrypt Key"
		return 1
	fi
	
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
	
	local hex_enc_key=""; local hex_mac_key="";
	
	hex_enc_key="$(func_load_cmnkey "${USERKEY_INJECT_ENC_KEY_SIZE}" < "${FILEPATH_USERKEY_INJECT_ENC_KEY}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load Encryption Key for inject."
		return 1
	fi
	
	hex_mac_key="$(func_load_cmnkey "${USERKEY_INJECT_MAC_KEY_SIZE}" < "${FILEPATH_USERKEY_INJECT_MAC_KEY}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load MAC Generation Key for inject."
		return 1
	fi
	
	local hex_enc_iv0='00000000000000000000000000000000'
	
	if [ "${HMAC_SHA1_KEY_TYPE}" != "${TYPE_TARGET_KEY}" ] && [ "${HMAC_SHA256_KEY_TYPE}" != "${TYPE_TARGET_KEY}" ]; then
	
		hex_enc_iv0="$(./genkey.sh -t "${AES_128_KEY_TYPE}" | func_bin_to_hex)"
		if [ 0 != $? ]; then
			errlog "[error] ${file_script}: Failed to generate IV."
		fi
	fi
	
	local hex_cmn_key="$(func_load_cmnkey "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load Common Key."
		return 1
	fi
	
	echo "${hex_cmn_key}" | func_encrypt_key "${hex_enc_key}" "${hex_mac_key}" "${hex_enc_iv0}"
	if [ 0 != $? ];then
		errlog "[error] ${file_script}: Failed to wrap Common Key."
		return 1
	fi
	
	return 0
}


#*******************************************************************************
# Function Name: func_wrap_pubkey
# Description  : Wrap the rsa public key.
# Arguments    : ${1} - key length
#              : stdout - encrypted rsa public key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_pubkey ()
{
	local len_tag_key="${1}"
	
	local hex_enc_key=""; local hex_mac_key="";
	
	hex_enc_key="$(func_load_cmnkey "${USERKEY_INJECT_ENC_KEY_SIZE}" < "${FILEPATH_USERKEY_INJECT_ENC_KEY}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load Encryption Key for inject."
		return 1
	fi
	
	hex_mac_key="$(func_load_cmnkey "${USERKEY_INJECT_MAC_KEY_SIZE}" < "${FILEPATH_USERKEY_INJECT_MAC_KEY}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load MAC Generation Key for inject."
		return 1
	fi
	
	local hex_enc_iv0="$(./genkey.sh -t "${AES_128_KEY_TYPE}" | func_bin_to_hex)"
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to generate IV."
	fi
	
	local hex_pub_key="$(func_load_pubkey "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load RSA Public Key."
		return 1
	fi
	
	echo "${hex_pub_key}" | func_encrypt_key "${hex_enc_key}" "${hex_mac_key}" "${hex_enc_iv0}"
	if [ 0 != $? ];then
		errlog "[error] ${file_script}: Failed to wrap RSA Public Key."
		return 1
	fi
	
	return 0
}

#*******************************************************************************
# Function Name: func_wrap_prvkey
# Description  : Wrap the rsa private key.
# Arguments    : ${1} - key length
#              : stdout - encrypted rsa private key in binary
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_prvkey ()
{
	local len_tag_key="${1}"
	
	local hex_enc_key=""; local hex_mac_key="";
	
	hex_enc_key="$(func_load_cmnkey "${USERKEY_INJECT_ENC_KEY_SIZE}" < "${FILEPATH_USERKEY_INJECT_ENC_KEY}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load Encryption Key for inject."
		return 1
	fi
	
	hex_mac_key="$(func_load_cmnkey "${USERKEY_INJECT_MAC_KEY_SIZE}" < "${FILEPATH_USERKEY_INJECT_MAC_KEY}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load MAC Generation Key for inject."
		return 1
	fi
	
	local hex_enc_iv0="$(./genkey.sh -t "${AES_128_KEY_TYPE}" | func_bin_to_hex)"
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to generate IV."
	fi
	
	local hex_prv_key="$(func_load_prvkey "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load RSA Private Key."
		return 1
	fi
	
	echo "${hex_prv_key}" | func_encrypt_key "${hex_enc_key}" "${hex_mac_key}" "${hex_enc_iv0}"
	if [ 0 != $? ];then
		errlog "[error] ${file_script}: Failed to wrap RSA Private Key."
		return 1
	fi
	
	return 0
}

#*******************************************************************************
# Function Name: func_wrap_keyring
# Description  : Wrap the keyring.
# Arguments    : ${1} - key length
#              : ${2} - update flag
# Return Value : 0 or 1
#*******************************************************************************
func_wrap_keyring ()
{
	local len_tag_key="${1}"
	local flg_key_upd="${2}"
	
	local hex_enc_key=""; local hex_mac_key="";
	
	if [ ! -z "${FILEPATH_PROVISIONING_KEY}" ]; then
		
		if [ ! -s "${FILEPATH_PROVISIONING_KEY}" ]; then
			
			mkdir -p "$(dirname "${FILEPATH_PROVISIONING_KEY}")"
			
			./genkey.sh -t "${AES_256_KEY_TYPE}" > "${FILEPATH_PROVISIONING_KEY}"
			if [ 0 != $? ]; then
				errlog "[error] ${file_script}: Failed to generate the Provisioning Key"
				return 1
			fi
		fi
		
		hex_prov_key="$(func_load_cmnkey "${PROVISIONING_KEY_SIZE}" < "${FILEPATH_PROVISIONING_KEY}")"
		if [ 0 != $? ]; then 
			errlog "[error] ${file_script}: Failed to load Provisioning Key."
			return 1
		fi
		
		hex_enc_key="$(echo "${hex_prov_key}" | cut -c 1-32)"
		hex_mac_key="$(echo "${hex_prov_key}" | cut -c 33-64)"
	else
		hex_enc_key="$(func_load_cmnkey "${KEYRING_UPDATE_ENC_KEY_SIZE}" < "${FILEPATH_KEYRING_UPDATE_ENC_KEY}")"
		if [ 0 != $? ]; then 
			errlog "[error] ${file_script}: Failed to load Encryption Key for update."
			return 1
		fi
		
		hex_mac_key="$(func_load_cmnkey "${KEYRING_UPDATE_MAC_KEY_SIZE}" < "${FILEPATH_KEYRING_UPDATE_MAC_KEY}")"
		if [ 0 != $? ]; then 
			errlog "[error] ${file_script}: Failed to load MAC Generation Key for update."
			return 1
		fi
	fi
	
	local hex_enc_iv0="85c1673483d5d291f0d0713e3ea434a3"
	
	local hex_keyring="$(func_load_cmnkey "${len_tag_key}" < "${TMP_FILE}")"
	if [ 0 != $? ]; then 
		errlog "[error] ${file_script}: Failed to load Keyring."
		return 1
	fi
	
	echo "${hex_keyring}" | func_encrypt_key "${hex_enc_key}" "${hex_mac_key}" "${hex_enc_iv0}"
	if [ 0 != $? ];then
		errlog "[error] ${file_script}: Failed to wrap Keyring."
		return 1
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
	errlog
	errlog "Usage:"
	errlog "    ${file_script} -t ${BOOT_KEYRING_TYPE} [-p <path> | -u <path>]"
	errlog "  or"
	errlog "    ${file_script} -t <type> -e <path>" 
	errlog
	errlog "Read the key from standard input or pipe and write the wrapped key to"
	errlog "standard output."
	errlog
	errlog "  -p <path>"
	errlog "     Path to the directory that contains the temporary encryption key for"
	errlog "     the provisioning."
	errlog "     This option is for wrapping the keyring for provisioning."
	errlog "     If the key does not exist, it will be generated by this script."
	errlog "     The key for provisioning is ${FILE_PROVISIONING_KEY}."
	errlog
	errlog "  -u <path>"
	errlog "     Path to the directory that contains the temporary encryption key for"
	errlog "     the update. Specify this option if the keyring is updated."
	errlog "     The keys for update are ${FILE_KEYRING_UPDATE_ENC_KEY} and ${FILE_KEYRING_UPDATE_MAC_KEY}."
	errlog
	errlog "  -t <type>"
	errlog "     Type of user key to be wrapped."
	errlog "     The supported user key types are:"
	errlog "         ${AES_128_KEY_TYPE}"
	errlog "         ${AES_256_KEY_TYPE}"
	errlog "         ${HMAC_SHA1_KEY_TYPE}"
	errlog "         ${HMAC_SHA256_KEY_TYPE}"
	errlog "         ${RSA_1024_KEY_TYPE_PRV}"
	errlog "         ${RSA_1024_KEY_TYPE_PUB}"
	errlog "         ${RSA_2048_KEY_TYPE_PRV}"
	errlog "         ${RSA_2048_KEY_TYPE_PUB}"
	errlog
	errlog "  -e <path>"
	errlog "     Path to the directory that contains the temporary encryption key for"
	errlog "     injecting the user key."
	errlog "     The keys for injection are ${FILE_USERKEY_INJECT_ENC_KEY} and ${FILE_USERKEY_INJECT_MAC_KEY}."
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
		"${RSA_1024_KEY_TYPE_PRV}")
			func_wrap_prvkey "${RSA_1024_KEY_SIZE}"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			func_wrap_pubkey "${RSA_1024_KEY_SIZE}"
			;;
		"${RSA_2048_KEY_TYPE_PRV}")
			func_wrap_prvkey "${RSA_2048_KEY_SIZE}"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			func_wrap_pubkey "${RSA_2048_KEY_SIZE}"
			;;
		"${BOOT_KEYRING_TYPE}")
			func_wrap_keyring "${BOOT_KEYRING_SIZE}"
			;;
		*)  errlog "[error] ${file_script}: Unsupported key type \"${TYPE_TARGET_KEY}\"."
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

file_script="$(basename ${0})"

if [ -f /dev/stdin ] || [ -p /dev/stdin ]; then
	cat "/dev/stdin" > "${TMP_FILE}"
fi

while getopts :t:p:u:e:f: OPT
do
	case "${OPT}" in
		t) typ_tag_key="${OPTARG}"
			;;
		p) dirpath_prv="${OPTARG}"
			;;
		u) dirpath_upd="${OPTARG}"
			;;
		e) dirpath_inj="${OPTARG}"
			;;
		f) filepath_key="${OPTARG}"
			;;
		:|\?) func_usage_exit
			;;
	esac
done

if [ ! -s "${TMP_FILE}" ] || [ -z "${typ_tag_key}" ]; then
	func_usage_exit
fi

TYPE_TARGET_KEY="$(echo "${typ_tag_key}" | tr '[:upper:]' '[:lower:]')"

if [ ! -z "${dirpath_prv}" ]; then
	FILEPATH_PROVISIONING_KEY="${dirpath_prv%/}/${FILE_PROVISIONING_KEY}"
fi

if [ ! -z "${dirpath_upd}" ]; then
	FILEPATH_KEYRING_UPDATE_ENC_KEY="${dirpath_upd%/}/${FILE_KEYRING_UPDATE_ENC_KEY}"
	FILEPATH_KEYRING_UPDATE_MAC_KEY="${dirpath_upd%/}/${FILE_KEYRING_UPDATE_MAC_KEY}"
fi

if [ ! -z "${dirpath_inj}" ]; then
	FILEPATH_USERKEY_INJECT_ENC_KEY="${dirpath_inj%/}/${FILE_USERKEY_INJECT_ENC_KEY}"
	FILEPATH_USERKEY_INJECT_MAC_KEY="${dirpath_inj%/}/${FILE_USERKEY_INJECT_MAC_KEY}"
fi

if [ ! -z "${filepath_key}" ]; then
	cat "${filepath_key}" > "${TMP_FILE}"
	if [ 0 != $? ]; then func_usage_exit; fi
fi

# Call func_main
func_main
