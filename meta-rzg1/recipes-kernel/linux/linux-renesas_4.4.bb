DESCRIPTION = "Linux kernel for the R-Car Generation 3 based board"

require recipes-kernel/linux/linux-yocto.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"
COMPATIBLE_MACHINE = "iwg20m|iwg21m"

DEPENDS_append = " util-linux-native openssl-native"

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "046b9337e935a5d07efab1f97ce3728f54a2ebd6"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.55-cip3 \
"

LINUX_VERSION ?= "v4.4.55-cip3"
PV = "${LINUX_VERSION}+git${SRCPV}"
PR = "r1"

S = "${WORKDIR}/git"

SRC_URI_append = " \
    file://defconfig \
    file://iwg20m_defconfig \
    file://iwg21m_defconfig \
"

do_configure_prepend_iwg20m() {
    cp -f ${WORKDIR}/iwg20m_defconfig ${WORKDIR}/defconfig
}

do_configure_prepend_iwg21m() {
    cp -f ${WORKDIR}/iwg21m_defconfig ${WORKDIR}/defconfig
}

SRC_URI_append_iwg20m = " \
    file://iwg20m/0001-v4l2-core-remove-unhelpful-kernel-warning.patch \
"

KERNEL_VERSION_SANITY_SKIP="1"
