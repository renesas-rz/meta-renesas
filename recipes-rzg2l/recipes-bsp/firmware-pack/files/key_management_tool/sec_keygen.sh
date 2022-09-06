#!/bin/sh

. ./utility.sh

#*******************************************************************************
# Function Name: func_find_dirnames_match_pttrn
# Description  : Find the directory names that matches the pattern.
#              : The pattern is "major minor trace".
# Arguments    : ${1} - directory path to search
#              : ${2} - major number
#              : ${3} - minor number
#              : ${4} - trace number
#              : stdout - directory name that matches the pattern
# Return Value : 0 or others
#*******************************************************************************
func_find_dirnames_match_pttrn ()
{
	local dirname=""; local parentdir="${1}"
	
	local major="${2}"; local minor="${3}"; local trace="${4}"
	
	if [ ! -d "${parentdir}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Unable to find the directory \"${parentdir}\"."
		return 1
	fi
	
	dirname="$(cd "${parentdir}"; find ./ -maxdepth 1 -type d | \
		grep "^\.\/${major:-[0-9]\+}\.${minor:-\([0-9]\+\)}\.${trace:-\([0-9]\+\)}.*$" | \
		sed 's/^\.\///')"
	
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to find the directory name that matches the pattern."
		return 1
	fi
	
	echo "${dirname}"
	
	return 0
}

#*******************************************************************************
# Function Name: func_extract_pttrn_from_dirname
# Description  : Extract the pattern from the directory name.
# Arguments    : ${1} - directory name
#              : stdout - pattern number
# Return Value : 0 or 1
#*******************************************************************************
func_extract_pttrn_from_dirname ()
{
	local dirname="${1}"; local pttrn_nums=""
	
	if [ ! -z "${dirname}" ]; then

		pttrn_nums="$(echo "${dirname}" | sed -r -n -e "s/^([0-9]+)(\.([0-9]+))?(\.([0-9]+))?$/\1 \3 \5/p")"

		if [ -z "${pttrn_nums}" ]; then
			errlog "[error] ${SCRIPT_NAME}: Incorrect directory name pattern \"${dirname}\"."
			return 1
		fi
		echo -n "${pttrn_nums}"
	fi
	return 0
}

#*******************************************************************************
# Function Name: func_from_pttrn_to_dirname
# Description  : Create a directory name from the input pattern.
# Arguments    : ${1} - major number
#              : ${2} - minor number
#              : ${3} - trace number
#              : stdout - directory name
# Return Value : 0 or 1
#*******************************************************************************
func_from_pttrn_to_dirname ()
{
	local dirname=""
	
	local major=0; local minor=0; local trace=0;

	if [ ! -z "${1}" ]; then major="${1}"; fi
	if [ ! -z "${2}" ]; then minor="${2}"; fi
	if [ ! -z "${3}" ]; then trace="${3}"; fi

	dirname="${major}.${minor}.${trace}"

	func_extract_pttrn_from_dirname "${dirname}" >/dev/null
	if [ 0 != $? ]; then
		return 1
	fi

	echo "${dirname}"

	return 0
}

#*******************************************************************************
# Function Name: func_get_pttrn_newest_dirname
# Description  : Choose the newest directory that matches the pattern number.
# Arguments    : ${1} - directory path to search
#              : ${2} - directory name
#              : stdout - directory name pattern
# Return Value : 0 or 1
#*******************************************************************************
func_get_pttrn_newest_dirname ()
{
	local parentdir="${1}"; local dirname="${2}"; local pttrn_value="";

	pttrn_value="$(func_extract_pttrn_from_dirname ${dirname})"
	if [ 0 != $? ]; then
		return 1
	fi

	list_matched_dirname="$(func_find_dirnames_match_pttrn "${parentdir}" ${pttrn_value})"
	if [ 0 != $? ]; then
		return 1
	fi

	list_dirname_number="$(echo "${list_matched_dirname}" | sed -r -n -e "s/^([0-9]+)(\.([0-9]+))(\.([0-9]+)).*$/\1 \3 \5/p")"

	echo "${list_dirname_number}" | sort -k 1n,1 -k 2n,2 | tail -n 1

	return 0
}

#*******************************************************************************
# Function Name: func_update_major_number
# Description  : Update the major number of the newest directory.
# Arguments    : ${1} - directory path to search
#              : stdout - directory name
# Return Value : 0 or 1
#*******************************************************************************
func_update_major_number ()
{
	local parentdir="${1}"; local pattern=""

	local trace=0; local minor=0; local major=0;

	pattern="$(func_get_pttrn_newest_dirname "${parentdir}")"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Unable to find the newest directory."
		return 1
	fi
	
	if [ -n "${pattern}" ]; then
		set -- ${pattern}
		major="${1}"
		major=$(( major + 1 ))
	fi
	
	func_from_pttrn_to_dirname "${major}" "${minor}" "${trace}"
}

#*******************************************************************************
# Function Name: func_update_minor_number
# Description  : Update the minor number of the directory that matches the pattern.
# Arguments    : ${1} - directory path to search
#              : ${2} - major number
#              : ${3} - minor number
#              : ${4} - trace number
#              : stdout - directory name
# Return Value : 0 or 1
#*******************************************************************************
func_update_minor_number ()
{
	local parentdir="${1}"; local pattern=""
	
	local major="${2}"; local minor="${3}"; local trace="${4}";

	if [ -z "${major}${minor}${trace}" ]; then
		errlog "[error] ${SCRIPT_NAME}: The version pattern is empty."
		return 1
	fi

	func_from_pttrn_to_dirname ${major} ${minor} ${trace} >/dev/null
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to create the directory name from the pattern \"${major}" "${minor}" "${trace}\"."
		return 1
	fi

	pattern="$(func_get_pttrn_newest_dirname "${parentdir}" ${major})"
	if [ 0 != $? ] || [ -z "${pattern}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Unable to find the latest directory."
		return 1
	fi

	set -- ${pattern}
	
	trace=${minor}; minor=${2}; major=${1};

	minor="$(( minor + 1 ))"

	func_from_pttrn_to_dirname ${major} ${minor} ${trace}
}

#*******************************************************************************
# Function Name: func_get_key_filepath
# Description  : Return the path of the key file.
# Arguments    : ${1} - key type
#              : ${2} - key name
#              : ${3} - directory path where the key is generated
#              : ${4} - key number (may be empty)
#              : stdout - key file path
# Return Value : 0 or 1
#*******************************************************************************
func_get_key_filepath ()
{
	local fpath_gen_key=""
	
	local key_type="${1}"; local key_name="${2}"; local dirpath="${3}"; local key_num="${4}"

	if [ -z "${key_num}" ] || [ "${key_num}" -le 1 ]; then
		key_num=""
	fi

	fpath_gen_key="${dirpath%/}/${key_name}${key_num}"

	case "${key_type}" in

		"${AES_128_KEY_TYPE}")
			fpath_gen_key="${fpath_gen_key}.txt"
			;;
		"${AES_256_KEY_TYPE}")
			fpath_gen_key="${fpath_gen_key}.txt"
			;;
		"${HMAC_SHA1_KEY_TYPE}")
			fpath_gen_key="${fpath_gen_key}.txt"
			;;
		"${HMAC_SHA256_KEY_TYPE}")
			fpath_gen_key="${fpath_gen_key}.txt"
			;;
		"${RSA_1024_KEY_TYPE_PRI}")
			fpath_gen_key="${fpath_gen_key}.pem"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			fpath_gen_key="${fpath_gen_key}_pub.pem"
			;;
		"${RSA_2048_KEY_TYPE_PRI}")
			fpath_gen_key="${fpath_gen_key}.pem"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			fpath_gen_key="${fpath_gen_key}_pub.pem"
			;;
		"${RSA_4096_KEY_TYPE_PRI}")
			fpath_gen_key="${fpath_gen_key}.pem"
			;;
		"${RSA_4096_KEY_TYPE_PUB}")
			fpath_gen_key="${fpath_gen_key}_pub.pem"
			;;
		"${ECC_P192_KEY_TYPE_PRI}")
			fpath_gen_key="${fpath_gen_key}.pem"
			;;
		"${ECC_P192_KEY_TYPE_PUB}")
			fpath_gen_key="${fpath_gen_key}_pub.pem"
			;;
		"${ECC_P224_KEY_TYPE_PRI}")
			fpath_gen_key="${fpath_gen_key}.pem"
			;;
		"${ECC_P224_KEY_TYPE_PUB}")
			fpath_gen_key="${fpath_gen_key}_pub.pem"
			;;
		"${ECC_P256_KEY_TYPE_PRI}")
			fpath_gen_key="${fpath_gen_key}.pem"
			;;
		"${ECC_P256_KEY_TYPE_PUB}")
			fpath_gen_key="${fpath_gen_key}_pub.pem"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PRI}")
			fpath_gen_key="${fpath_gen_key}.pem"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PUB}")
			fpath_gen_key="${fpath_gen_key}_pub.pem"
			;;
		"${KEY_UPDATE_KEY_TYPE}")
			fpath_gen_key="${fpath_gen_key}.txt"
			;;
		"${KEY_UPDATE_IV0_TYPE}")
			fpath_gen_key="${fpath_gen_key}.txt"
			;;
		*)
			errlog "[error] ${SCRIPT_NAME}: Unsupported key type \"${key_type}\"."
			return 1
			;;
	esac
	
	echo "${fpath_gen_key}"

	return 0
}

