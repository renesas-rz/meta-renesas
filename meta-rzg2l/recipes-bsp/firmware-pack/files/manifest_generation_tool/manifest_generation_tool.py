# *********************************************************************************************************************
# DISCLAIMER
# This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
# other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
# applicable laws, including copyright laws.
# THIS SOFTWARE IS PROVIDED 'AS IS' AND RENESAS MAKES NO WARRANTIES REGARDING
# THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
# EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
# SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
# SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
# Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
# this software. By using this software, you agree to the additional terms and conditions found by accessing the
# following link:
# www.renesas.com/disclaimer
#
# Copyright (C) 2019-2020 Renesas Electronics Corporation. All rights reserved.
# *********************************************************************************************************************
import os
import re
import binascii
import argparse
import xml.etree.ElementTree as ET
import tool_crypto as tc

# ======================================================================================================================
# Private constant valiables
# ======================================================================================================================
# Error message print
ERRMSG = print

# Size
WORD_BYTES            = 4
BASE_HEX              = 16
IMAGE_UNIT_SIZE       = 16
IV_LEN                = 16
TLV_TYPE_LEN_SIZE     = 4
TLV_TYPE_MASK         = 0xFFFFFF00
TLV_LEN_MASK          = 0x000000FF
TLV_VAL_LEN_MIN       = 0
TLV_VAL_LEN_MAX       = 1020

# Endian string
ENDIAN_BIG            = 'big'
ENDIAN_LITTLE         = 'little'

# Custom tlvs order string
ORDER_TOP             = 'top'
ORDER_BOTTOM          = 'bottom'

# Signing target string
SIGNTARGET_CERTANDIMG  = 'CertificateAndImage'
SIGNTARGET_CERTONLY    = 'CertificateOnly'

# Dictionary keys
KEY_ENCMANNER         = 'encryption_manner'
KEY_SIGNTARGET        = 'signing_target'
KEY_WDATA             = 'word_data'
KEY_CTLV_ORDER        = 'custom_tlvs_order'
KEY_MANIVER           = 'manifest_ver'
KEY_FLAGS             = 'flags'
KEY_LADDR             = 'load_addr'
KEY_DADDR             = 'dest_addr'
KEY_IMGVER            = 'image_version'
KEY_BUILDNUM          = 'build_number'
KEY_HASHS             = 'hash'
KEY_PCS               = 'product_class'
KEY_ICIS              = 'image_cipher_info'
KEY_CUSTOMTLVS        = 'custom_tlv'
KEY_TYPE              = 'type'
KEY_ALGO              = 'algorithm'
KEY_MODE              = 'mode'
KEY_VAL               = 'value'
KEY_TARGET            = 'target'
KEY_UT                = 'use_type'
KEY_HASH_ISPK         = 'ImageSignerPK'
KEY_HASH_IMG          = 'Image'
KEY_HASH_EIMG         = 'EncryptedImage'
KEY_PID               = 'ProductID'
KEY_VID               = 'VendorID'
KEY_ICI_IMG_CIP       = 'ImageCipher'
KEY_ICI_TMP_IMG_DEC   = 'TemporaryImageDecryption'

# Error Message
ERRMSG_OPENFAIL       = 'manifest_generation_tool.py : error: File open failed : %s'
ERRMSG_PARSEFAIL      = 'manifest_generation_tool.py : error: Manifest info parsing failed : %s'
ERRMSG_IMPORTFAIL     = 'manifest_generation_tool.py : error: Key import failed : %s'
ERRMSG_ENCIMGOPTFAIL  = 'manifest_generation_tool.py : error: The encimage option is specified, but the iekey, ealgo '\
                        'option is not specified'
ERRMSG_ENCIMGINFOFAIL = 'manifest_generation_tool.py : error: Inconsistency occurs in the contents of encimage option '\
                        'and Manifest Info : %s'
ERRMSG_SIGNFAIL       = 'manifest_generation_tool.py : error: Signature creation failed'
ERRMSG_ENCFAIL        = 'manifest_generation_tool.py : error: Image encryption failed'
ERRMSG_TLVFAIL        = 'manifest_generation_tool.py : error: TLV creation failed : %s'
ERRMSG_HASHFAIL       = 'manifest_generation_tool.py : error: hash failed : %s'

# Type Class
TLV_TYPE_CLS_POS                            = (28)  # Type Class Bit Position
TLV_TYPE_CLS_KEY                            = (0x0 << (TLV_TYPE_CLS_POS))   # Class Key
TLV_TYPE_CLS_HASH                           = (0x1 << (TLV_TYPE_CLS_POS))   # Class Hash
TLV_TYPE_CLS_SIGN                           = (0x2 << (TLV_TYPE_CLS_POS))   # Class Signature
TLV_TYPE_CLS_CRC                            = (0x4 << (TLV_TYPE_CLS_POS))   # Class CRC
TLV_TYPE_CLS_IV                             = (0x5 << (TLV_TYPE_CLS_POS))   # Class IV
TLV_TYPE_CLS_PC                             = (0xD << (TLV_TYPE_CLS_POS))   # Class Product class
TLV_TYPE_CLS_ICI                            = (0xE << (TLV_TYPE_CLS_POS))   # Class Image Cipher info

# Use type of KEY class
TLV_TYPE_CLS_KEY_UT_POS                     = (24)  # Use Type Bit Position
TLV_TYPE_CLS_KEY_UT_OEM_ROOT_PK             = (0x0 << (TLV_TYPE_CLS_KEY_UT_POS))   # OEM root public key
TLV_TYPE_CLS_KEY_UT_IMG_PK                  = (0x1 << (TLV_TYPE_CLS_KEY_UT_POS))   # Image public key

# Use type of HASH class
TLV_TYPE_CLS_HASH_UT_POS                    = (24)  # Use Type Bit Position
TLV_TYPE_CLS_HASH_UT_IMG_PK                 = (0x0 << (TLV_TYPE_CLS_HASH_UT_POS))  # Image public key Hash
TLV_TYPE_CLS_HASH_UT_IMG                    = (0x1 << (TLV_TYPE_CLS_HASH_UT_POS))  # Image Hash
TLV_TYPE_CLS_HASH_UT_ENCIMG                 = (0x2 << (TLV_TYPE_CLS_HASH_UT_POS))  # Encrypt Image Hash

