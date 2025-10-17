DESCRIPTION = "Linux kernel for the RZ/G based board"

require recipes-kernel/linux/linux-yocto.inc
include linux.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"
COMPATIBLE_MACHINE = "iwg20m-g1m|iwg20m-g1n|iwg21m|iwg22m|iwg23s"

DEPENDS_append = " util-linux-native openssl-native"
KERNEL_URL=" \
	git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "${@bb.utils.contains("IS_RT_BSP", "1", "rzg1-cip102-rt57", "rzg1-cip102",d)}"
SRCREV = "${@bb.utils.contains("IS_RT_BSP", "1", "2072aaab7861228946346229b41aeec34fc3f4f1", "a6e2e06c37645977643b18874a64db3046123d67",d)}"
SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

LINUX_VERSION ?= "${@bb.utils.contains("IS_RT_BSP", "1", "4.4.302-cip102-rt57", "4.4.302-cip102",d)}"

PV = "${LINUX_VERSION}+git${SRCPV}"
PR = "r1"

S = "${WORKDIR}/git"

SRC_URI_append = " \
	file://defconfig \
"

SRC_URI_append = " \
    ${@bb.utils.contains("IS_RT_BSP", "1", " file://rt_config.cfg", " ", d)} \
"

SRC_URI_append = " \
    ${@bb.utils.contains("IS_RT_BSP", "1", " file://patches/0001-v4l2-core-remove-unhelpful-kernel-warning.patch", " ", d)} \
    ${@bb.utils.contains("IS_RT_BSP", "1", " file://patches/0002-rt-add-kernel-module-backfire-for-rt-tests.patch", " ", d)} \
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
