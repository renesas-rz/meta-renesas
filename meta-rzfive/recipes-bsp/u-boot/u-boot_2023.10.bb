require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2023.10/rzfive"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "6d62d510575b8b3319a75e4d9506d702aee11138"
PV = "v2023.10+git${SRCPV}"
