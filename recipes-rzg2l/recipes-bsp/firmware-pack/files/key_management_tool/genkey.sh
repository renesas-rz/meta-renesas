#!/bin/sh

. ./utility.sh

#*******************************************************************************
# Function Name: func_gen_cmnkey
# Description  : Generate the common key.
# Arguments    : ${1} - key length in bytes
#              : stdout - Generated random numbers in text or binary
# Return Value : 0 or 1
#*******************************************************************************
func_gen_cmnkey ()
{
	local len_tag_key="${1}"

	if [ "true" != "${FLAG_HEX_COMMON}" ]; then
		openssl rand "${len_tag_key}"
	else
		openssl rand -hex "${len_tag_key}"
	fi

	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to generate Common Key."
		return 1
	fi
	return 0
}

#*******************************************************************************
# Function Name: func_gen_rsa_pri
# Description  : Generate the rsa private key.
# Arguments    : ${1} - key length in bytes
#              : stdout - rsa private key in PEM format
# Return Value : 0 or 1
#*******************************************************************************
func_gen_rsa_pri ()
{
	local len_tag_key="$(expr ${1} \* 8)"

	openssl genrsa -f4 "${len_tag_key}" 2>/dev/null

	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to generate RSA Private Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_gen_rsa_pub
# Description  : Generate the rsa public key.
# Arguments    : stdin - rsa private key in PEM format
#              : stdout - rsa public key in PEM format
# Return Value : 0 or 1
#*******************************************************************************
func_gen_rsa_pub ()
{
	local rsa_pri_key="$(cat)"

	echo "${rsa_pri_key}" | openssl rsa -pubout 2>/dev/null

	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to generate RSA Public Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_gen_p256
# Description  : Generate the ecc private key.
# Arguments    : ${1} - key generation option
#              : stdout - ecc private key in PEM format
# Return Value : 0 or 1
#*******************************************************************************
func_gen_ecc_pri ()
{
	openssl ecparam -genkey -name ${1} -noout 2>/dev/null

	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to generate ECC Private Key."
		return 1
	fi

	return 0
}

#*******************************************************************************
# Function Name: func_gen_ecc_pub
# Description  : Generate the ecc p256 public key.
# Arguments    : stdin - ecc private key in PEM format
#              : stdout - ecc public key in PEM format
# Return Value : 0 or 1
#*******************************************************************************
func_gen_ecc_pub ()
{
	openssl ec -pubout 2>/dev/null

	if [ 0 != $? ]; then
		errlog "[error] ${SCRIPT_NAME}: Failed to generate ECC Public Key."
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
	errlog "This script is for generating RZ/G2 security key."
	errlog "Version ${TOOL_VERSION}"
	errlog
	errlog "Usage:"
	errlog "  ${SCRIPT_NAME} -t <type> [-x]"
	errlog
	errlog "Write the generated key to standard output."
	errlog "If the type of key generated is a public key, the private key is read from standard input or pipe."
	errlog
	errlog "  -t <type>"
	errlog "     Type of key to be generated."
	errlog "     The supported key types are:"
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
	errlog "         ${ECC_P192_KEY_TYPE_PRI}"
	errlog "         ${ECC_P192_KEY_TYPE_PUB}"
	errlog "         ${ECC_P224_KEY_TYPE_PRI}"
	errlog "         ${ECC_P224_KEY_TYPE_PUB}"
	errlog "         ${ECC_P256_KEY_TYPE_PRI}"
	errlog "         ${ECC_P256_KEY_TYPE_PUB}"
	errlog "         ${ECC_BSI_P512_KEY_TYPE_PRI}"
	errlog "         ${ECC_BSI_P512_KEY_TYPE_PUB}"
	errlog
	errlog "  -x"
	errlog "     Output common key in hex text."
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
	if [ -z "${TYPE_TARGET_KEY}" ]; then
		errlog "[error] ${SCRIPT_NAME}: The key type is not specified."
		func_usage_exit
	fi

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
		"${RSA_1024_KEY_TYPE_PRI}")
			func_gen_rsa_pri "${RSA_1024_KEY_SIZE}"
			;;
		"${RSA_1024_KEY_TYPE_PUB}")
			func_gen_rsa_pub < "${TMP_FILE}"
			;;
		"${RSA_2048_KEY_TYPE_PRI}")
			func_gen_rsa_pri "${RSA_2048_KEY_SIZE}"
			;;
		"${RSA_2048_KEY_TYPE_PUB}")
			func_gen_rsa_pub  < "${TMP_FILE}"
			;;
		"${RSA_4096_KEY_TYPE_PRI}")
			func_gen_rsa_pri "${RSA_4096_KEY_SIZE}"
			;;
		"${RSA_4096_KEY_TYPE_PUB}")
			func_gen_rsa_pub  < "${TMP_FILE}"
			;;
		"${ECC_P192_KEY_TYPE_PRI}")
			func_gen_ecc_pri prime192v1
			;;
		"${ECC_P192_KEY_TYPE_PUB}")
			func_gen_ecc_pub  < "${TMP_FILE}"
			;;
		"${ECC_P224_KEY_TYPE_PRI}")
			func_gen_ecc_pri secp224r1
			;;
		"${ECC_P224_KEY_TYPE_PUB}")
			func_gen_ecc_pub  < "${TMP_FILE}"
			;;
		"${ECC_P256_KEY_TYPE_PRI}")
			func_gen_ecc_pri prime256v1
			;;
		"${ECC_P256_KEY_TYPE_PUB}")
			func_gen_ecc_pub  < "${TMP_FILE}"
			;;
		"${ECC_BSI_P512_KEY_TYPE_PRI}")
			func_gen_ecc_pri brainpoolP512r1
			;;
		"${ECC_BSI_P512_KEY_TYPE_PUB}")
			func_gen_ecc_pub  < "${TMP_FILE}"
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

while getopts :t:xh OPT
do
	case "${OPT}" in
		t) typ_tag_key="${OPTARG}"
			;;
		x) flg_hex_cmn="true"
			;;
		:|\?) func_usage_exit
			;;
	esac
done

TYPE_TARGET_KEY="$(echo "${typ_tag_key}" | tr '[:upper:]' '[:lower:]')"
FLAG_HEX_COMMON="${flg_hex_cmn}"

# Call func_main
func_main