# Use type of Signature class
TLV_TYPE_CLS_SIGN_UT_POS                    = (24)  # Use Type Bit Position
TLV_TYPE_CLS_SIGN_UT_CERT                   = (0x0 << (TLV_TYPE_CLS_SIGN_UT_POS))  # Certificate Signature
TLV_TYPE_CLS_SIGN_UT_CODE_CERT_AND_IMG      = (0x5 << (TLV_TYPE_CLS_SIGN_UT_POS))  # Code Certificate + Image Signature
TLV_TYPE_CLS_SIGN_UT_CODE_CERT_AND_ENCIMG   = (0x6 << (TLV_TYPE_CLS_SIGN_UT_POS))  # Code Certificate +
                                                                                   # Encrypted Image Signature

# Hash Algorithm of Signature class
TLV_TYPE_CLS_SIGN_HASH_ALGO_POS             = (10)  # Hash Algorithm Bit Position
TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_256        = (0x1 << (TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))  # SHA2-256
TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_384        = (0x2 << (TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))  # SHA2-384
TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_256        = (0x5 << (TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))  # SHA3-256
TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_384        = (0x6 << (TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))  # SHA3-384

# Scheme of Signature class
TLV_TYPE_CLS_SIGN_SCHEME_POS                = (8)   # Scheme Bit Position
TLV_TYPE_CLS_SIGN_SCHEME_RSASSA_PSS         = (0x1 << (TLV_TYPE_CLS_SIGN_SCHEME_POS))  # RSASSA-PSS

# Use type of CRC class
TLV_TYPE_CLS_CRC_UT_POS                     = (24)  # Use Type Bit Position
TLV_TYPE_CLS_CRC_UT_IMG                     = (0x0 << (TLV_TYPE_CLS_CRC_UT_POS))  # Image CRC

# Polynomial of CRC class
TLV_TYPE_CLS_CRC_POLY_POS                   = (20)  # Polynomial Bit Position
TLV_TYPE_CLS_CRC_POLY_CRC32                 = (0x0 << (TLV_TYPE_CLS_CRC_POLY_POS))  # Polynomial CRC32

# Use type of Product Class(PC) class
TLV_TYPE_CLS_PC_UT_POS                      = (24)  # Use Type Bit Position
TLV_TYPE_CLS_PC_UT_VENDER_ID                = (0x0 << (TLV_TYPE_CLS_PC_UT_POS))  # Vender ID
TLV_TYPE_CLS_PC_UT_PRODUCT_ID               = (0x1 << (TLV_TYPE_CLS_PC_UT_POS))  # Product ID

# Use type of IV class
TLV_TYPE_CLS_IV_UT_POS                      = (24)  # Use Type Bit Position
TLV_TYPE_CLS_IV_UT_IMG_CIPHER               = (0x0 << (TLV_TYPE_CLS_IV_UT_POS))  # Image Cipher IV
TLV_TYPE_CLS_IV_UT_TMP_IMG_DEC              = (0x1 << (TLV_TYPE_CLS_IV_UT_POS))  # Temporary Image Decryption IV

# Use type of Image Cipher Info(ICI) class
TLV_TYPE_CLS_ICI_UT_POS                     = (24)  # Use Type Bit Position
TLV_TYPE_CLS_ICI_UT_IMG_ENC_DEC             = (0x0 << (TLV_TYPE_CLS_ICI_UT_POS))
TLV_TYPE_CLS_ICI_UT_TMP_IMG_DEC             = (0x1 << (TLV_TYPE_CLS_ICI_UT_POS))


# Cipher mode of Image Cipher Info(ICI) class
TLV_TYPE_CLS_ICI_MODE_POS                   = (10)  # Cipher mode Bit Position
TLV_TYPE_CLS_ICI_MODE_CBC                   = (0x1 << (TLV_TYPE_CLS_ICI_MODE_POS))  # Mode CBC

# Cryptographic algorithm
TLV_TYPE_CRYPTO_ALGO_POS                    = (14)  # Cryptographic Algorithm Bit Position
TLV_TYPE_CRYPTO_ALGO_AES128                 = (0x0000 << (TLV_TYPE_CRYPTO_ALGO_POS))  # AES-128
TLV_TYPE_CRYPTO_ALGO_RSA2048                = (0x0011 << (TLV_TYPE_CRYPTO_ALGO_POS))  # RSA 2048
TLV_TYPE_CRYPTO_ALGO_ECC_P256               = (0x0022 << (TLV_TYPE_CRYPTO_ALGO_POS))  # ECC NIST P-256
TLV_TYPE_CRYPTO_ALGO_ECC_P384               = (0x0023 << (TLV_TYPE_CRYPTO_ALGO_POS))  # ECC NIST P-384
TLV_TYPE_CRYPTO_ALGO_SHA2_256               = (0x0051 << (TLV_TYPE_CRYPTO_ALGO_POS))  # SHA2-256
TLV_TYPE_CRYPTO_ALGO_SHA2_384               = (0x0052 << (TLV_TYPE_CRYPTO_ALGO_POS))  # SHA2-384
TLV_TYPE_CRYPTO_ALGO_SHA3_256               = (0x0055 << (TLV_TYPE_CRYPTO_ALGO_POS))  # SHA3-256
TLV_TYPE_CRYPTO_ALGO_SHA3_384               = (0x0056 << (TLV_TYPE_CRYPTO_ALGO_POS))  # SHA3-384

# ======================================================================================================================
# Private global valiables
# ======================================================================================================================
# Algorithm type list
algo_types = {
    'AES-128':       TLV_TYPE_CRYPTO_ALGO_AES128,
    'RSA-PSS':       TLV_TYPE_CRYPTO_ALGO_RSA2048,
    'ECDSA-P256':    TLV_TYPE_CRYPTO_ALGO_ECC_P256,
    'ECDSA-P384':    TLV_TYPE_CRYPTO_ALGO_ECC_P384,
    'SHA2-256':      TLV_TYPE_CRYPTO_ALGO_SHA2_256,
    'SHA2-384':      TLV_TYPE_CRYPTO_ALGO_SHA2_384,
    'SHA3-256':      TLV_TYPE_CRYPTO_ALGO_SHA3_256,
    'SHA3-384':      TLV_TYPE_CRYPTO_ALGO_SHA3_384,
}

# Signature lengt list for each signature algorithm
salgo_sign_lens = {
    'RSA-PSS':      256,  # RSA2048 256 [bytes]
    'ECDSA-P256':   64,   # ECDSA P-256 32(r) + 32(s) [bytes]
    'ECDSA-P384':   96,   # ECDSA P-384 48(r) + 48(s) [bytes]
}

