DESCRIPTION = "Linux kernel for the RZ/G based board"

require recipes-kernel/linux/linux-yocto.inc
include linux.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"
COMPATIBLE_MACHINE = "iwg20m-g1m|iwg20m-g1n|iwg21m|iwg22m|iwg23s"

DEPENDS_append = " util-linux-native openssl-native"
KERNEL_URL=" \
	git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "rzg1-cip70"
SRCREV = "cf20f2b80364a8d8dfec466befd8a10fa1e1b716"
SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

LINUX_VERSION ?= "4.4.302-cip70"
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
