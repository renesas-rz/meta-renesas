require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2023.10/rzfive"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "f511c0824b9ef38cd716c962c59ff4346151fbbf"
PV = "v2023.10+git${SRCPV}"
