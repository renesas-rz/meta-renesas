require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2023.10/rz-asr"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "af7bb315304617ab219471a13ddbd2c767d74d6b"
PV = "v2023.10+git${SRCPV}"
