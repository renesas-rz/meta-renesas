DESCRIPTION = "Linux kernel for the R-Car Generation 3 based board"

require recipes-kernel/linux/linux-yocto.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"
COMPATIBLE_MACHINE = "iwg20m|iwg21m|iwg22m|iwg23s"

DEPENDS_append = " util-linux-native openssl-native"

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "2d012656650dbadf65cee359510d3aaaeeeaf1b5"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.138-cip25 \
	file://0001-v4l2-core-remove-unhelpful-kernel-warning.patch \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

LINUX_VERSION ?= "4.4.138-cip25"
PV = "${LINUX_VERSION}+git${SRCPV}"
PR = "r1"

S = "${WORKDIR}/git"

SRC_URI_append = " \
    file://defconfig \
    file://common.cfg \
"

SRC_URI_append_iwg20m = " \
    file://iwg20m.cfg \
"

SRC_URI_append_iwg21m = " \
    file://iwg21m.cfg \
"

SRC_URI_append_iwg22m = " \
    file://iwg22m.cfg \
"

SRC_URI_append_iwg23s = " \
    file://iwg23s.cfg \
"

