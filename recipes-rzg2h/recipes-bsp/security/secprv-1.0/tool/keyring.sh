#!/bin/sh

. ./utility.sh

#*******************************************************************************
# Function Name: func_exists_key
# Description  : Checks if a key of the specified type and name exists. 
#              : If the key does not exist, create it.
# Arguments    : ${1} - key type
#              : ${2} - key file path
# Return Value : 0 or 1
#*******************************************************************************
func_exists_key ()
{
	local typ_tag_key="${1}"
	local filepath_key="${2}"

	if [ ! -s "${filepath_key}" ]; then

		./genkey.sh -t "${typ_tag_key}" > "${filepath_key}"

		if [ 0 != $? ] || [ ! -s "${filepath_key}" ]; then
			errlog "[error] ${file_script}: Failed to generate ${filepath_key}."
			return 1;
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
	errlog "This script is for generating RZ/G2 security keyring."
	errlog
	errlog "Usage:"
	errlog "    ${file_script} -d <path>"
	errlog
	errlog "  -d <path>"
	errlog "      Path to the directory where the generated keyring is output."
	errlog "      The file name of the generated keyring is ${FILE_BOOT_KEYRING}."
	errlog
	errlog "      The key files generated for the keyring are:"
	errlog "        * ${FILE_BOOTPRG_VERIFY_ENC_KEY}"
	errlog "            - Key to encrypt the program in Ttemporary Encryption."
	errlog "        * ${FILE_BOOTPRG_VERIFY_SIG_KEY}"
	errlog "            - Key to sign the program in Temporary Encryption."
	errlog "            - This key is not included in the keyring."
	errlog "        * ${FILE_BOOTPRG_VERIFY_VER_KEY}"
	errlog "            - Key to validate the program in Re-Encryption."
	errlog "        * ${FILE_KEYRING_UPDATE_ENC_KEY}"
	errlog "            - Key to wrap the next keyring in Keyring Update."
	errlog "        * ${FILE_KEYRING_UPDATE_MAC_KEY}"
	errlog "            - Key to validate MAC of the next keyring in Keyring Update."
	errlog "        * ${FILE_USERKEY_INJECT_ENC_KEY}"
	errlog "            - Key to wrap the user key in Key Injection."
	errlog "        * ${FILE_USERKEY_INJECT_MAC_KEY}"
	errlog "            - Key to validate MAC of the user key in Key Injection."
	errlog

	exit 1
}

