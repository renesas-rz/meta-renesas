DESCRIPTION = "Linux kernel for the R-Car Generation 3 based board"

require recipes-kernel/linux/linux-yocto.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"
COMPATIBLE_MACHINE = "iwg20m|iwg21m"

DEPENDS_append = " util-linux-native openssl-native"

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "79f8a920af486ed07283dbe7159e68ee3c19d19c"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.55-cip3 \
"

LINUX_VERSION ?= "4.4.55-cip3"
PV = "${LINUX_VERSION}+git${SRCPV}"
PR = "r1"

SRC_URI_append = " \
    file://defconfig \
"