# Hash type list for each hash algorithm
halgo_sign_hsah_types = {
    'SHA2-256':     TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_256,
    'SHA2-384':     TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_384,
    'SHA3-256':     TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_256,
    'SHA3-384':     TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_384,
}

# Scheme type list for each hash signature algorithm
salgo_sign_scheme_types = {
    'RSA-PSS':      TLV_TYPE_CLS_SIGN_SCHEME_RSASSA_PSS,
    'ECDSA-P256':   0,  # Don't not use scheme
    'ECDSA-P384':   0,  # Don't not use scheme
}

# Key lengt list for each encryption algorithm
ealgo_key_lens = {
    'AES-CBC':      16,
}


# ======================================================================================================================
# Functions
# ======================================================================================================================
# **********************************************************************************************************************
# Function Name : main
# **********************************************************************************************************************
def main():
    # Command line argument perse
    parser = set_cmdline_argparser()
    args = parser.parse_args()

    # Generate Certificate
    # (args.gentype is always set to 'genkcert' or 'genccert')
    if args.gentype == 'genkcert':
        # Read Manifest information file
        info_xml = read_text_file(args.info)
        if info_xml is None:
            exit(1)

        # Read Image signer key file
        iskey_pem = read_text_file(args.iskey)
        if iskey_pem is None:
            exit(1)

        # Read Manifest signer key file
        mskey_pem = read_text_file(args.mskey)
        if mskey_pem is None:
            exit(1)

        # Delete files at output path
        if os.path.exists(args.certout) is True:
            os.remove(args.certout)

        # Generate Key Certificate
        keycert, mskey_hash = gen_key_cert(args.halgo, args.salgo, info_xml, mskey_pem, iskey_pem)
        if keycert is None:
            exit(1)

        # Write Key certificate to file
        if write_bin_file(keycert, args.certout) == -1:
            exit(1)

        # Write Hash of Manifest Signer PK
        mskey_hash_name = os.path.splitext(os.path.basename(args.mskey))[0] + '_pk.hash'
        mskey_hash_name = os.path.join(os.path.split(args.certout)[0], mskey_hash_name)
        if write_bin_file(mskey_hash, mskey_hash_name) == -1:
            exit(1)

    else:  # args.gentype == 'genccert'
        # Read Manifest information file
        info_xml = read_text_file(args.info)
        if info_xml is None:
            exit(1)

        # Read Image signer key file
        iskey_pem = read_text_file(args.iskey)
        if iskey_pem is None:
            exit(1)

        # Read Image
        img = read_bin_file(args.imgin)
        if img is None:
            exit(1)

        # Delete files at output path
        if os.path.exists(args.certout) is True:
            os.remove(args.certout)

        if os.path.exists(args.imgout) is True:
            os.remove(args.imgout)

        # Read iekey(Execute only if encimage is true)
        if args.encimage is True:
            if args.iekey != '':
                # Read encrypt key file
                iekey_text = read_text_file(args.iekey)
                if iekey_text is None:
                    exit(1)

                # string to bytes
                try:
                    iekey = bytes.fromhex(iekey_text)
                except:
                    ERRMSG(str.format(ERRMSG_IMPORTFAIL % ('ImageEncryptionKey')))
                    exit(1)

                # Swap endian
                if args.iekey_endian == 'Little':
                    tmp = int.from_bytes(iekey, ENDIAN_BIG)
                    iekey = tmp.to_bytes(len(iekey), ENDIAN_LITTLE)
            else:
                iekey = None
            
            if args.ieiv != '':
                # Read initial vector file
                ieiv_text = read_text_file(args.ieiv)
                if ieiv_text is None:
                    exit(1)

                # string to bytes
                try:
                    ieiv = bytes.fromhex(ieiv_text)
                except:
                    ERRMSG(str.format(ERRMSG_IMPORTFAIL % ('ImageEncryptionIV')))
                    exit(1)
                
                # Swap endian
                if args.iekey_endian == 'Little':
                    tmp = int.from_bytes(ieiv, ENDIAN_BIG)
                    ieiv = tmp.to_bytes(len(ieiv), ENDIAN_LITTLE)
            else:
                ieiv = None
        else:
            iekey = None
            ieiv = None

        # Generate Key Certificate
        codecert, outimg = gen_code_cert(args.halgo, args.salgo, info_xml, img, iskey_pem,
                                         args.makecrc, args.encimage, args.ealgo, iekey, ieiv)
        if codecert is None:
            exit(1)

        # Write image
        if write_bin_file(outimg, args.imgout) == -1:
            exit(1)

        # Write Code certificate to file
        if write_bin_file(codecert, args.certout) == -1:
            exit(1)

    # Success
    exit(0)


