#!/bin/sh

. ./utility.sh

#*******************************************************************************
# Function Name: func_find_dirname_matching
# Description  : Find the directory name that matches the pattern.
#              : The pattern is "major minor trace".
# Arguments    : ${1} - Directory path to search
#              : ${2} - Major number
#              : ${3} - Minor number
#              : ${4} - Trace number
#              : stdout - Directory name that matches the pattern
# Return Value : 0 or 1
#*******************************************************************************
func_find_dirname_matching ()
{
	if [ -d "${1}" ]; then
		(cd "${1}"; find ./ -maxdepth 1 -type d | grep "^\.\/${2:-[0-9]\+}\.${3:-\([0-9]\+\)}\.${4:-\([0-9]\+\)}.*$" | sed 's/^\.\///')
	fi
}

#*******************************************************************************
# Function Name: func_extract_dirname_pattern
# Description  : Extract the pattern from the directory name.
# Arguments    : ${1} - Directory name
#              : stdout - Pattern
# Return Value : 0 or 1
#*******************************************************************************
func_extract_dirname_pattern ()
{
	if [ ! -z "${1}" ]; then
	
		pttrn_nums="$(echo "${1}" | sed -r -n -e "s/^([0-9]+)(\.([0-9]+))?(\.([0-9]+))?$/\1 \3 \5/p")"
		
		if [ -z "${pttrn_nums}" ]; then
			return 1
		fi
		echo -n "${pttrn_nums}"
	fi
	return 0
}

#*******************************************************************************
# Function Name: func_from_pattern_to_dirname
# Description  : Create a directory name from a pattern.
# Arguments    : ${1} - Major number
#              : ${2} - Minor number
#              : ${3} - Trace number
#              : stdout - Directory name
# Return Value : 0 or 1
#*******************************************************************************
func_from_pattern_to_dirname ()
{
	local pttrn_major=0; local pttrn_minor=0; local pttrn_trace=0;
	
	if [ ! -z "${1}" ]; then pttrn_major=${1}; fi
	if [ ! -z "${2}" ]; then pttrn_minor=${2}; fi
	if [ ! -z "${3}" ]; then pttrn_trace=${3}; fi
	
	local dirname="${pttrn_major}.${pttrn_minor}.${pttrn_trace}"
	
	func_extract_dirname_pattern ${dirname} >/dev/null
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Incorrect directory name pattern \"${dirname}\"."
		return 1
	fi
	
	echo ${dirname}
	
	return 0
}

#*******************************************************************************
# Function Name: func_search_for_latest_dirname
# Description  : Find for the latest directory name that matches the pattern.
#              : Directory name pattern is "major.minor.trace".
# Arguments    : ${1} - Directory path to search
#              : ${2} - Directory name pattern
#              : stdout - Latest directory name
# Return Value : 0 or 1
#*******************************************************************************
func_search_for_latest_dirname ()
{
	local dirpath_parent="${1}" 
	
	local pttrn_value="$(func_extract_dirname_pattern ${2})" 
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Incorrect directory name pattern \"${2}\"."
		return 1
	fi

	list_matched_dirname="$(func_find_dirname_matching "${dirpath_parent}" ${pttrn_value})"
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to match the directory name pattern."
		return 1
	fi
	
	list_dirname_number="$(echo "${list_matched_dirname}" | sed -r -n -e "s/^([0-9]+)(\.([0-9]+))(\.([0-9]+)).*$/\1 \3 \5/p")"
	
	echo "${list_dirname_number}" | sort -k 1n,1 -k 2n,2 | tail -n 1
	
	return 0
}

