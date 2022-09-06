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

	local hex_privateExponent="$(echo "${pem_rsa_key}" | func_extract_rsaprm "privateExponent")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The privateExponent parameter cannot be found."
		return 1
	fi

	echo -n "${hex_modulus}${hex_privateExponent}"

	return 0
}

#*******************************************************************************
# Function Name: func_extract_eccprm
# Description  : Extract parameters from PEM format ECC key.
# Arguments    : ${1} - ecc parameters
#              : stdin - ecc key in PEM format
#              : stdout - hexadecimal string of the ecc key parameter
# Return Value : 0 or 1
#*******************************************************************************
func_extract_eccprm ()
{
	local txt_ecc_prms="${1}"

	local pem_ecc_key="$(cat)"

	local txt_ecc_key=""

	echo "${pem_ecc_key}" | grep -i "PRIVATE KEY" >/dev/null
	if [ 0 = $? ]; then
		txt_ecc_key="$(echo "${pem_ecc_key}" | openssl ec -text -noout 2>/dev/null)"
	else
		txt_ecc_key="$(echo "${pem_ecc_key}" | openssl ec -text -noout -pubin -conv_form uncompressed 2>/dev/null)"
	fi

	if [ $? != 0 ] || [ -z "${txt_ecc_key}" ]; then
		errlog "[error] utility.sh: Unable to load ECC key from PEM file."
		return 1
	fi

	local line_num_prm=""

	for txt_ecc_prm in ${txt_ecc_prms}; do
		line_num_prm="$(echo "${txt_ecc_key}" | grep -i "${txt_ecc_prm}:" -n | sed -e 's/:.*//g')"
		if [ 0 = $? ] && [ ! -z "${line_num_prm}" ]; then
			break;
		fi
	done

	if [ -z "${line_num_prm}" ]; then
		errlog "[error] utility.sh: ECC parameter cannot be found \"${txt_ecc_prms}\"."
		return 1
	fi

	txt_ecc_key="$(echo "${txt_ecc_key}" | tail -n +"${line_num_prm}")"

	echo "${txt_ecc_key}" | while read txt_line || [ -n "${txt_line}" ];
	do
		local txt_key_line="$(echo "${txt_line}" | sed "s/^\s*\(.*\)\s*$/\1/g")"
		echo -n "${txt_key_line}"

		local txt_end_code="$(echo "${txt_key_line}" | sed "s/^.*\(.\)$/\1/g")"
		if [ ":" != "${txt_end_code}" ]; then
			break
		fi
	done | sed -e "s/${txt_ecc_prm}:[ \t]*\([^ \t]*\).*/\1/i" | sed -e "s/://g"

	return $?
}

#*******************************************************************************
# Function Name: func_load_ecc_pub
# Description  : Load the ecc public key parameter as a hexadecimal string
# Arguments    : ${1} - ecc key length in bytes
#              : stdin - ecc key in PEM format
#              : stdout - hexadecimal string of the ecc public key parameter
# Return Value : 0 or 1
#*******************************************************************************
func_load_ecc_pub ()
{
	local pem_ecc_key="$(cat)"

	local len_tag_key="$(expr ${1} \* 2)"

	if [ $? -ge 2 ];then
		errlog "[error] utility.sh: The expected value of the key length is invalid."
		return 1
	fi

	local hex_pub="$(echo "${pem_ecc_key}" | func_extract_eccprm "pub")"
	if [ 0 != $? ]; then
		errlog "[error] utility.sh: The public parameter cannot be found."
		return 1
	fi
	
	hex_pub="$(echo "${hex_pub}" | sed -e "s/^04//g")"
	
	echo -n "${hex_pub}"
	
	return 0
}

#*******************************************************************************
# Function Name: func_load_ecc_pri
# Description  : Load the ecc private key parameter as a hexadecimal string
# Arguments    : ${1} - ecc key length in bytes
#              : stdin - ecc private key in PEM format
#              : stdout - hexadecimal string of the ecc private key parameter
# Return Value : 0 or 1
#*******************************************************************************
func_load_ecc_pri ()
{
	local pem_ecc_key="$(cat)"

	local len_tag_key="$(expr ${1} \* 2)"

	if [ $? -ge 2 ];then
		errlog "[error] utility.sh: The expected value of the key length is invalid."
		return 1
	fi

	local hex_priv="$(echo "${pem_ecc_key}" | func_extract_eccprm "priv")"
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