#*******************************************************************************
# Function Name: func_generate_keyfile
# Description  : Generate a key and return the path of the key file.
# Arguments    : ${1} - key type
#              : ${2} - key name
#              : ${3} - directory path where the key is generated
#              : ${4} - key number (may be empty)
#              : stdout - path of the generated key file
# Return Value : 0 or 1
#*******************************************************************************
func_generate_keyfile ()
{
	local fpath_gen_key=""; local fpath_pri_key=""
	
	local key_type="${1}"; local key_name="${2}"; local dirpath="${3}"; local key_num="${4}"
	
	fpath_gen_key="$(func_get_key_filepath "${key_type}" "${key_name}" "${dirpath}" "${key_num}")"
	if [ 0 != $? ]; then
		return 1
	fi
	
	case "${key_type}" in

		"${AES_128_KEY_TYPE}")
			./genkey.sh -t "${AES_128_KEY_TYPE}" -x > "${fpath_gen_key}"
			;;
		"${AES_256_KEY_TYPE}")
			./genkey.sh -t "${AES_256_KEY_TYPE}" -x > "${fpath_gen_key}"
			;;
		"${HMAC_SHA1_KEY_TYPE}")
			./genkey.sh -t "${HMAC_SHA1_KEY_TYPE}" -x > "${fpath_gen_key}"
			;;
		"${HMAC_SHA256_KEY_TYPE}")
			./genkey.sh -t "${HMAC_SHA256_KEY_TYPE}" -x > "${fpath_gen_key}"
			;;
		"${RSA_1024_KEY_TYPE_PRI}")
			./genkey.sh -t "${RSA_1024_KEY_TYPE_PRI}" > "${fpath_gen_key}"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			fpath_pri_key="$(func_get_key_filepath "${RSA_1024_KEY_TYPE_PRI}" "${key_name}" "${dirpath}" "${key_num}")"
			./genkey.sh -t "${RSA_1024_KEY_TYPE_PUB}" < "${fpath_pri_key}" > "${fpath_gen_key}"
			;;
		"${RSA_2048_KEY_TYPE_PRI}")
			./genkey.sh -t "${RSA_2048_KEY_TYPE_PRI}" > "${fpath_gen_key}"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			fpath_pri_key="$(func_get_key_filepath "${RSA_2048_KEY_TYPE_PRI}" "${key_name}" "${dirpath}" "${key_num}")"
			./genkey.sh -t "${RSA_2048_KEY_TYPE_PUB}" < "${fpath_pri_key}" > "${fpath_gen_key}"
			;;
		"${RSA_4096_KEY_TYPE_PRI}")
			./genkey.sh -t "${RSA_4096_KEY_TYPE_PRI}" > "${fpath_gen_key}"
			;;
		"${RSA_4096_KEY_TYPE_PUB}")
			fpath_pri_key="$(func_get_key_filepath "${RSA_4096_KEY_TYPE_PRI}" "${key_name}" "${dirpath}" "${key_num}")"
			./genkey.sh -t "${RSA_4096_KEY_TYPE_PUB}" < "${fpath_pri_key}" > "${fpath_gen_key}"
			;;
		"${ECC_P192_KEY_TYPE_PRI}")
			./genkey.sh -t "${ECC_P192_KEY_TYPE_PRI}" > "${fpath_gen_key}"
			;;
		"${ECC_P192_KEY_TYPE_PUB}")
			fpath_pri_key="$(func_get_key_filepath "${ECC_P192_KEY_TYPE_PRI}" "${key_name}" "${dirpath}" "${key_num}")"
			./genkey.sh -t "${ECC_P192_KEY_TYPE_PUB}" < "${fpath_pri_key}" > "${fpath_gen_key}"
			;;
		"${ECC_P224_KEY_TYPE_PRI}")
			./genkey.sh -t "${ECC_P224_KEY_TYPE_PRI}" > "${fpath_gen_key}"
			;;
		"${ECC_P224_KEY_TYPE_PUB}")
			fpath_pri_key="$(func_get_key_filepath "${ECC_P224_KEY_TYPE_PRI}" "${key_name}" "${dirpath}" "${key_num}")"
			./genkey.sh -t "${ECC_P224_KEY_TYPE_PUB}" < "${fpath_pri_key}" > "${fpath_gen_key}"
			;;
		"${ECC_P256_KEY_TYPE_PRI}")
			./genkey.sh -t "${ECC_P256_KEY_TYPE_PRI}" > "${fpath_gen_key}"
			;;
		"${ECC_P256_KEY_TYPE_PUB}")
			fpath_pri_key="$(func_get_key_filepath "${ECC_P256_KEY_TYPE_PRI}" "${key_name}" "${dirpath}" "${key_num}")"
			./genkey.sh -t "${ECC_P256_KEY_TYPE_PUB}" < "${fpath_pri_key}" > "${fpath_gen_key}"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PRI}")
			./genkey.sh -t "${ECC_BSI_P512_KEY_TYPE_PRI}" > "${fpath_gen_key}"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PUB}")
			fpath_pri_key="$(func_get_key_filepath "${ECC_BSI_P512_KEY_TYPE_PRI}" "${key_name}" "${dirpath}" "${key_num}")"
			./genkey.sh -t "${ECC_BSI_P512_KEY_TYPE_PUB}" < "${fpath_pri_key}" > "${fpath_gen_key}"
			;;
		"${KEY_UPDATE_KEY_TYPE}")
			./genkey.sh -t "${AES_128_KEY_TYPE}" -x > "${fpath_gen_key}"  
			./genkey.sh -t "${AES_128_KEY_TYPE}" -x >> "${fpath_gen_key}"  
			;;
		"${KEY_UPDATE_IV0_TYPE}")
			./genkey.sh -t "${AES_128_KEY_TYPE}" -x > "${fpath_gen_key}"  
			;;			
		*)
			errlog "[error] ${SCRIPT_NAME}: Unsupported key type \"${key_type}\"."
			return 1
			;;
	esac

	if [ 0 != $? ]; then
		return 1
	fi

	echo "${fpath_gen_key}"
	
	return 0
}