#*******************************************************************************
# Function Name: func_update_major_number
# Description  : Update the major number of the latest directory.
# Arguments    : ${1} - Directory path to search
#              : stdout - Directory name
# Return Value : 0 or 1
#*******************************************************************************
func_update_major_number ()
{
	local dirpath_parent="${1}"

	local pttrn_dirname="$(func_search_for_latest_dirname "${dirpath_parent}")"
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Unable to find the latest directory."
		return 1
	fi
	
	if [ -z "${pttrn_dirname}" ]; then
		echo "0.0.0"
		return 0
	else
		set -- ${pttrn_dirname}
		local pttrn_trace=0; local pttrn_minor=0; local pttrn_major=${1};
		
		pttrn_trace="${pttrn_trace}"
		pttrn_minor="${pttrn_minor}"
		pttrn_major=$(( pttrn_major + 1 ))
		
		func_from_pattern_to_dirname "${pttrn_major}" "${pttrn_minor}" "${pttrn_trace}"
	fi
}

#*******************************************************************************
# Function Name: func_update_minor_number
# Description  : Update the minor number of the directory that matches the pattern.
# Arguments    : ${1} - Directory path to search
#              : ${2} - Major number
#              : ${3} - Minor number
#              : ${4} - Trace number
#              : stdout - Directory name
# Return Value : 0 or 1
#*******************************************************************************
func_update_minor_number ()
{
	local dirpath_parent="${1}"
	local pttrn_major=${2}; local pttrn_minor=${3}; local pttrn_trace=${4};

	if [ -z "${pttrn_major}${pttrn_minor}${pttrn_trace}" ]; then
			errlog "[error] ${file_script}: The version pattern is empty."
			return 1
	else
		func_from_pattern_to_dirname ${pttrn_major} ${pttrn_minor} ${pttrn_trace} >/dev/null
		if [ 0 != $? ]; then
			errlog "[error] ${file_script}: Failed to create the directory name from the pattern \"${pttrn_major}" "${pttrn_minor}" "${pttrn_trace}\"."
			return 1
		fi
		
		local pttrn_dirname="$(func_search_for_latest_dirname "${dirpath_parent}" ${pttrn_major})"
		if [ 0 != $? ] || [ -z "${pttrn_dirname}" ]; then
			errlog "[error] ${file_script}: Unable to find the latest directory."
			return 1
		fi
		
		set -- ${pttrn_dirname}
		pttrn_trace=${pttrn_minor}; pttrn_minor=${2}; pttrn_major=${1};
		
		pttrn_trace="${pttrn_trace}"
		pttrn_minor="$(( pttrn_minor + 1 ))"
		pttrn_major="${pttrn_major}"
		
		func_from_pattern_to_dirname ${pttrn_major} ${pttrn_minor} ${pttrn_trace}
	fi
}