# **********************************************************************************************************************
# Function Name : set_cmdline_argparser
# **********************************************************************************************************************
def set_cmdline_argparser():
    # Local constant value
    HALGOS        = ['SHA2-256', 'SHA2-384', 'SHA3-256', 'SHA3-384']
    SALGOS        = ['RSA-PSS', 'ECDSA-P256', 'ECDSA-P384']
    EALGOS        = ['AES-CBC']
    IEKEY_ENDIANS = ['Big', 'Little']

    DESC_TOOL       = 'Generate manifest tool for Renesas-SB-Library'
    DESC_GENKCERT   = 'Generate Key Certificate'
    DESC_GENCCERT   = 'Generate Code Certificate'

    METAVER_INFO    = '<ManifestInfoFile>'
    METAVER_CERTOUT = '<CertificateFile>'
    METAVER_ISKEY   = '<ImageSignerKeyFile>'
    METAVER_MSKEY   = '<ManifestSignerKeyFile>'
    METAVER_IEKEY   = '<ImageEncryptionKeyFile>'
    METAVER_IEIV    = '<ImageEncryptionIVFile>'
    METAVER_IMGIN   = '<InputImageFile>'
    METAVER_IMGOUT  = '<OutputImageFile>'

    HELP_GENTYPE    = 'Specify the manifest type to generate'
    HELP_INFO       = 'Specify the path of the Manifest Info file'
    HELP_CERTOUT    = 'Specify the path of the Certificate file to be output'
    HELP_ISKEY      = 'Specify the path of the Image Signer Key file'
    HELP_MSKEY      = 'Specify the path of the Manifest Signer Key file'
    HELP_IEKEY      = 'Specify the path of the Image Encrypted Key file'
    HELP_IEIV       = 'Specify the path of the Image Encrypted IV file'
    HELP_IEKEYEND   = 'Specify the endian of the input Image Encryption Key'
    HELP_HALGO      = 'Specify hash algorithm'
    HELP_SALGO      = 'Specify signature algorithm'
    HELP_EALGO      = 'Specify encryption algorithm'
    HELP_IMGIN      = 'Specify the path of the input Image file or Encrypted Image file'
    HELP_IMGOUT     = 'Specify the path of the output Image file'
    HELP_ENCIMG     = 'Specify when encrypting Image'
    HELP_MAKECRC    = 'Specify to include the CRC value of Image'

    # Set command line parser
    parser = argparse.ArgumentParser(description=DESC_TOOL)
    subparsers = parser.add_subparsers(dest='gentype', required=True, help=HELP_GENTYPE)

    parser_genkcert = subparsers.add_parser('genkcert', description=DESC_GENKCERT)
    parser_genccert = subparsers.add_parser('genccert', description=DESC_GENCCERT)

    # Set arguments for Key Certificate
    parser_genkcert.add_argument('-info',  metavar=METAVER_INFO, required=True, help=HELP_INFO)
    parser_genkcert.add_argument('-certout', metavar=METAVER_CERTOUT, required=True, help=HELP_CERTOUT)
    parser_genkcert.add_argument('-iskey', metavar=METAVER_ISKEY, required=True, help=HELP_ISKEY)
    parser_genkcert.add_argument('-mskey', metavar=METAVER_MSKEY, required=True, help=HELP_MSKEY)
    parser_genkcert.add_argument('-halgo', choices=HALGOS, required=True, help=HELP_HALGO)
    parser_genkcert.add_argument('-salgo', choices=SALGOS, required=True, help=HELP_SALGO)

    # Set arguments for Code Certificate
    parser_genccert.add_argument('-info', metavar=METAVER_INFO, required=True, help=HELP_INFO)
    parser_genccert.add_argument('-certout', metavar=METAVER_CERTOUT, required=True, help=HELP_CERTOUT)
    parser_genccert.add_argument('-imgin', metavar=METAVER_IMGIN, required=True, help=HELP_IMGIN)
    parser_genccert.add_argument('-imgout', metavar=METAVER_IMGOUT, required=True, help=HELP_IMGOUT)
    parser_genccert.add_argument('-iskey', metavar=METAVER_ISKEY, required=True, help=HELP_ISKEY)
    parser_genccert.add_argument('-halgo', choices=HALGOS, required=True, help=HELP_HALGO)
    parser_genccert.add_argument('-salgo', choices=SALGOS, required=True, help=HELP_SALGO)
    parser_genccert.add_argument('-encimage', action='store_true', default=False, help=HELP_ENCIMG)
    parser_genccert.add_argument('-iekey', metavar=METAVER_IEKEY, default="", help=HELP_IEKEY)
    parser_genccert.add_argument('-ieiv', metavar=METAVER_IEIV, default="", help=HELP_IEIV)
    parser_genccert.add_argument('-iekey_endian', choices=IEKEY_ENDIANS, default='Big', help=HELP_IEKEYEND)
    parser_genccert.add_argument('-ealgo', choices=EALGOS, default="", help=HELP_EALGO)
    parser_genccert.add_argument('-makecrc', action='store_true', default=False, help=HELP_MAKECRC)

    return parser


# **********************************************************************************************************************
# Function Name : gen_key_cert
# **********************************************************************************************************************
def gen_key_cert(halgo, salgo, info_xml, mskey_pem, iskey_pem):
    keycert = b''
    tlvs = b''
    mskey_hash = b''
    ctlvs = b''

    # Parse Manifest info
    cert_info, err_element = parse_manifest_info_key_cert(info_xml)
    if cert_info is None:
        ERRMSG(str.format(ERRMSG_PARSEFAIL) % (err_element))
        return None

    # Make Key Certificate header
    header = make_key_cert_header(cert_info[KEY_MANIVER], cert_info[KEY_FLAGS], cert_info[KEY_WDATA])

    # Get image signer public key
    iskey_pub = tc.get_pubkey_bytes(salgo, iskey_pem)
    if iskey_pub is None:
        ERRMSG(str.format(ERRMSG_IMPORTFAIL % ('ImageSignerKey')))
        return None

    # Get manifest signer public key
    mskey_pub = tc.get_pubkey_bytes(salgo, mskey_pem)
    if mskey_pub is None:
        ERRMSG(str.format(ERRMSG_IMPORTFAIL % ('ManifestSignerKey')))
        return None

    # Calculate hash of manifest signer key
    mskey_hash = tc.calc_hash(halgo, [mskey_pub])
    if mskey_hash is None:
        ERRMSG(str.format(ERRMSG_HASHFAIL % ('ManifestSignerPK')))
        return None
    
    # Make Custom TLV
    for ctlv in cert_info[KEY_CUSTOMTLVS]:
        tlv = make_tlv(int(ctlv[KEY_TYPE], BASE_HEX), ctlv[KEY_VAL], cert_info[KEY_WDATA], ENDIAN_BIG)
        if tlv is None:
            ERRMSG(str.format(ERRMSG_TLVFAIL % ('CustomTLV')))
            return None
        ctlvs += tlv
    
    # Add Custom TLVs if it is required on Top
    if cert_info[KEY_CTLV_ORDER] == ORDER_TOP:
        if ctlvs is not None:
            tlvs += ctlvs

    # Make manifest signer key TLV
    tlv_type = TLV_TYPE_CLS_KEY | TLV_TYPE_CLS_KEY_UT_OEM_ROOT_PK | algo_types[salgo]
    tlv = make_tlv(tlv_type, mskey_pub, cert_info[KEY_WDATA], ENDIAN_BIG)
    if tlv is None:
        ERRMSG(str.format(ERRMSG_TLVFAIL % ('ManifestSignerPK')))
        return None
    tlvs += tlv

    # Calculate hash of image signer public key
    iskey_pub_hash = tc.calc_hash(halgo, [iskey_pub])
    if iskey_pub_hash is None:
        ERRMSG(str.format(ERRMSG_HASHFAIL % ('ImageSignerPK')))
        return None

    # Make image signer public key hash TLV
    tlv_type = TLV_TYPE_CLS_HASH | TLV_TYPE_CLS_HASH_UT_IMG_PK | algo_types[halgo]
    tlv = make_tlv(tlv_type, iskey_pub_hash, cert_info[KEY_WDATA], ENDIAN_BIG)
    if tlv is None:
        ERRMSG(str.format(ERRMSG_TLVFAIL % ('ImageSignerPKHash')))
        return None
    tlvs += tlv

    # Add Custom TLVs if it is required on Bottom
    if cert_info[KEY_CTLV_ORDER] != ORDER_TOP:
        if ctlvs is not None:
            tlvs += ctlvs

    # Calculate TLV length
    tlv_len = len(tlvs)
    tlv_len += (TLV_TYPE_LEN_SIZE + salgo_sign_lens[salgo])

    # Joins Header and TLV Length and TLVs (But TLVs except Signature TLV)
    keycert = header
    keycert += tlv_len.to_bytes(WORD_BYTES, cert_info[KEY_WDATA])
    keycert += tlvs

    # Calculate key certificate signature
    cert_sign = tc.calc_sign(salgo, halgo, mskey_pem, [keycert])
    if cert_sign is None:
        ERRMSG(str.format(ERRMSG_SIGNFAIL))
        return None

    # Make key certificate signature TLV
    tlv_type = (TLV_TYPE_CLS_SIGN | TLV_TYPE_CLS_SIGN_UT_CERT | algo_types[salgo] |
                halgo_sign_hsah_types[halgo] | salgo_sign_scheme_types[salgo])

    tlv = make_tlv(tlv_type, cert_sign, cert_info[KEY_WDATA], ENDIAN_BIG)
    if tlv is None:
        ERRMSG(str.format(ERRMSG_TLVFAIL % ('KeyCertSign')))
        return None
    keycert += tlv

    return keycert, mskey_hash


