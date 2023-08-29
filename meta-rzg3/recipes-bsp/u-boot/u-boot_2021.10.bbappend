FILESEXTRAPATHS_append := "${THISDIR}/files"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rzg3s-dev"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "58b9bdaaa4c514383492c783022eaa1081aa2068"