#*******************************************************************************
# Function Name: func_get_genkey_path
# Description  : Generate a key and return the path of the key.
# Arguments    : ${1} - Key type
#              : ${2} - Directory path where the key is generated
#              : ${3} - Key number
#              : stdout - Generated key path
# Return Value : 0 or 1
#*******************************************************************************
func_get_genkey_path ()
{
	local typ_tag_key="${1}"
	local dirpath_key="${2}"
	local num_tag_key=""
	
	if [ ! -z "${3}" ] && [ "${3}" -gt 1 ]; then
		num_tag_key="${3}"
	fi
	
	local FILEPATH_AES_128_KEY="${dirpath_key%/}/${FILE_AES_128_KEY%.*}${num_tag_key}.${FILE_AES_128_KEY##*.}"
	local FILEPATH_AES_256_KEY="${dirpath_key%/}/${FILE_AES_256_KEY%.*}${num_tag_key}.${FILE_AES_256_KEY##*.}"
	local FILEPATH_HMAC_SHA1_KEY="${dirpath_key%/}/${FILE_HMAC_SHA1_KEY%.*}${num_tag_key}.${FILE_HMAC_SHA1_KEY##*.}"
	local FILEPATH_HMAC_SHA256_KEY="${dirpath_key%/}/${FILE_HMAC_SHA256_KEY%.*}${num_tag_key}.${FILE_HMAC_SHA256_KEY##*.}"
	local FILEPATH_RSA_1024_PRV_KEY="${dirpath_key%/}/${FILE_RSA_1024_PRV_KEY%.*}${num_tag_key}.${FILE_RSA_1024_PRV_KEY##*.}"
	local FILEPATH_RSA_1024_PUB_KEY="${dirpath_key%/}/${FILE_RSA_1024_PUB_KEY%.*}${num_tag_key}.${FILE_RSA_1024_PUB_KEY##*.}"
	local FILEPATH_RSA_2048_PRV_KEY="${dirpath_key%/}/${FILE_RSA_2048_PRV_KEY%.*}${num_tag_key}.${FILE_RSA_2048_PRV_KEY##*.}"
	local FILEPATH_RSA_2048_PUB_KEY="${dirpath_key%/}/${FILE_RSA_2048_PUB_KEY%.*}${num_tag_key}.${FILE_RSA_2048_PUB_KEY##*.}"
	local FILEPATH_BOOT_KEYRING="${dirpath_key%/}/${FILE_BOOT_KEYRING}"
	
	local filepath_gen_key=""

	case "${typ_tag_key}" in
	
		"${AES_128_KEY_TYPE}")
			filepath_gen_key="${FILEPATH_AES_128_KEY}"
			./genkey.sh -t "${typ_tag_key}" > "${FILEPATH_AES_128_KEY}"
			;;
		"${AES_256_KEY_TYPE}")
			filepath_gen_key="${FILEPATH_AES_256_KEY}"
			./genkey.sh -t "${typ_tag_key}" > "${FILEPATH_AES_256_KEY}"
			;;
		"${HMAC_SHA1_KEY_TYPE}")
			filepath_gen_key="${FILEPATH_HMAC_SHA1_KEY}"
			./genkey.sh -t "${typ_tag_key}" > "${FILEPATH_HMAC_SHA1_KEY}"
			;;
		"${HMAC_SHA256_KEY_TYPE}")
			filepath_gen_key="${FILEPATH_HMAC_SHA256_KEY}"
			./genkey.sh -t "${typ_tag_key}" > "${FILEPATH_HMAC_SHA256_KEY}"
			;;
		"${RSA_1024_KEY_TYPE_PRV}")
			filepath_gen_key="${FILEPATH_RSA_1024_PRV_KEY}"
			./genkey.sh -t "${typ_tag_key}" > "${FILEPATH_RSA_1024_PRV_KEY}"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			filepath_gen_key="${FILEPATH_RSA_1024_PUB_KEY}"
			./genkey.sh -t "${typ_tag_key}" < "${FILEPATH_RSA_1024_PRV_KEY}" > "${FILEPATH_RSA_1024_PUB_KEY}"
			;;
		"${RSA_2048_KEY_TYPE_PRV}")
			filepath_gen_key="${FILEPATH_RSA_2048_PRV_KEY}"
			./genkey.sh -t "${typ_tag_key}" > "${FILEPATH_RSA_2048_PRV_KEY}"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			filepath_gen_key="${FILEPATH_RSA_2048_PUB_KEY}"
			./genkey.sh -t "${typ_tag_key}" < "${FILEPATH_RSA_2048_PRV_KEY}" > "${FILEPATH_RSA_2048_PUB_KEY}"
			;;
		"${BOOT_KEYRING_TYPE}")
			filepath_gen_key="${FILEPATH_BOOT_KEYRING}"
			./keyring.sh -d "${dirpath_keyring}" > "${FILEPATH_BOOT_KEYRING}"
			;;
		*)
			errlog "[error] ${file_script}: Unsupported key type \"${typ_tag_key}\"."
			return 1
			;;
	esac
	
	if [ 0 != $? ]; then
		return 1
	else
		echo "${filepath_gen_key}"
		return 0
	fi
}

