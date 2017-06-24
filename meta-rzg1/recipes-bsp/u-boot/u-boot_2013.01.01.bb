require u-boot.inc

# This is needs to be validated among supported BSP's before we can
# make it default
DEFAULT_PREFERENCE = "-1"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb"

PV = "v2013.01.01+git${SRCPV}"

SRCREV = "cb82c56b5342908120e0cad4679dca7d6058d728"
SRC_URI = "git://git.denx.de/u-boot-sh.git;branch=renesas/bsp/rcar-gen2-1.9.4;protocol=git"

S = "${WORKDIR}/git"

COMPATIBLE_MACHINE = "(skrzg1m|skrzg1e|iwg20m|iwg21m|iwg22m|iwg23s)"

SRC_URI_append_lcb = " \
	file://0001-add-r8a7743-and-r8a7745-support.patch \
	file://0002-add-skrzg1e-and-skrzg1m-support.patch \
	file://0004-ARM-cpu-Add-ARMv7-barrier-operations-support.patch \
	file://0007-gpio-sh-pfc-fix-gpio-input-read.patch \
	file://0008-serial-sh-interface-for-rzg1.patch \
	file://0009-INTC-workaround.patch \
"

SRC_URI_append_iwg20m = " \
	file://PATCH002-iW-PREWZ-SC-01-R3.0-REL2.0-Linux3.10.31-UBoot_basic_customization.patch \
"

SRC_URI_append_iwg21m = " \
	file://0010-add-r8a7742-support.patch \
	file://0011-add-skrzg1h-support.patch \
	file://PATCH001-iW-PREXZ-SC-01-R2.0-REL1.0-Linux3.10.31-UBoot_basic_customization.patch \
"

SRC_URI_append_iwg22m = " \
	file://PATCH001-iW-PREZZ-SC-01-R2.0-REL1.0-Linux3.10.31-UBoot_basic_customization.patch \
"

SRC_URI_append_iwg23s = " \
	file://0012-ARM-shmobile-Add-r8a7747x-support.patch \
	file://0013-Board-iwg23s_Pi-Add-iwg23s_Pi-support.patch \
"
