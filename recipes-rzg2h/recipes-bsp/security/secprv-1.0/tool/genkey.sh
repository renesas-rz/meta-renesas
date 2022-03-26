#!/bin/sh

. ./utility.sh

#*******************************************************************************
# Function Name: func_gen_cmnkey
# Description  : Generate the common key.
# Arguments    : ${1} - key length in bytes
#              : stdout - key size random binary numbers
# Return Value : 0 or 1
#*******************************************************************************
func_gen_cmnkey ()
{
	local len_tag_key="${1}"

	openssl rand "${len_tag_key}"

	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to generate Common Key."
		return 1
	fi
	return 0
}

#*******************************************************************************
# Function Name: func_gen_prvkey
# Description  : Generate the rsa private key.
# Arguments    : ${1} - key length in bytes
#              : stdout - rsa private key in PEM format
# Return Value : 0 or 1
#*******************************************************************************
func_gen_prvkey ()
{
	local len_tag_key="$(expr ${1} \* 8)"

	openssl genrsa -f4 "${len_tag_key}" 2>/dev/null

	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to generate RSA Private Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_gen_pubkey
# Description  : Generate the rsa public key.
# Arguments    : stdin - rsa private key in PEM format
#              : stdout - rsa public key in PEM format
# Return Value : 0 or 1
#*******************************************************************************
func_gen_pubkey ()
{
	local rsa_prv_key="$(cat)"

	echo "${rsa_prv_key}" | openssl rsa -pubout 2>/dev/null

	if [ 0 != $? ]; then
		errlog "[error] ${file_script}: Failed to generate RSA Public Key."
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
func_usage_exit ()
{
	errlog 
	errlog "This script is for generating RZ/G2 security keys."
	errlog 
	errlog "Usage:"
	errlog "  ${file_script} -t <type>"
	errlog
	errlog "Write the generated key to standard output."
	errlog "If the key type is ${RSA_1024_KEY_TYPE_PUB} or ${RSA_2048_KEY_TYPE_PUB}, read the private key from"
	errlog "standard input or pipe."
	errlog
	errlog "  -t <type>"
	errlog "     Type of key to be generated."
	errlog "     The supported key types are:"
	errlog "         ${AES_128_KEY_TYPE}"
	errlog "         ${AES_256_KEY_TYPE}"
	errlog "         ${HMAC_SHA1_KEY_TYPE}"
	errlog "         ${HMAC_SHA256_KEY_TYPE}"
	errlog "         ${RSA_1024_KEY_TYPE_PRV}"
	errlog "         ${RSA_1024_KEY_TYPE_PUB}"
	errlog "         ${RSA_2048_KEY_TYPE_PRV}"
	errlog "         ${RSA_2048_KEY_TYPE_PUB}"
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
	case "${TYPE_TARGET_KEY}" in

		"${AES_128_KEY_TYPE}")
			func_gen_cmnkey "${AES_128_KEY_SIZE}"
			;;
		"${AES_256_KEY_TYPE}")
			func_gen_cmnkey "${AES_256_KEY_SIZE}"
			;;
		"${HMAC_SHA1_KEY_TYPE}")
			func_gen_cmnkey "${HMAC_SHA1_KEY_SIZE}"
			;;
		"${HMAC_SHA256_KEY_TYPE}")
			func_gen_cmnkey "${HMAC_SHA256_KEY_SIZE}"
			;;
		"${RSA_1024_KEY_TYPE_PRV}")
			func_gen_prvkey "${RSA_1024_KEY_SIZE}"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			func_gen_pubkey < "${TMP_FILE}"
			;;
		"${RSA_2048_KEY_TYPE_PRV}")
			func_gen_prvkey "${RSA_2048_KEY_SIZE}"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			func_gen_pubkey  < "${TMP_FILE}"
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

while getopts :t:f: OPT
do
	case "${OPT}" in
		t) typ_tag_key="${OPTARG}"
			;;
		f) filepath_key="${OPTARG}"
			;;
		:|\?) func_usage_exit
			;;
	esac
done

if [ -z "${typ_tag_key}" ]; then
	func_usage_exit
fi

TYPE_TARGET_KEY="$(echo "${typ_tag_key}" | tr '[:upper:]' '[:lower:]')"

if [ ! -z "${filepath_key}" ]; then
	cat "${filepath_key}" > "${TMP_FILE}"
	if [ 0 != $? ]; then func_usage_exit; fi
fi

# Call func_main
func_main