#*******************************************************************************
# Function Name: func_get_wrapkey_path
# Description  : Wraps a key and returns the path to that key.
# Arguments    : ${1} - Key type
#              : ${2} - Key path to be wrapped
#              : ${3} - The path of the directory referenced for wrapping
#              : stdout - Wrapped key path
# Return Value : 0 or 1
#*******************************************************************************
func_get_wrapkey_path ()
{
	local typ_tag_key="${1}"

	local filepath_gen_key="${2}"
	local filepath_enc_key="${filepath_gen_key%.*}_Enc.bin"

	local dirpath_ref_key="${3}"

	case "${typ_tag_key}" in
		
		"${AES_128_KEY_TYPE}")
			./wrapkey.sh -t "${AES_128_KEY_TYPE}" -e "${dirpath_ref_key}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			;;
		"${AES_256_KEY_TYPE}")
			./wrapkey.sh -t "${AES_256_KEY_TYPE}" -e "${dirpath_ref_key}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			;;
		"${HMAC_SHA1_KEY_TYPE}")
			./wrapkey.sh -t "${HMAC_SHA1_KEY_TYPE}" -e "${dirpath_ref_key}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			;;
		"${HMAC_SHA256_KEY_TYPE}")
			./wrapkey.sh -t "${HMAC_SHA256_KEY_TYPE}" -e "${dirpath_ref_key}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			;;
		"${RSA_1024_KEY_TYPE_PRV}")
			./wrapkey.sh -t "${RSA_1024_KEY_TYPE_PRV}" -e "${dirpath_ref_key}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${RSA_1024_KEY_TYPE_PUB}" -e "${dirpath_ref_key}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			;;
		"${RSA_2048_KEY_TYPE_PRV}")
			./wrapkey.sh -t "${RSA_2048_KEY_TYPE_PRV}" -e "${dirpath_ref_key}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			./wrapkey.sh -t "${RSA_2048_KEY_TYPE_PUB}" -e "${dirpath_ref_key}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			;;
		"${BOOT_KEYRING_TYPE}")
			if [ -z "${dirpath_ref_key}" ]; then
				./wrapkey.sh -t "${BOOT_KEYRING_TYPE}" -p "${DIRPATH_PROVISIONING_KEY}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			else
				./wrapkey.sh -t "${BOOT_KEYRING_TYPE}" -u "${dirpath_ref_key}" < "${filepath_gen_key}" > "${filepath_enc_key}"
			fi
			;;
		*)
			errlog "[error] ${file_script}: Unsupported key type \"${typ_tag_key}\"."
			return 1
			;;
	esac
	
	if [ 0 != $? ]; then
		return 1
	else
		echo "${filepath_enc_key}"
		return 0
	fi
}

#*******************************************************************************
# Function Name: func_create_keyring
# Description  : Create the keyring.
# Arguments    : stdout - Directory path where the keyring was generated
# Return Value : 0 or 1
#*******************************************************************************
func_create_keyring ()
{
	mkdir -p "${DIRPATH_KEYGEN_ROOT}"
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to create the directory \"${DIRPATH_KEYGEN_ROOT}\"."
		return 1
	fi
	
	local dirname_keyring="$(func_update_major_number ${DIRPATH_KEYGEN_ROOT})"
	if [ 0 != $? ] || [ -z "${dirname_keyring}" ]; then
		errlog "[error] ${file_script}: Failed to update the major number of the directory name."
		return 1
	fi
	
	local dirpath_keyring="${DIRPATH_KEYGEN_ROOT%/}/${dirname_keyring}"
	
	mkdir "${dirpath_keyring}"
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to create the directory \"${dirpath_keyring}\"."
		return 1
	fi
	
	local filepath_gen_keyring="$(func_get_genkey_path "${BOOT_KEYRING_TYPE}" "${dirpath_keyring}")"
	
	if [ 0 != $? ] || [ ! -s "${filepath_gen_keyring}" ]; then
		errlog "[error] ${file_script}: Failed to generate the Keyring."
		return 1
	fi
	
	local filepath_enc_keyring="$(func_get_wrapkey_path "${BOOT_KEYRING_TYPE}" "${filepath_gen_keyring}")"
	
	if [ 0 != $? ] || [ ! -s "${filepath_enc_keyring}" ]; then
		errlog "[error] ${file_script}: Failed to wrap the \"${filepath_gen_keyring}\"."
		return 1
	fi
	
	echo "${dirpath_keyring}"
	
	return 0
}

