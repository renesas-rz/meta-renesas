require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2023.10/rz-asr"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "c2acd42c91633cc6812f83d029485561f0d2a6dc"
PV = "v2023.10+git${SRCPV}"
