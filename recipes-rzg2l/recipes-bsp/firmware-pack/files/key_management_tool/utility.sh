#!/bin/sh

if [ -z "${TMP_FILE}" ]; then
	TMP_FILE="$(mktemp)"
	if [ ! -f "${TMP_FILE}" ]; then
		echo "[error] utility.sh: Failed to create temporary file." >&2
		exit 1
	fi
	trap 'rm -f ${TMP_FILE}' EXIT # Command to delete temporary files when the script ends
fi

#*******************************************************************************
# Function Name: errlog
# Description  : Write logs to standard error
# Arguments    : ${1} - key length
# Return Value : none
#*******************************************************************************
errlog ()
{
	echo "${1}" 1>&2
	return 0
}

#*******************************************************************************
# Function Name: func_extract_rsaprm
# Description  : Extract parameters from PEM format RSA key.
# Arguments    : ${1} - rsa parameters
#              : stdin - rsa key in PEM format
#              : stdout - hexadecimal string of the rsa key parameter
# Return Value : 0 or 1
#*******************************************************************************
func_extract_rsaprm ()
{
	local txt_rsa_prms="${1}"

	local pem_rsa_key="$(cat)"

	local txt_rsa_key=""

	echo "${pem_rsa_key}" | grep -i "PRIVATE KEY" >/dev/null
	if [ 0 = $? ]; then
		txt_rsa_key="$(echo "${pem_rsa_key}" | openssl rsa -noout -text 2>/dev/null)"
	else
		txt_rsa_key="$(echo "${pem_rsa_key}" | openssl rsa -noout -text -pubin 2>/dev/null)"
	fi

	if [ $? != 0 ] || [ -z "${txt_rsa_key}" ]; then
		errlog "[error] utility.sh: Unable to load RSA key from PEM file."
		return 1
	fi

	local line_num_prm=""

	for txt_rsa_prm in ${txt_rsa_prms}; do
		line_num_prm="$(echo "${txt_rsa_key}" | grep -i "${txt_rsa_prm}:" -n | sed -e 's/:.*//g')"
		if [ 0 = $? ] && [ ! -z "${line_num_prm}" ]; then
			break;
		fi
	done

	if [ -z "${line_num_prm}" ]; then
		errlog "[error] utility.sh: RSA parameter cannot be found \"${txt_rsa_prms}\"."
		return 1
	fi

	txt_rsa_key="$(echo "${txt_rsa_key}" | tail -n +"${line_num_prm}")"

	echo "${txt_rsa_key}" | while read txt_line || [ -n "${txt_line}" ];
	do
		local txt_key_line="$(echo "${txt_line}" | sed "s/^\s*\(.*\)\s*$/\1/g")"
		echo -n "${txt_key_line}"

		local txt_end_code="$(echo "${txt_key_line}" | sed "s/^.*\(.\)$/\1/g")"
		if [ ":" != "${txt_end_code}" ]; then
			break
		fi
	done | sed -e "s/${txt_rsa_prm}:[ \t]*\([^ \t]*\).*/\1/i" | sed -e "s/://g" | sed -e "s/^00//g"

	return $?
}