#*******************************************************************************
# Function Name: func_update_keyring
# Description  : Update the keyring.
# Arguments    : ${1} - Directory name where the keyring of the update source is stored
#              : stdout - Directory path where the keyring was generated
# Return Value : 0 or 1
#*******************************************************************************
func_update_keyring ()
{
	local dirname_pttrn="${1}"
	
	local pttrn_dirname="$(func_search_for_latest_dirname "${DIRPATH_KEYGEN_ROOT}" "${dirname_pttrn}")"
	if [ 0 != $? ] || [ -z "${pttrn_dirname}" ]; then
		errlog "[error] ${file_script}: Unable to find the latest directory."
		return 1
	fi
	
	local dirname_current="$(func_from_pattern_to_dirname ${pttrn_dirname})"
	if [ 0 != $? ] || [ -z "${dirname_current}" ]; then
		errlog "[error] ${file_script}: Failed to create the latest directory name from the pattern \"${pttrn_dirname}\"."
		return 1
	fi
	
	local dirpath_current="${DIRPATH_KEYGEN_ROOT%/}/${dirname_current}"
	if [ ! -d "${dirpath_current}" ]; then
		errlog "[error] ${file_script}: Unable to find the directory \"${dirname_current}\"."
		return 1
	fi
	
	local dirname_keyring="$(func_update_minor_number "${DIRPATH_KEYGEN_ROOT}" ${pttrn_dirname})"
	if [ 0 != $? ] || [ -z "${dirname_keyring}" ]; then
		errlog "[error] ${file_script}: Failed to update the minor number of the directory name."
		return 1
	fi
	
	local dirpath_keyring="${DIRPATH_KEYGEN_ROOT%/}/${dirname_keyring}"

	mkdir "${dirpath_keyring}"
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to create the directory \"${dirpath_keyring}\"."
		return 1
	fi

	local filepath_gen_keyring="$(func_get_genkey_path "${BOOT_KEYRING_TYPE}" "${dirpath_keyring}")"
	
	if [ 0 != $? ] || [ ! -s "${filepath_gen_keyring}" ]; then
		errlog "[error] ${file_script}: Failed to generate the Keyring."
		return 1
	fi
	
	local filepath_enc_keyring="$(func_get_wrapkey_path "${BOOT_KEYRING_TYPE}" "${filepath_gen_keyring}" "${dirpath_current}")"

	if [ 0 != $? ] || [ ! -s "${filepath_enc_keyring}" ]; then
		errlog "[error] ${file_script}: Failed to wrap the \"${filepath_gen_keyring}\"."
		return 1
	fi
	
	echo "${dirpath_keyring}"
	
	return 0
}