# **********************************************************************************************************************
# Function Name : gen_code_cert
# **********************************************************************************************************************
def gen_code_cert(halgo, salgo, info_xml, img, iskey_pem, makecrc, encimage, ealgo, iekey, ieiv):
    codecert = b''
    tlvs = b''
    eimg = None
    ctlvs = b''

    # Parse Manifest info
    cert_info, err_element = parse_manifest_info_code_cert(info_xml)
    if cert_info is None:
        ERRMSG(str.format(ERRMSG_PARSEFAIL) % (err_element))
        return None, None

    # Zeropadding of image
    if (len(img) % 16) != 0:
        img += bytes.fromhex('00' * (IMAGE_UNIT_SIZE - (len(img) % IMAGE_UNIT_SIZE)))

    # Set signature target image and output image
    target_img = img
    out_img = img

    # Encrypt image (Execute only if encimage is true)
    if encimage is True:
        # Check encimage required option
        if (iekey is None) or (ealgo == ''):
            ERRMSG(str.format(ERRMSG_ENCIMGOPTFAIL))
            return None, None

        # Check key size
        if ealgo_key_lens[ealgo] != len(iekey):
            ERRMSG(str.format(ERRMSG_IMPORTFAIL % ('ImageEncryptionKey')))
            return None, None

        # Check without Encryption manner
        if cert_info[KEY_ENCMANNER] is None:
            ERRMSG(str.format(ERRMSG_ENCIMGINFOFAIL % ('encryption_manner')))
            return None, None

        # Get IV
        if ieiv is None:
            iv = tc.get_rand(IV_LEN)
        else:
            iv = ieiv

        # Encrypt image
        eimg = tc.encrypt(ealgo, iekey, iv, img)
        if eimg is None:
            ERRMSG(str.format(ERRMSG_ENCFAIL))
            return None, None

        # Change signature target image
        if cert_info[KEY_ENCMANNER] == 'EncThenSign':
            target_img = eimg

        # Change output image
        out_img = eimg
    else:
        # Check required Encrypted hash without encimage
        if 'EncryptedImage' in cert_info[KEY_HASHS]:
            ERRMSG(str.format(ERRMSG_ENCIMGINFOFAIL % ('hash(EncryptedImage)')))
            return None, None

    # Make Code Certificate header
    header = make_code_cert_header(cert_info[KEY_MANIVER], cert_info[KEY_FLAGS], cert_info[KEY_LADDR],
                                   cert_info[KEY_DADDR], len(target_img), cert_info[KEY_IMGVER],
                                   cert_info[KEY_BUILDNUM], cert_info[KEY_WDATA])

    # Get image signer public key
    iskey_pub = tc.get_pubkey_bytes(salgo, iskey_pem)
    if iskey_pub is None:
        ERRMSG(str.format(ERRMSG_IMPORTFAIL % ('ImageSignerKey')))
        return None, None

    # Make Custom TLV
    for ctlv in cert_info[KEY_CUSTOMTLVS]:
        tlv = make_tlv(int(ctlv[KEY_TYPE], BASE_HEX), ctlv[KEY_VAL], cert_info[KEY_WDATA], ENDIAN_BIG)
        if tlv is None:
            ERRMSG(str.format(ERRMSG_TLVFAIL % ('CustomTLV')))
            return None, None
        ctlvs += tlv
    
    # Add Custom TLVs if it is required on top
    if cert_info[KEY_CTLV_ORDER] == ORDER_TOP:
        if ctlvs is not None:
            tlvs += ctlvs

    # Make image signer public key TLV
    tlv_type = TLV_TYPE_CLS_KEY | TLV_TYPE_CLS_KEY_UT_IMG_PK | algo_types[salgo]
    tlv = make_tlv(tlv_type, iskey_pub, cert_info[KEY_WDATA], ENDIAN_BIG)
    if tlv is None:
        ERRMSG(str.format(ERRMSG_TLVFAIL % ('ImageSignerPK')))
        return None, None
    tlvs += tlv

    # Make CRC TLV (Execute only if makecrc is true)
    if makecrc is True:
        crc = binascii.crc32(target_img, 0)
        tlv_type = TLV_TYPE_CLS_CRC | TLV_TYPE_CLS_CRC_UT_IMG | TLV_TYPE_CLS_CRC_POLY_CRC32
        # CRC value endian follows word_data endian
        tlv = make_tlv(tlv_type, crc.to_bytes(WORD_BYTES, ENDIAN_BIG), cert_info[KEY_WDATA], cert_info[KEY_WDATA])
        if tlv is None:
            ERRMSG(str.format(ERRMSG_TLVFAIL % ('CRC')))
            return None, None
        tlvs += tlv

    # Make IV TLV (Execute only if encimage is true)
    if encimage is True:
        # IV use type list for each Encryption manner
        encmanner_iv_types = {
            'EncThenSign':   TLV_TYPE_CLS_IV_UT_IMG_CIPHER,
            'SignThenEnc':   TLV_TYPE_CLS_IV_UT_IMG_CIPHER,
            'TemporaryEnc':  TLV_TYPE_CLS_IV_UT_TMP_IMG_DEC,
        }
        tlv_type = TLV_TYPE_CLS_IV | encmanner_iv_types[cert_info[KEY_ENCMANNER]]
        tlv = make_tlv(tlv_type, iv, cert_info[KEY_WDATA], ENDIAN_BIG)
        if tlv is None:
            ERRMSG(str.format(ERRMSG_TLVFAIL % ('IV')))
            return None, None
        tlvs += tlv

    # Make hash TLV
    hash_tlv_params = {
        KEY_HASH_ISPK:  {KEY_TARGET: iskey_pub, KEY_UT: TLV_TYPE_CLS_HASH_UT_IMG_PK},
        KEY_HASH_IMG:   {KEY_TARGET: img,       KEY_UT: TLV_TYPE_CLS_HASH_UT_IMG},
        KEY_HASH_EIMG:  {KEY_TARGET: eimg,      KEY_UT: TLV_TYPE_CLS_HASH_UT_ENCIMG}
    }
    for key in cert_info[KEY_HASHS]:
        param = hash_tlv_params[key]
        digest = tc.calc_hash(halgo, [param[KEY_TARGET]])
        if digest is None:
            ERRMSG(str.format(ERRMSG_HASHFAIL % (key)))
            return None, None
        tlv_type = TLV_TYPE_CLS_HASH | param[KEY_UT] | algo_types[halgo]
        tlv = make_tlv(tlv_type, digest, cert_info[KEY_WDATA], ENDIAN_BIG)
        if tlv is None:
            ERRMSG(str.format(ERRMSG_TLVFAIL % (key + 'Hash')))
            return None, None
        tlvs += tlv

    # Make Image Hash TLV (Execute only if signing target is CertificateOnly)
    if cert_info[KEY_SIGNTARGET] == SIGNTARGET_CERTONLY:
        digest = tc.calc_hash(halgo, [target_img])
        if target_img == img:
            target_str = 'Image'
            use_type = TLV_TYPE_CLS_HASH_UT_IMG
        else:
            target_str = 'EncryptedImage'
            use_type = TLV_TYPE_CLS_HASH_UT_ENCIMG
        tlv_type = TLV_TYPE_CLS_HASH | use_type | algo_types[halgo]
        tlv = make_tlv(tlv_type, digest, cert_info[KEY_WDATA], ENDIAN_BIG)
        if tlv is None:
            ERRMSG(str.format(ERRMSG_TLVFAIL % (target_str + 'Hash')))
            return None, None
        tlvs += tlv

    # Make Product class TLV
    pc_tlv_params = {
        KEY_PID: {KEY_UT: TLV_TYPE_CLS_PC_UT_PRODUCT_ID},
        KEY_VID: {KEY_UT: TLV_TYPE_CLS_PC_UT_VENDER_ID}
    }
    for key, value in cert_info[KEY_PCS].items():
        param = pc_tlv_params[key]
        tlv_type = TLV_TYPE_CLS_PC | param[KEY_UT]
        tlv = make_tlv(tlv_type, value[KEY_VAL], cert_info[KEY_WDATA], ENDIAN_BIG)
        if tlv is None:
            ERRMSG(str.format(ERRMSG_TLVFAIL % (key)))
            return None, None
        tlvs += tlv

    # Make Image Cipher Info(ICI) TLV
    pc_tlv_params = {
        KEY_ICI_IMG_CIP:      {KEY_UT: TLV_TYPE_CLS_ICI_UT_IMG_ENC_DEC},
        KEY_ICI_TMP_IMG_DEC:  {KEY_UT: TLV_TYPE_CLS_ICI_UT_TMP_IMG_DEC}
    }
    # Image Cipher Info mode list for each encryption mode
    ici_mode_types = {
        'CBC':  TLV_TYPE_CLS_ICI_MODE_CBC,  # CBC
    }
    for key, value in cert_info[KEY_ICIS].items():
        param = pc_tlv_params[key]
        tlv_type = (TLV_TYPE_CLS_ICI | param[KEY_UT] | algo_types[value[KEY_ALGO]] | ici_mode_types[value[KEY_MODE]])
        # This is RZ/G2L customization.
        # Value of ImageCipherInfo is described in big endian in ManifestInfo file.
        # However, RZ/G2L needs to refer to Value as little endian, so endian conversion is performed here.
        # tlv = make_tlv(tlv_type,  value[KEY_VAL], cert_info[KEY_WDATA], ENDIAN_BIG)
        tlv = make_tlv(tlv_type,  value[KEY_VAL], cert_info[KEY_WDATA], ENDIAN_LITTLE)
        if tlv is None:
            ERRMSG(str.format(ERRMSG_TLVFAIL % (key + 'Info')))
            return None, None
        tlvs += tlv

    # Add Custom TLVs if it is required on bottom
    if cert_info[KEY_CTLV_ORDER] != ORDER_TOP:
        if ctlvs is not None:
            tlvs += ctlvs

    # Calculate TLV length
    tlv_len = len(tlvs)
    tlv_len += (TLV_TYPE_LEN_SIZE + salgo_sign_lens[salgo])

    # Joins Header and TLV Length and TLVs (But TLVs except Signature TLV)
    codecert = header
    codecert += tlv_len.to_bytes(WORD_BYTES, cert_info[KEY_WDATA])
    codecert += tlvs

    # Set sign parameter
    if cert_info[KEY_SIGNTARGET] == SIGNTARGET_CERTANDIMG:
        msgs = [codecert, target_img]
        if target_img == img:
            use_type = TLV_TYPE_CLS_SIGN_UT_CODE_CERT_AND_IMG
        else:
            use_type = TLV_TYPE_CLS_SIGN_UT_CODE_CERT_AND_ENCIMG
    else:   # SIGNTARGET_CERTONLY
        msgs = [codecert]
        use_type = TLV_TYPE_CLS_SIGN_UT_CERT

    # Calculate key certificate signature
    cert_sign = tc.calc_sign(salgo, halgo, iskey_pem, msgs)
    if cert_sign is None:
        ERRMSG(str.format(ERRMSG_SIGNFAIL))
        return None, None

    # Make key certificate signature TLV
    tlv_type = (TLV_TYPE_CLS_SIGN | use_type | algo_types[salgo] | halgo_sign_hsah_types[halgo] |
                salgo_sign_scheme_types[salgo])
    tlv = make_tlv(tlv_type, cert_sign, cert_info[KEY_WDATA], ENDIAN_BIG)
    if tlv is None:
        ERRMSG(str.format(ERRMSG_TLVFAIL % ('CodeCertSign')))
        return None, None
    codecert += tlv

    return codecert, out_img