#*******************************************************************************
# Function Name: func_main
# Description  : Create the Keyring.
# Arguments    : none
# Return Value : 0 or 1
#*******************************************************************************
func_main ()
{
	mkdir -p "${DIRPATH_BOOT_KEYRING}"
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Unable to create directory ${DIRPATH_BOOT_KEYRING} ."
		exit 1
	fi

	func_exists_key "${AES_256_KEY_TYPE}" "${FILEPATH_BOOTPRG_VERIFY_ENC_KEY}"
	if [ 0 != $? ]; then exit 1; fi

	func_exists_key "${RSA_2048_KEY_TYPE_PRV}" "${FILEPATH_BOOTPRG_VERIFY_SIG_KEY}"
	if [ 0 != $? ]; then exit 1; fi

	func_exists_key "${RSA_2048_KEY_TYPE_PUB}" "${FILEPATH_BOOTPRG_VERIFY_VER_KEY}" < "${FILEPATH_BOOTPRG_VERIFY_SIG_KEY}"
	if [ 0 != $? ]; then exit 1; fi

	func_exists_key "${AES_128_KEY_TYPE}" "${FILEPATH_KEYRING_UPDATE_ENC_KEY}"
	if [ 0 != $? ]; then exit 1; fi

	func_exists_key "${AES_128_KEY_TYPE}" "${FILEPATH_KEYRING_UPDATE_MAC_KEY}"
	if [ 0 != $? ]; then exit 1; fi

	func_exists_key "${AES_128_KEY_TYPE}" "${FILEPATH_USERKEY_INJECT_ENC_KEY}"
	if [ 0 != $? ]; then exit 1; fi

	func_exists_key "${AES_128_KEY_TYPE}" "${FILEPATH_USERKEY_INJECT_MAC_KEY}"
	if [ 0 != $? ]; then exit 1; fi

	local hex_bootprg_verify_enc_key="$(func_load_cmnkey "${BOOTPRG_VERIFY_ENC_KEY_SIZE}" < "${FILEPATH_BOOTPRG_VERIFY_ENC_KEY}")"
	if [ 0 != $? ]; then exit 1; fi

	local hex_bootprg_verify_ver_key="$(func_load_pubkey "${BOOTPRG_VERIFY_VER_KEY_SIZE}" < "${FILEPATH_BOOTPRG_VERIFY_VER_KEY}")"
	if [ 0 != $? ]; then exit 1; fi

	local hex_keyring_update_enc_key="$(func_load_cmnkey "${KEYRING_UPDATE_ENC_KEY_SIZE}" < "${FILEPATH_KEYRING_UPDATE_ENC_KEY}")"
	if [ 0 != $? ]; then exit 1; fi

	local hex_keyring_update_mac_key="$(func_load_cmnkey "${KEYRING_UPDATE_MAC_KEY_SIZE}" < "${FILEPATH_KEYRING_UPDATE_MAC_KEY}")"
	if [ 0 != $? ]; then exit 1; fi

	local hex_userkey_inject_enc_key="$(func_load_cmnkey "${USERKEY_INJECT_ENC_KEY_SIZE}" < "${FILEPATH_USERKEY_INJECT_ENC_KEY}")"
	if [ 0 != $? ]; then exit 1; fi

	local hex_userkey_inject_mac_key="$(func_load_cmnkey "${USERKEY_INJECT_MAC_KEY_SIZE}" < "${FILEPATH_USERKEY_INJECT_MAC_KEY}")"
	if [ 0 != $? ]; then exit 1; fi

	{
		func_zeropad 32
		echo -n "${hex_bootprg_verify_enc_key}"
		echo -n "${hex_bootprg_verify_ver_key}"
		func_zeropad 272
		echo -n "${hex_keyring_update_enc_key}"
		echo -n "${hex_keyring_update_mac_key}"
		echo -n "${hex_userkey_inject_enc_key}"
		echo -n "${hex_userkey_inject_mac_key}"
	} | func_hex_to_bin > "${FILEPATH_BOOT_KEYRING}"

	if [ ! -s "${FILEPATH_BOOT_KEYRING}" ]; then
		errlog "[error] ${file_script}: Failed to create ${FILEPATH_BOOT_KEYRING}."
		exit 1
	fi

	local key_size="$(wc -c < "${FILEPATH_BOOT_KEYRING}")"
	if [ ${key_size} -ne ${BOOT_KEYRING_SIZE} ]; then
		errlog "[error] ${file_script}: Keyring size is invalid."
		errlog "        The expected size is ${BOOT_KEYRING_SIZE}, actually ${key_size}."
		exit 1
	fi

	exit 0
}

#*******************************************************************************
# Startup
#*******************************************************************************
cd "$(dirname ${0})"

. ./config.sh

file_script="$(basename ${0})"

while getopts :d: OPT
do
	case "${OPT}" in
		d)  dirpath_keyring="${OPTARG}"
			;;
		:|\?)  func_usage_exit
			;;
	esac
done

if [ -z "${dirpath_keyring}" ]; then
	func_usage_exit
fi

DIRPATH_BOOT_KEYRING="${dirpath_keyring}"

FILEPATH_BOOT_KEYRING="${DIRPATH_BOOT_KEYRING%/}/${FILE_BOOT_KEYRING}"

FILEPATH_BOOTPRG_VERIFY_ENC_KEY="${DIRPATH_BOOT_KEYRING%/}/${FILE_BOOTPRG_VERIFY_ENC_KEY}"
FILEPATH_BOOTPRG_VERIFY_SIG_KEY="${DIRPATH_BOOT_KEYRING%/}/${FILE_BOOTPRG_VERIFY_SIG_KEY}"
FILEPATH_BOOTPRG_VERIFY_VER_KEY="${DIRPATH_BOOT_KEYRING%/}/${FILE_BOOTPRG_VERIFY_VER_KEY}"

FILEPATH_KEYRING_UPDATE_ENC_KEY="${DIRPATH_BOOT_KEYRING%/}/${FILE_KEYRING_UPDATE_ENC_KEY}"
FILEPATH_KEYRING_UPDATE_MAC_KEY="${DIRPATH_BOOT_KEYRING%/}/${FILE_KEYRING_UPDATE_MAC_KEY}"

FILEPATH_USERKEY_INJECT_ENC_KEY="${DIRPATH_BOOT_KEYRING%/}/${FILE_USERKEY_INJECT_ENC_KEY}"
FILEPATH_USERKEY_INJECT_MAC_KEY="${DIRPATH_BOOT_KEYRING%/}/${FILE_USERKEY_INJECT_MAC_KEY}"

# Call func_main
func_main
