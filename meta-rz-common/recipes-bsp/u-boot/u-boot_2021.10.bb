require u-boot-common_${PV}.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rz"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "711334a179f32dee4ea4c71cfb3cc1408ac65535"
PV = "v2021.10+git${SRCPV}"

SRC_URI_append = " \
	file://asr/0001-smarc-rzg2l-efi_loader-Fix-loaded-image-alignment.patch       \
	file://asr/0002-smarc-rzg2l-enable-configuration-for-ARM-system-read.patch    \
	file://asr/0003-smarc-rzg2l-arm-system-ready-increase-size-of-uboot.patch     \
	file://asr/0004-smarc-rzg2l-enable-distro-bootcmd.patch                       \
	file://asr/0005-smarc-rzg2l-randomize-ethernet-address-to-avoid-null.patch    \
	file://asr/0006-smarc-rzg2l-enable-rtc-command-and-store-rtc-time.patch       \
	file://asr/0007-smarc-rzg2l-capsule-updates.patch                             \
"