# **********************************************************************************************************************
# Function Name : parse_manifest_info_key_cert
# **********************************************************************************************************************
def parse_manifest_info_key_cert(info_xml):

    # Initialize key certificate information
    info = {
        KEY_WDATA:        ENDIAN_LITTLE,
        KEY_CTLV_ORDER:   ORDER_BOTTOM,
        KEY_MANIVER:      None,
        KEY_FLAGS:        None,
        KEY_CUSTOMTLVS:   [],
    }

    # Find key_cert structure
    try:
        root = ET.fromstring(info_xml)
    except:
        return None, 'syntax'

    e_keycert = root.find('key_cert')
    if e_keycert is None:
        return None, 'key_cert'

    # Parse format elements
    e_format = e_keycert.find('format')
    if e_format is not None:
        e_worddata = e_format.find('word_data')
        if e_worddata is not None:
            worddata_endianess = [ENDIAN_BIG, ENDIAN_LITTLE]
            if e_worddata.attrib['endianess'] in worddata_endianess:
                info[KEY_WDATA] = e_worddata.attrib['endianess']
            else:
                return None, 'word_data'
        e_custom_tlvs_order = e_format.find('custom_tlvs_order')
        if e_custom_tlvs_order is not None:
            custom_tlvs_order= [ORDER_TOP, ORDER_BOTTOM]
            if e_custom_tlvs_order.attrib['order'] in custom_tlvs_order:
                info[KEY_CTLV_ORDER] = e_custom_tlvs_order.attrib['order']
            else:
                return None, 'custom_tlvs_order'
    else:
        # format elements is optional
        pass

    # Parse header elements
    e_header = e_keycert.find('header')
    if e_header is None:
        return None, 'header'

    elements = [KEY_MANIVER, KEY_FLAGS]
    for element in elements:
        try:
            contents = e_header.findtext(element)
            if re.match('^0x[0-9,A-F,a-f]{8}$', contents) is None:
                return None, element
            info[element] = int(contents, base=BASE_HEX)
        except:
            # header elements is required
            return None, element

    # Parse additional_tlvs elements
    e_addtlvs = e_keycert.find('additional_tlvs')
    if e_addtlvs is not None:
        for ctlv in e_addtlvs.findall('custom_tlv'):
            if re.match('^0x[0-9,A-F,a-f]{8}$', ctlv.attrib['type']) is None:
                return None, 'custom_tlv'
            info[KEY_CUSTOMTLVS].append({KEY_TYPE: ctlv.attrib['type'], KEY_VAL: ctlv.text})
    else:
        # additional_tlvs elements is optional
        pass

    return info, None


