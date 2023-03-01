FILESEXTRAPATHS_append := "${THISDIR}/files"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rzg3s"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "9c69847bbf1cde84d0941801bb216dc92085162f"