#*******************************************************************************
# Function Name: func_load_rsa_pub
# Description  : Load the rsa public key parameter as a hexadecimal string
# Arguments    : ${1} - rsa key length in bytes
#              : stdin - rsa key in PEM format
#              : stdout - hexadecimal string of the rsa public key parameter
# Return Value : 0 or 1
#*******************************************************************************
func_load_rsa_pub ()
{
	local pem_rsa_key="$(cat)"

	local len_tag_key="$(expr ${1} \* 2)"

	if [ $? -ge 2 ];then
		errlog "[error] utility.sh: The expected value of the key length is invalid."
		return 1
	fi

	local hex_modulus="$(echo "${pem_rsa_key}" | func_extract_rsaprm "modulus")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The modulus parameter cannot be found."
		return 1
	fi

	if [ ${len_tag_key} -ne ${#hex_modulus} ]; then
		errlog "[error] utility.sh: The key length does not match the expected value."
		return 1
	fi

	local hex_exponent="$(echo "${pem_rsa_key}" | func_extract_rsaprm "exponent")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The exponent parameter cannot be found."
		return 1
	fi

	hex_exponent="$(printf "%08X" "${hex_exponent}")$(func_zeropad 12)"

	echo -n "${hex_modulus}${hex_exponent}"

	return 0
}

#*******************************************************************************
# Function Name: func_load_rsa_pri
# Description  : Load the rsa private key parameter as a hexadecimal string
# Arguments    : ${1} - rsa key length in bytes
#              : stdin - rsa private key in PEM format
#              : stdout - hexadecimal string of the rsa private key parameter
# Return Value : 0 or 1
#*******************************************************************************
func_load_rsa_pri ()
{
	local pem_rsa_key="$(cat)"

	local len_tag_key="$(expr ${1} \* 2)"

	if [ $? -ge 2 ];then
		errlog "[error] utility.sh: The expected value of the key length is invalid."
		return 1
	fi

	local hex_modulus="$(echo "${pem_rsa_key}" | func_extract_rsaprm "modulus")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The modulus parameter cannot be found."
		return 1
	fi

	if [ ${len_tag_key} -ne ${#hex_modulus} ]; then
		errlog "[error] utility.sh: The key length does not match the expected value."
		return 1
	fi

	local hex_exponent1="$(echo "${pem_rsa_key}" | func_extract_rsaprm "exponent1")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The exponent1 parameter cannot be found."
		return 1
	fi

	local hex_exponent2="$(echo "${pem_rsa_key}" | func_extract_rsaprm "exponent2")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The exponent2 parameter cannot be found."
		return 1
	fi

	local hex_prime1="$(echo "${pem_rsa_key}" | func_extract_rsaprm "prime1")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The prime1 parameter cannot be found."
		return 1
	fi

	local hex_prime2="$(echo "${pem_rsa_key}" | func_extract_rsaprm "prime2")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The prime2 parameter cannot be found."
		return 1
	fi

	local hex_coefficient="$(echo "${pem_rsa_key}" | func_extract_rsaprm "coefficient")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The coefficient parameter cannot be found."
		return 1
	fi

	echo -n "${hex_exponent2}${hex_prime2}${hex_exponent1}${hex_prime1}${hex_coefficient}"

	return 0
}

#*******************************************************************************
# Function Name: func_extract_ecdsaprm
# Description  : Extract parameters from PEM format ECDSA key.
# Arguments    : ${1} - ecdsa parameters
#              : stdin - ecdsa key in PEM format
#              : stdout - hexadecimal string of the ecdsa key parameter
# Return Value : 0 or 1
#*******************************************************************************
func_extract_ecdsaprm ()
{
	local txt_ecdsa_prms="${1}"

	local pem_ecdsa_key="$(cat)"

	local txt_ecdsa_key=""

	echo "${pem_ecdsa_key}" | grep -i "PRIVATE KEY" >/dev/null
	if [ 0 = $? ]; then
		txt_ecdsa_key="$(echo "${pem_ecdsa_key}" | openssl ec -text -noout 2>/dev/null)"
	else
		txt_ecdsa_key="$(echo "${pem_ecdsa_key}" | openssl ec -text -noout -pubin -conv_form uncompressed 2>/dev/null)"
	fi

	if [ $? != 0 ] || [ -z "${txt_ecdsa_key}" ]; then
		errlog "[error] utility.sh: Unable to load ECDSA key from PEM file."
		return 1
	fi

	local line_num_prm=""

	for txt_ecdsa_prm in ${txt_ecdsa_prms}; do
		line_num_prm="$(echo "${txt_ecdsa_key}" | grep -i "${txt_ecdsa_prm}:" -n | sed -e 's/:.*//g')"
		if [ 0 = $? ] && [ ! -z "${line_num_prm}" ]; then
			break;
		fi
	done

	if [ -z "${line_num_prm}" ]; then
		errlog "[error] utility.sh: ECDSA parameter cannot be found \"${txt_ecdsa_prms}\"."
		return 1
	fi

	txt_ecdsa_key="$(echo "${txt_ecdsa_key}" | tail -n +"${line_num_prm}")"

	echo "${txt_ecdsa_key}" | while read txt_line || [ -n "${txt_line}" ];
	do
		local txt_key_line="$(echo "${txt_line}" | sed "s/^\s*\(.*\)\s*$/\1/g")"
		echo -n "${txt_key_line}"

		local txt_end_code="$(echo "${txt_key_line}" | sed "s/^.*\(.\)$/\1/g")"
		if [ ":" != "${txt_end_code}" ]; then
			break
		fi
	done | sed -e "s/${txt_ecdsa_prm}:[ \t]*\([^ \t]*\).*/\1/i" | sed -e "s/://g"

	return $?
}

#*******************************************************************************
# Function Name: func_load_ecdsa_pub
# Description  : Load the ecdsa public key parameter as a hexadecimal string
# Arguments    : ${1} - ecdsa key length in bytes
#              : stdin - ecdsa key in PEM format
#              : stdout - hexadecimal string of the ecdsa public key parameter
# Return Value : 0 or 1
#*******************************************************************************
func_load_ecdsa_pub ()
{
	local pem_ecdsa_key="$(cat)"

	local len_tag_key="$(expr ${1} \* 2)"

	if [ $? -ge 2 ];then
		errlog "[error] utility.sh: The expected value of the key length is invalid."
		return 1
	fi

	local hex_pub="$(echo "${pem_ecdsa_key}" | func_extract_ecdsaprm "pub")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The public parameter cannot be found."
		return 1
	fi
	
	hex_pub="$(echo "${hex_pub}" | sed -e "s/^04//g")"
	
	echo -n "${hex_pub}"
	
	return 0
}

#*******************************************************************************
# Function Name: func_load_ecdsa_pri
# Description  : Load the ecdsa private key parameter as a hexadecimal string
# Arguments    : ${1} - ecdsa key length in bytes
#              : stdin - ecdsa private key in PEM format
#              : stdout - hexadecimal string of the ecdsa private key parameter
# Return Value : 0 or 1
#*******************************************************************************
func_load_ecdsa_pri ()
{
	local pem_ecdsa_key="$(cat)"

	local len_tag_key="$(expr ${1} \* 2)"

	if [ $? -ge 2 ];then
		errlog "[error] utility.sh: The expected value of the key length is invalid."
		return 1
	fi

	local hex_priv="$(echo "${pem_ecdsa_key}" | func_extract_ecdsaprm "priv")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The priv parameter cannot be found."
		return 1
	fi

	echo -n "${hex_priv}"

	return 0
}

#*******************************************************************************
# Function Name: func_load_cmnkey
# Description  : Load the common key as a hexadecimal string
# Arguments    : ${1} - common key length in bytes
#              : stdin - common key data
#              : stdout - hexadecimal string of common key
# Return Value : 0 or 1
#*******************************************************************************
func_load_cmnkey ()
{
	local hex_cmn_key="$(func_bin_to_hex)"

	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The common key cannot be loaded."
		return 1
	fi

	local len_cmn_key="$(expr ${1} \* 2)"

	if [ $? -ge 2 ];then
		errlog "[error] utility.sh: The expected value of the key length is invalid."
		return 1
	fi

	if [ ${len_cmn_key} -ne ${#hex_cmn_key} ]; then
		errlog "[error] utility.sh: The key length does not match the expected value."
		return 1
	fi

	echo -n "${hex_cmn_key}"

	return 0
}

#*******************************************************************************
# Function Name: func_bin_to_hex
# Description  : Convert binary to hexadecimal string
# Arguments    : ${1} - path to binary file
#              : stdin - binary data
#              : stdout - hexadecimal string
# Return Value : 0 or 1
#*******************************************************************************
func_bin_to_hex ()
{
	if [ ! -z "${1}" ]; then
		cat "${1}" | xxd -p | tr -d '\n\r'
	elif [ -p /dev/stdin ] || [ -f /dev/stdin ]; then
		cat "/dev/stdin" | xxd -p | tr -d '\n\r'
	else
		echo -n
	fi
	return $?
}

#*******************************************************************************
# Function Name: func_hex_to_bin
# Description  : Convert hexadecimal string to binary
# Arguments    : ${1} or stdin - hexadecimal string
#              : stdout - binary
# Return Value : 0 or 1
#*******************************************************************************
func_hex_to_bin ()
{
	local hex_string=""

	if [ ! -z "${1}" ]; then
		hex_string="${1}"
	elif [ -p /dev/stdin ] || [ -f /dev/stdin ]; then
		hex_string="$(cat "/dev/stdin")"
	else
		hex_string=""
	fi

	local hex_check="$(echo -n "${hex_string}" | grep "[^0-9a-fA-F]")"

	if [ ! -z "${hex_check}" ]; then
		return 1
	fi

	echo -n ${hex_string} | xxd -r -p

	return 0
}

#*******************************************************************************
# Function Name: func_zeropad
# Description  : Outputs text filled with zeros
# Arguments    : ${1} - zero padding length in bytes
#              : stdout - zero padding string
# Return Value : 0
#*******************************************************************************
func_zeropad ()
{
	local pads="$(expr ${1} \* 2)"
	if [ $? -lt 2 ];then
		while [ $pads -gt 0 ]
		do
			echo -n 0
			pads=$(($pads-1))
		done
	fi
	return 0
}