# **********************************************************************************************************************
# Function Name : parse_manifest_info_code_cert
# **********************************************************************************************************************
def parse_manifest_info_code_cert(info_xml):

    # Initialize code certificat information
    info = {
        KEY_ENCMANNER:        None,
        KEY_SIGNTARGET:       SIGNTARGET_CERTANDIMG,
        KEY_WDATA:            ENDIAN_LITTLE,
        KEY_CTLV_ORDER:       ORDER_BOTTOM,
        KEY_MANIVER:          None,
        KEY_FLAGS:            None,
        KEY_LADDR:            None,
        KEY_DADDR:            None,
        KEY_IMGVER:           None,
        KEY_BUILDNUM:         None,
        KEY_HASHS:            {},
        KEY_PCS:              {},
        KEY_ICIS:             {},
        KEY_CUSTOMTLVS:       [],
    }

    # Find code_cert structure
    try:
        root = ET.fromstring(info_xml)
    except:
        return None, 'syntax'

    e_codecert = root.find('code_cert')
    if e_codecert is None:
        return None, 'code_cert'

    # Parse format elements
    e_format = e_codecert.find('format')
    if e_format is not None:
        e_encmanner = e_format.find('encryption_manner')
        if e_encmanner is not None:
            encmanners = ['EncThenSign', 'SignThenEnc', 'TemporaryEnc']
            if e_encmanner.text in encmanners:
                info[KEY_ENCMANNER] = e_encmanner.text
            else:
                return None, 'encryption_manner'

        e_signtarget = e_format.find('signing_target')
        if e_signtarget is not None:
            signtargets = ['CertificateAndImage', 'CertificateOnly']
            if e_signtarget.text in signtargets:
                info[KEY_SIGNTARGET] = e_signtarget.text
            else:
                return None, 'signing_target'

        e_worddata = e_format.find('word_data')
        if e_worddata is not None:
            worddata_endianess = [ENDIAN_BIG, ENDIAN_LITTLE]
            if e_worddata.attrib['endianess'] in worddata_endianess:
                info[KEY_WDATA] = e_worddata.attrib['endianess']
            else:
                return None, 'word_data'
        
        e_custom_tlvs_order = e_format.find('custom_tlvs_order')
        if e_custom_tlvs_order is not None:
            custom_tlvs_order= [ORDER_TOP, ORDER_BOTTOM]
            if e_custom_tlvs_order.attrib['order'] in custom_tlvs_order:
                info[KEY_CTLV_ORDER] = e_custom_tlvs_order.attrib['order']
            else:
                return None, 'custom_tlvs_order'
    else:
        # format elements is optional
        pass

    # Parse header elements
    e_header = e_codecert.find('header')
    if e_header is None:
        return None, 'header'

    elements = [KEY_MANIVER, KEY_FLAGS, KEY_LADDR, KEY_DADDR, KEY_IMGVER, KEY_BUILDNUM]
    for element in elements:
        try:
            contents = e_header.findtext(element)
            if re.match('^0x[0-9,A-F,a-f]{8}$', contents) is None:
                return None, element
            info[element] = int(contents, base=BASE_HEX)
        except:
            # header elements is required
            return None, element

    # Parse additional_tlvs elements
    e_addtlvs = e_codecert.find('additional_tlvs')
    if e_addtlvs is not None:
        # Parse hash elements
        if info[KEY_SIGNTARGET] == SIGNTARGET_CERTONLY:
            # If signing target is 'CertificateOnly', ignore 'Image' and 'EncryptedImage' target
            # These hashes are automatically generated by the tool
            hash_targets = [KEY_HASH_ISPK]
        else:
            hash_targets = [KEY_HASH_ISPK, KEY_HASH_IMG, KEY_HASH_EIMG]
        for e_hash in e_addtlvs.findall('hash'):
            if e_hash.get('target') in hash_targets:
                info[KEY_HASHS].setdefault(e_hash.get('target'), e_hash.attrib)
            else:
                return None, 'hash'

        # Parse hash elements
        pc_usetypes = [KEY_PID, KEY_VID]
        for e_pc in e_addtlvs.findall('product_class'):
            if e_pc.get('use_type') in pc_usetypes:
                pc_info = e_pc.attrib
                pc_info.update({KEY_VAL: e_pc.text})
                info[KEY_PCS].setdefault(e_pc.get('use_type'), pc_info)
            else:
                return None, 'product_class'

        # Parse image_cipher_info(ICI) elements
        ici_usetypes   = [KEY_ICI_IMG_CIP, KEY_ICI_TMP_IMG_DEC]
        ici_algorithms = ['AES-128']
        ici_modes      = ['CBC']
        for e_ici in e_addtlvs.findall('image_cipher_info'):
            if ((e_ici.get('use_type') in ici_usetypes) and
               (e_ici.get('algorithm') in ici_algorithms) and
               (e_ici.get('mode') in ici_modes)):
                ici_info = e_ici.attrib
                ici_info.update({KEY_VAL: e_ici.text})
                info[KEY_ICIS].setdefault(ici_info.get('use_type'), ici_info)
            else:
                return None, 'image_cipher_info'

        for ctlv in e_addtlvs.findall('custom_tlv'):
            if re.match('^0x[0-9,A-F,a-f]{8}$', ctlv.attrib['type']) is None:
                return None, 'custom_tlv'
            info[KEY_CUSTOMTLVS].append({KEY_TYPE: ctlv.attrib['type'], KEY_VAL: ctlv.text})
    else:
        # additional_tlvs elements is optional
        pass

    return info, None


