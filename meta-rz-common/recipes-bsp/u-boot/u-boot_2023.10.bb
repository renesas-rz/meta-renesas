require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2023.10/rz-asr"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "269f162cf520c80804db419434de2e0d169df9a3"
PV = "v2023.10+git${SRCPV}"
