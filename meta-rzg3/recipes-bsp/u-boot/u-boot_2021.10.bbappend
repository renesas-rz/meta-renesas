FILESEXTRAPATHS_append := "${THISDIR}/files"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rzg3s-dev"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "3cc7decb2851a1f3e0e4d4581e3113bfdd791acc"