# **********************************************************************************************************************
# Function Name : make_key_cert_header
# **********************************************************************************************************************
def make_key_cert_header(manifest_ver, flags, endian):
    KEYCERT_MAGIC = 0x6b657963  # ASCII code of "keyc"
    reserved = [0, 0, 0, 0, 0]  # 4byte * 5

    header = b''
    header += KEYCERT_MAGIC.to_bytes(WORD_BYTES, endian)
    header += manifest_ver.to_bytes(WORD_BYTES, endian)
    header += flags.to_bytes(WORD_BYTES, endian)
    for resv in reserved:
        header += resv.to_bytes(WORD_BYTES, endian)

    return header


# **********************************************************************************************************************
# Function Name : make_code_cert_header
# **********************************************************************************************************************
def make_code_cert_header(manifest_ver, flags, load_addr, dest_addr, img_size, img_ver, build_ver, endian):
    CODECERT_MAGIC = 0x636f6463  # ASCII code of "codc"

    header = b''
    header += CODECERT_MAGIC.to_bytes(WORD_BYTES, endian)
    header += manifest_ver.to_bytes(WORD_BYTES, endian)
    header += flags.to_bytes(WORD_BYTES, endian)
    header += load_addr.to_bytes(WORD_BYTES, endian)
    header += dest_addr.to_bytes(WORD_BYTES, endian)
    header += img_size.to_bytes(WORD_BYTES, endian)
    header += img_ver.to_bytes(WORD_BYTES, endian)
    header += build_ver.to_bytes(WORD_BYTES, endian)

    return header


# **********************************************************************************************************************
# Function Name : make_tlv
# **********************************************************************************************************************
def make_tlv(tlv_type, tlv_value, tl_endian, v_endian):

    # Check value type
    if type(tlv_value) == str:
        try:
            # Covert string to bytes
            tlv_value = bytes.fromhex(tlv_value)
        except:
            return None

    tlv_val_len = len(tlv_value)

    # Check multiples of length
    if (tlv_val_len % WORD_BYTES) != 0:
        # length supports only word size multiples
        return None

    # Check minimum and maximum length
    if (tlv_val_len < TLV_VAL_LEN_MIN) or (tlv_val_len > TLV_VAL_LEN_MAX):
        return None

    # Make TLV
    type_len = (tlv_type & TLV_TYPE_MASK) | ((tlv_val_len//WORD_BYTES) & TLV_LEN_MASK)
    tlv = type_len.to_bytes(WORD_BYTES, tl_endian)
    for i in range(0, len(tlv_value), WORD_BYTES):
        wordval = int.from_bytes(tlv_value[i:i+WORD_BYTES], ENDIAN_BIG)
        tlv += wordval.to_bytes(WORD_BYTES, v_endian)

    return tlv


# **********************************************************************************************************************
# Function Name : read_text_file
# **********************************************************************************************************************
def read_text_file(file_path):
    try:
        with open(file_path, 'r') as infile:
            text = infile.read()
    except:
        ERRMSG(str.format(ERRMSG_OPENFAIL % (file_path)))
        text = None
    return text


# **********************************************************************************************************************
# Function Name : read_bin_file
# **********************************************************************************************************************
def read_bin_file(file_path):
    try:
        with open(file_path, 'rb') as infile:
            bin = infile.read()
    except:
        ERRMSG(str.format(ERRMSG_OPENFAIL % (file_path)))
        bin = None
    return bin


# **********************************************************************************************************************
# Function Name : write_bin_file
# **********************************************************************************************************************
def write_bin_file(data, file_path):
    ret = 0
    try:
        with open(file_path, 'bw') as outfile:
            outfile.write(data)
    except:
        ERRMSG(str.format(ERRMSG_OPENFAIL % (file_path)))
        ret = -1
    return ret


# ======================================================================================================================
# Script start
# ======================================================================================================================
if __name__ == '__main__':
    main()