#*******************************************************************************
# Function Name: func_encrypt_keyfile
# Description  : Encrypt a key and return the path of the encrypted key file.
# Arguments    : ${1} - key type
#              : ${2} - path of the encrypted key file
#              : ${3} - path to the directory where the wrapping key is stored
#              : stdout - encrypted key path
# Return Value : 0 or 1
#*******************************************************************************
func_encrypt_keyfile ()
{
	local fname_gen_key=""; local fpath_enc_key=""
	
	local key_type="${1}"; local fpath_gen_key="${2}"; local dirpath_refkey="${3}";

	fname_gen_key="${fpath_gen_key##*/}"
	fpath_enc_key="${fpath_gen_key%/*}/encrypted-${fname_gen_key%.*}.bin"

	case "${key_type}" in

		"${AES_128_KEY_TYPE}")
			./wrapkey.sh -t "${AES_128_KEY_TYPE}" -p "${dirpath_refkey}" -x < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${AES_256_KEY_TYPE}")
			./wrapkey.sh -t "${AES_256_KEY_TYPE}" -p "${dirpath_refkey}" -x < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${HMAC_SHA1_KEY_TYPE}")
			./wrapkey.sh -t "${HMAC_SHA1_KEY_TYPE}" -p "${dirpath_refkey}" -x < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${HMAC_SHA256_KEY_TYPE}")
			./wrapkey.sh -t "${HMAC_SHA256_KEY_TYPE}" -p "${dirpath_refkey}" -x < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_1024_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${RSA_1024_KEY_TYPE_PRI}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${RSA_1024_KEY_TYPE_PUB}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_2048_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${RSA_2048_KEY_TYPE_PRI}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${RSA_2048_KEY_TYPE_PUB}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_4096_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${RSA_4096_KEY_TYPE_PRI}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_4096_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${RSA_4096_KEY_TYPE_PUB}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P192_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${ECC_P192_KEY_TYPE_PRI}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P192_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${ECC_P192_KEY_TYPE_PUB}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P224_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${ECC_P224_KEY_TYPE_PRI}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P224_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${ECC_P224_KEY_TYPE_PUB}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P256_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${ECC_P256_KEY_TYPE_PRI}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P256_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${ECC_P256_KEY_TYPE_PUB}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${ECC_BSI_P512_KEY_TYPE_PRI}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${ECC_BSI_P512_KEY_TYPE_PUB}" -p "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${KEY_UPDATE_KEY_TYPE}")
			./wrapkey.sh -t "${AES_256_KEY_TYPE}" -p "${dirpath_refkey}" -x < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		*)
			errlog "[error] ${SCRIPT_NAME}: Unsupported key type \"${key_type}\"."
			return 1
			;;
	esac

	if [ 0 != $? ]; then
		return 1
	else
		echo "${fpath_enc_key}"
		return 0
	fi
}

