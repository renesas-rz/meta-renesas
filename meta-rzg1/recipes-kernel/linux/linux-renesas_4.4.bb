DESCRIPTION = "Linux kernel for the RZ/G based board"

require recipes-kernel/linux/linux-yocto.inc
include linux.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"
COMPATIBLE_MACHINE = "iwg20m-g1m|iwg20m-g1n|iwg21m|iwg22m|iwg23s"

DEPENDS_append = " util-linux-native openssl-native"

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "fac3c06918060fc00ebe552c3349d51817ce89c8"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.138-cip25-rt \
	file://0001-v4l2-core-remove-unhelpful-kernel-warning.patch \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
	file://0002-rt-add-kernel-module-backfire-for-rt-tests.patch \
"

LINUX_VERSION ?= "4.4.138-cip25-rt"
PV = "${LINUX_VERSION}+git${SRCPV}"
PR = "r1"

S = "${WORKDIR}/git"

SRC_URI_append = " \
    file://defconfig \
    file://common.cfg \
"

SRC_URI_append_iwg20m-g1m = " \
    file://iwg20m.cfg \
"

SRC_URI_append_iwg20m-g1n = " \
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

do_configure_append() {
	# If kernel_configure_variable or similar functions is used, add here.
	# Note that the settings here has higher priority than cfg files above.

}
