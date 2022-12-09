require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rz"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "a6528333e4a22094c11a4b3f218ffeb0f4a6eff0"
PV = "v2021.10+git${SRCPV}"
