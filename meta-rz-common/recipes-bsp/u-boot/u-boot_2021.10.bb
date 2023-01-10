require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rz"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "83b2ea37f4b2dd52accce8491af86cbb280f6774"
PV = "v2021.10+git${SRCPV}"