#*******************************************************************************
# Function Name: func_update_keyfile
# Description  : Encrypt a key and return the path of the encrypted key file.
# Arguments    : ${1} - key type
#              : ${2} - path of the encrypted key file
#              : ${3} - path to the directory where the wrapping key is stored
#              : stdout - encrypted key path
# Return Value : 0 or 1
#*******************************************************************************
func_update_keyfile ()
{
	local fname_gen_key=""; local fpath_enc_key=""
	
	local key_type="${1}"; local fpath_gen_key="${2}"; local dirpath_refkey="${3}";

	fname_gen_key="${fpath_gen_key##*/}"
	fpath_enc_key="${fpath_gen_key%/*}/encrypted-${fname_gen_key%.*}.bin"

	case "${key_type}" in

		"${AES_128_KEY_TYPE}")
			./wrapkey.sh -t "${AES_128_KEY_TYPE}" -u "${dirpath_refkey}" -x < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${AES_256_KEY_TYPE}")
			./wrapkey.sh -t "${AES_256_KEY_TYPE}" -u "${dirpath_refkey}" -x < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${HMAC_SHA1_KEY_TYPE}")
			./wrapkey.sh -t "${HMAC_SHA1_KEY_TYPE}" -u "${dirpath_refkey}" -x < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${HMAC_SHA256_KEY_TYPE}")
			./wrapkey.sh -t "${HMAC_SHA256_KEY_TYPE}" -u "${dirpath_refkey}" -x < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_1024_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${RSA_1024_KEY_TYPE_PRI}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${RSA_1024_KEY_TYPE_PUB}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_2048_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${RSA_2048_KEY_TYPE_PRI}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${RSA_2048_KEY_TYPE_PUB}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_4096_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${RSA_4096_KEY_TYPE_PRI}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${RSA_4096_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${RSA_4096_KEY_TYPE_PUB}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P192_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${ECC_P192_KEY_TYPE_PRI}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P192_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${ECC_P192_KEY_TYPE_PUB}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P224_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${ECC_P224_KEY_TYPE_PRI}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P224_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${ECC_P224_KEY_TYPE_PUB}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P256_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${ECC_P256_KEY_TYPE_PRI}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_P256_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${ECC_P256_KEY_TYPE_PUB}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PRI}")
			./wrapkey.sh -t "${ECC_BSI_P512_KEY_TYPE_PRI}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${ECC_BSI_P512_KEY_TYPE_PUB}" -u "${dirpath_refkey}" < "${fpath_gen_key}" > "${fpath_enc_key}"
			;;
		*)
			errlog "[error] ${SCRIPT_NAME}: Unsupported key type \"${key_type}\"."
			return 1
			;;
	esac

	if [ 0 != $? ]; then
		return 1
	else
		echo "${fpath_enc_key}"
		return 0
	fi
}

