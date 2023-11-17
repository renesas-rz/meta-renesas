require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2023.10/rz-asr"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "f4370ff1f6c46bca481bd646813bab7ae23e7d48"
PV = "v2023.10+git${SRCPV}"
