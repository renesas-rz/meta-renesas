FILESEXTRAPATHS_append := "${THISDIR}/files"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rzg3s-dev"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "0d4b28210402be3371a68d55783a7ddc48fdd319"
