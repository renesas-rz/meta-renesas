require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2023.10/rz-asr"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "cadb970a027f5b4a21ac1a72f491d0090852eed4"
PV = "v2023.10+git${SRCPV}"