#*******************************************************************************
# Function Name: func_create_userkey
# Description  : Create the user keys for Basic cryptographic features
# Arguments    : ${1} - Directory name where the keyring is stored
#              : stdout - Directory path where the use keys were generated
# Return Value : 0 or 1
#*******************************************************************************
func_create_userkey ()
{
	local dirname_pttrn="${1}"
	
	pttrn_dirname="$(func_search_for_latest_dirname "${DIRPATH_KEYGEN_ROOT}" "${dirname_pttrn}")"
	if [ 0 != $? ] || [ -z "${pttrn_dirname}" ]; then
		errlog "[error] ${file_script}: Unable to find the latest directory."
		return 1
	fi
	
	local dirname_keyring="$(func_from_pattern_to_dirname ${pttrn_dirname})"
	if [ 0 != $? ] || [ -z "${dirname_keyring}" ]; then
		errlog "[error] ${file_script}: Failed to create the directory name from the pattern \"${pttrn_dirname}\"."
		return 1
	fi

	local dirpath_keyring="${DIRPATH_KEYGEN_ROOT%/}/${dirname_keyring}"
	if [ ! -d "${dirpath_keyring}" ]; then
		errlog "[error] ${file_script}: Unable to find the directory \"${dirpath_keyring}\"."
		return 1
	fi

	local dirpath_userkey="${dirpath_keyring%/}/${DIR_USER_KEY}"
	
	mkdir "${dirpath_userkey}"
	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to create the new directory \"${dirpath_userkey}\"."
		return 1
	fi
	
	local num_key_typ="$(echo "${LIST_GENERATION_USERKEY}" | wc -l)"
	
	for i in ${LIST_GENERATION_USERKEY}; do
	
		set -- $(echo "${i}" | sed -e "s/,/ /g");
		
		local typ_gen_key="${1}"; local num_gen_key="${2:-"0"}"
		
		for j in $(awk "BEGIN{for(x=1; x<=${num_gen_key}; ++x) print x}"); do
			
			local filepath_gen_key="$(func_get_genkey_path "${typ_gen_key}" "${dirpath_userkey}" ${j})"
			
			if [ 0 != $? ] || [ ! -s "${filepath_gen_key}" ]; then
				errlog "[error] ${file_script}: Failed to generate the User Key."
				return 1
			fi
			
			local filepath_enc_key="$(func_get_wrapkey_path ${typ_gen_key} "${filepath_gen_key}" "${dirpath_keyring}")"; 
			
			if [ 0 != $? ] || [ ! -s "${filepath_enc_key}" ]; then
				errlog "[error] ${file_script}: Failed to wrap the \"${filepath_gen_key}\"."
				return 1
			fi
		done
	done
	
	echo "${dirpath_keyring}"
	
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
	errlog "This script is for generating RZ/G2 security keys."
	errlog
	errlog "Usage:"
	errlog "    ${file_script} [-t <storage-path>] [[-u | -e] [-d <name>]]"
	errlog
	errlog "Generate keys for RZ/G2 security in the specified directory."
	errlog
	errlog "  -t <storage-path>"
	errlog "     The Path of the directory for the key generation."
	errlog "     If this option is not specified, \"${DIRPATH_KEYGEN_ROOT}\" directory is created."
	errlog
	errlog "  -u"
	errlog "     Specify this option when updating the keyring"
	errlog
	errlog "  -e"
	errlog "     Specify this option when only user keys are generated."
	errlog
	errlog "  -d <name>"
	errlog "     The name of the target directory when the keyring updating or"
	errlog "     user key  generation."
	errlog "     If this option is not specified, the latest directory is targeted."
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
	local dirname_pttrn="${1}"
	local dirpath_genkey=""
	
	if [ 'create' = "${FLG_TSIP_KEYGEN}" ]; then

		dirpath_genkey="$(func_create_keyring)"
		if [ 0 != $? ]; then
			exit 1
		fi
		dirname_pttrn="$(basename ${dirpath_genkey})"
	fi
	if [ 'update' = "${FLG_TSIP_KEYGEN}" ]; then

		dirpath_genkey="$(func_update_keyring "${dirname_pttrn}")"
		if [ 0 != $? ]; then
			exit 1
		fi
		dirname_pttrn="$(basename ${dirpath_genkey})"
	fi

	dirpath_genkey="$(func_create_userkey "${dirname_pttrn}")"
	if [ 0 != $? ]; then
		exit 1
	fi
	
	echo "${dirpath_genkey}"
	
	exit 0
}

#*******************************************************************************
# Startup
#*******************************************************************************
cd "$(dirname ${0})"

. ./config.sh

file_script="$(basename ${0})"

flg_key_gen='create'

while getopts :t:d:ues OPT
do
	case "${OPT}" in
		t) dirpath_prd="${OPTARG}"
			;;
		u) flg_key_gen='update'
			;;
		e) flg_key_gen='inject'
			;;
		s) flg_key_gen='show'
			;;
		d) dirname_ptn="${OPTARG}"
			;;
		:|\?) func_usage_exit
			;;
	esac
done

FLG_TSIP_KEYGEN="${flg_key_gen}"

if [ ! -z "${dirpath_prd}" ]; then
	DIRPATH_KEYGEN_ROOT="${dirpath_prd}"
fi

DIRPATH_PROVISIONING_KEY="${DIRPATH_KEYGEN_ROOT%/}/${DIR_PROVISIONING_KEY}"

# Call func_main
func_main "${dirname_ptn}"
