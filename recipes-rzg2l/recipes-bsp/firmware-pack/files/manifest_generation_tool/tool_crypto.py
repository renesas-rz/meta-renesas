# *********************************************************************************************************************
# DISCLAIMER
# This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
# other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
# applicable laws, including copyright laws.
# THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
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
from Crypto import Random
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto.Hash import SHA384
from Crypto.Hash import SHA3_256
from Crypto.Hash import SHA3_384
from Crypto.Signature import pss
from Crypto.Signature import DSS
from Crypto.PublicKey import ECC
from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes

# ======================================================================================================================
# Private global valiables
# ======================================================================================================================
# ECC signature algorighm list
ecc_salgos  = ['ECDSA-P256', 'ECDSA-P384']

# RSA signature algorighm list
rsa_salgos  = ['RSA-PSS']

# Hash object list
halgo_objs  = {'SHA2-256': SHA256, 'SHA2-384': SHA384, 'SHA3-256': SHA3_256, 'SHA3-384': SHA3_384}

# Encryption mode list
ealgo_modes = {'AES-CBC': AES.MODE_CBC}


# ======================================================================================================================
# Functions
# ======================================================================================================================
# **********************************************************************************************************************
# Function Name : get_pubkey_bytes
# **********************************************************************************************************************
def get_pubkey_bytes(salgo, key_pem):
    try:
        if salgo in ecc_salgos:
            key = ECC.import_key(key_pem)
            pubkey = key.pointQ.x.to_bytes(key.pointQ.size_in_bytes())
            pubkey += key.pointQ.y.to_bytes(key.pointQ.size_in_bytes())
        elif salgo in rsa_salgos:
            key = RSA.import_key(key_pem)
            pubkey = key.n.to_bytes(key.size_in_bytes(), 'big')
            pubkey += key.e.to_bytes(4, 'big')
        else:
            pubkey = None
    except:
            pubkey = None
    return pubkey


# **********************************************************************************************************************
# Function Name : get_rand
# **********************************************************************************************************************
def get_rand(len):
    return get_random_bytes(len)


# **********************************************************************************************************************
# Function Name : calc_hash
# **********************************************************************************************************************
def calc_hash(halgo, msgs):
    try:
        hobj = halgo_objs[halgo].new()
        for msg in msgs:
            hobj.update(msg)
        digest = hobj.digest()
    except:
        digest = None
    return digest


# **********************************************************************************************************************
# Function Name : calc_sign
# **********************************************************************************************************************
def calc_sign(salgo, halgo, key_pem, msgs):
    try:
        if salgo in ecc_salgos:
            key = ECC.import_key(key_pem)
            hobj = halgo_objs[halgo].new()
            for msg in msgs:
                hobj.update(msg)
            sobj = DSS.new(key, 'fips-186-3')
            sign = sobj.sign(hobj)
        elif salgo in rsa_salgos:
            key = RSA.import_key(key_pem)
            hobj = halgo_objs[halgo].new()
            for msg in msgs:
                hobj.update(msg)
            sobj = pss.new(key, salt_bytes=(hobj.digest_size * 2))
            sign = sobj.sign(hobj)
        else:
            sign = None
    except:
        sign = None

    return sign


# **********************************************************************************************************************
# Function Name : encrypt
# **********************************************************************************************************************
def encrypt(ealgo, key, iv, plain):
    try:
        aes = AES.new(key, ealgo_modes[ealgo], iv)
        cipher = aes.encrypt(plain)
    except:
        cipher = None
    return cipher