#*******************************************************************************
# Function Name: func_create_bootkey
# Description  : Create the boot key.
# Arguments    : stdout - directory path where the boot key is generated
# Return Value : 0 or 1
#*******************************************************************************
func_create_bootkey ()
{
	local dirname_bootkey=""; local dirpath_bootkey=""
	
	local filepath_gen_enckey=""; local filepath_enc_cmnkey=""; local filepath_gen_sigkey=""
	
	mkdir -p "${DIRPATH_KEYGEN_ROOT}"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to create the directory \"${DIRPATH_KEYGEN_ROOT}\"."
		return 1
	fi

	dirname_bootkey="$(func_update_major_number "${DIRPATH_KEYGEN_ROOT}")"
	if [ 0 != $? ] || [ -z "${dirname_bootkey}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to update the major number of the directory name."
		return 1
	fi

	dirpath_bootkey="${DIRPATH_KEYGEN_ROOT%/}/${dirname_bootkey}"

	mkdir -p "${dirpath_bootkey}"
	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to create the directory \"${dirpath_bootkey}\"."
		return 1
	fi

	for fname in ${LIST_BOOTPRG_VERIFY_ENC_KEY}; do

		filepath_gen_enckey="$(func_generate_keyfile "${BOOTPRG_VERIFY_ENC_KEY_TYPE}" "${fname}" "${dirpath_bootkey}")"
		if [ 0 != $? ] || [ ! -s "${filepath_gen_enckey}" ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to generate the ${fname}."
			return 1
		fi

		filepath_enc_cmnkey="$(func_encrypt_keyfile "${BOOTPRG_VERIFY_ENC_KEY_TYPE}" "${filepath_gen_enckey}" "${DIRPATH_USER_FACTORY_PROG_KEY}")"
		if [ 0 != $? ] || [ ! -s "${filepath_enc_cmnkey}" ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to wrap the \"${filepath_gen_enckey}\"."
			return 1
		fi

	done

	for fname in ${LIST_BOOTPRG_VERIFY_SIG_KEY}; do

		filepath_gen_sigkey="$(func_generate_keyfile "${BOOTPRG_VERIFY_SIG_KEY_TYPE}" "${fname}" "${dirpath_bootkey}")"
		if [ 0 != $? ] || [ ! -s "${filepath_gen_sigkey}" ]; then
			errlog "[error] ${SCRIPT_NAME}: Failed to generate the ${fname}."
			return 1
		fi

	done

	filepath_gen_enckey="$(func_generate_keyfile "${KEY_UPDATE_KEY_TYPE}" "${FILE_KEY_UPDATE_KEY}" "${dirpath_bootkey}")"
	if [ 0 != $? ] || [ ! -s "${filepath_gen_enckey}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to generate the ${FILE_KEY_UPDATE_KEY}."
		return 1
	fi

	filepath_enc_cmnkey="$(func_encrypt_keyfile "${KEY_UPDATE_KEY_TYPE}" "${filepath_gen_enckey}" "${DIRPATH_USER_FACTORY_PROG_KEY}")"
	if [ 0 != $? ] || [ ! -s "${filepath_enc_cmnkey}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to wrap the \"${filepath_gen_enckey}\"."
		return 1
	fi

	filepath_gen_enckey="$(func_generate_keyfile "${KEY_UPDATE_IV0_TYPE}" "${FILE_KEY_UPDATE_IV0}" "${dirpath_bootkey}")"
	if [ 0 != $? ] || [ ! -s "${filepath_gen_enckey}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to generate the ${FILE_KEY_UPDATE_IV0}."
		return 1
	fi

	echo "${dirpath_bootkey}"

	return 0
}

#*******************************************************************************
# Function Name: func_create_userkey
# Description  : Create the user keys for Basic cryptographic features
# Arguments    : ${1} - directory name where the boot key is stored
#              : stdout - directory path where the use keys were generated
# Return Value : 0 or 1
#*******************************************************************************
func_create_userkey ()
{
	local dirname_bootkey=""; local dirpath_bootkey=""; local dirpath_userkey="";
	
	local filepath_gen_key=""; local filepath_enc_key=""
	
	local dirname_pttrn="${1}"; local pttrn_dirname=""; local num_key_typ=""

	pttrn_dirname="$(func_get_pttrn_newest_dirname "${DIRPATH_KEYGEN_ROOT}" "${dirname_pttrn}")"
	if [ 0 != $? ] || [ -z "${pttrn_dirname}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Unable to find the latest directory."
		return 1
	fi

	dirname_bootkey="$(func_from_pttrn_to_dirname ${pttrn_dirname})"
	if [ 0 != $? ] || [ -z "${dirname_bootkey}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to create the directory name from the pattern \"${pttrn_dirname}\"."
		return 1
	fi

	dirpath_bootkey="${DIRPATH_KEYGEN_ROOT%/}/${dirname_bootkey}"
	if [ ! -d "${dirpath_bootkey}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Unable to find the directory \"${dirpath_bootkey}\"."
		return 1
	fi

	symlink_userkey="${dirpath_bootkey%/}/${DIR_USER_KEY}"
	dirpath_userkey="${dirpath_bootkey%/}/${DIR_USER_KEY}"_"$(date '+%Y%m%d-%H%M%S')"
	
	num_key_typ="$(echo "${LIST_GENERATION_USERKEY}" | wc -l)"

	for i in ${LIST_GENERATION_USERKEY}; do

		set -- $(echo "${i}" | sed -e "s/,/ /g");

		local typ_gen_key="${1}"; local name_gen_key="${2}"; local num_gen_key="${3:-"0"}"

		for j in $(awk "BEGIN{for(x=1; x<=${num_gen_key}; ++x) print x}"); do

			if [ ! -d "${dirpath_userkey}" ]; then
				mkdir -p "${dirpath_userkey}"
				if [ 0 != $? ]; then
					errlog "[error] ${SCRIPT_NAME}: Failed to create the directory \"${dirpath_userkey}\"."
					return 1
				fi
			fi
			
			filepath_gen_key="$(func_generate_keyfile "${typ_gen_key}" "${name_gen_key}" "${dirpath_userkey}" ${j})"

			if [ 0 != $? ] || [ ! -s "${filepath_gen_key}" ]; then
				errlog "[error] ${SCRIPT_NAME}: Failed to generate the ${name_gen_key}."
				return 1
			fi

			filepath_enc_key="$(func_encrypt_keyfile ${typ_gen_key} "${filepath_gen_key}" "${DIRPATH_USER_FACTORY_PROG_KEY}")";

			if [ 0 != $? ] || [ ! -s "${filepath_enc_key}" ]; then
				errlog "[error] ${SCRIPT_NAME}: Failed to wrap the \"${filepath_gen_key}\"."
				return 1
			fi
		done
	done

	ln -nfs "${dirpath_userkey}" "${symlink_userkey}"
	
	echo "${dirpath_userkey}"

	return 0
}

#*******************************************************************************
# Function Name: func_update_userkey
# Description  : Update the user keys for Basic cryptographic features
# Arguments    : ${1} - directory name where the boot key is stored
#              : stdout - directory path where the use keys were generated
# Return Value : 0 or 1
#*******************************************************************************
func_update_userkey ()
{
	local dirname_bootkey=""; local dirpath_bootkey=""; local dirpath_userkey="";
	
	local filepath_gen_key=""; local filepath_enc_key=""
	
	local dirname_pttrn="${1}"; local pttrn_dirname=""; local num_key_typ=""

	pttrn_dirname="$(func_get_pttrn_newest_dirname "${DIRPATH_KEYGEN_ROOT}" "${dirname_pttrn}")"
	if [ 0 != $? ] || [ -z "${pttrn_dirname}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Unable to find the latest directory."
		return 1
	fi

	dirname_bootkey="$(func_from_pttrn_to_dirname ${pttrn_dirname})"
	if [ 0 != $? ] || [ -z "${dirname_bootkey}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to create the directory name from the pattern \"${pttrn_dirname}\"."
		return 1
	fi

	dirpath_bootkey="${DIRPATH_KEYGEN_ROOT%/}/${dirname_bootkey}"
	if [ ! -d "${dirpath_bootkey}" ]; then
		errlog "[error] ${SCRIPT_NAME}: Unable to find the directory \"${dirpath_bootkey}\"."
		return 1
	fi

	symlink_userkey="${dirpath_bootkey%/}/${DIR_USER_KEY}"
	dirpath_userkey="${dirpath_bootkey%/}/${DIR_USER_KEY}"_"$(date '+%Y%m%d-%H%M%S')"
	
	num_key_typ="$(echo "${LIST_GENERATION_USERKEY}" | wc -l)"

	for i in ${LIST_GENERATION_USERKEY}; do

		set -- $(echo "${i}" | sed -e "s/,/ /g");

		local typ_gen_key="${1}"; local name_gen_key="${2}"; local num_gen_key="${3:-"0"}"

		for j in $(awk "BEGIN{for(x=1; x<=${num_gen_key}; ++x) print x}"); do

			if [ ! -d "${dirpath_userkey}" ]; then
				mkdir -p "${dirpath_userkey}"
				if [ 0 != $? ]; then
					errlog "[error] ${SCRIPT_NAME}: Failed to create the directory \"${dirpath_userkey}\"."
					return 1
				fi
			fi
			
			filepath_gen_key="$(func_generate_keyfile "${typ_gen_key}" "${name_gen_key}" "${dirpath_userkey}" ${j})"

			if [ 0 != $? ] || [ ! -s "${filepath_gen_key}" ]; then
				errlog "[error] ${SCRIPT_NAME}: Failed to generate the ${name_gen_key}."
				return 1
			fi

			filepath_enc_key="$(func_update_keyfile ${typ_gen_key} "${filepath_gen_key}" "${dirpath_bootkey}")";

			if [ 0 != $? ] || [ ! -s "${filepath_enc_key}" ]; then
				errlog "[error] ${SCRIPT_NAME}: Failed to wrap the \"${filepath_gen_key}\"."
				return 1
			fi
		done
	done

	ln -nfs "${dirpath_userkey}" "${symlink_userkey}"
	
	echo "${dirpath_userkey}"

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
	errlog "This script is for generating RZ/G2 security key."
	errlog "Version ${TOOL_VERSION}"
	errlog
	errlog "Usage:"
	errlog "    ${SCRIPT_NAME} [-t <storage-path>]"
	errlog
	errlog "Generate keys for RZ/G2 security in the specified directory."
	errlog
	errlog "  -t <storage-path>"
	errlog "     The path of the directory for the key generation."
	errlog "     If this option is not specified, \"${DIRPATH_KEYGEN_ROOT}\" is created."
	errlog

	exit 1
}

#*******************************************************************************
# Function Name: func_main
# Description  : Call the key generation function for each specified key type.
# Arguments    : none
# Return Value : 0 or 1
#*******************************************************************************
func_main ()
{
	local dirpath=""; local dirname="${DIRNAME_PATTERN}"

	if [ 'create' = "${FLAG_SEC_KEYGEN}" ]; then
	
		dirpath="$(func_create_bootkey)"
		if [ 0 != $? ]; then
			exit 1
		fi
	elif [ 'update' = "${FLAG_SEC_KEYGEN}" ]; then
		dirpath="$(func_update_userkey "${dirname}")"
		if [ 0 != $? ]; then
			exit 1
		fi
	fi
	
	echo "${dirpath}"
	
	exit 0
}

#*******************************************************************************
# Startup
#*******************************************************************************
cd "$(dirname ${0})"

. ./config.sh

SCRIPT_NAME="$(basename ${0})"

FLAG_SEC_KEYGEN='create'

while getopts :t:d:u OPT
do
	case "${OPT}" in
		t) dirpath_keygen="${OPTARG}"
			;;
		d) dirname_pttrn="${OPTARG}"
			;;
		u) FLAG_SEC_KEYGEN='update'
			;;
		:|\?) func_usage_exit
			;;
	esac
done

DIRNAME_PATTERN="${dirname_pttrn}"

if [ -n "${dirpath_keygen}" ]; then
	DIRPATH_KEYGEN_ROOT="${dirpath_keygen}"
fi
DIRPATH_USER_FACTORY_PROG_KEY="${DIRPATH_KEYGEN_ROOT%/}/${DIR_USER_FACTORY_PROG}"

# Call func_main
func_main
