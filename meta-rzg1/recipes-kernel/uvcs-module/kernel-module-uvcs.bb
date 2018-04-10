require ../../include/rzg-modules-common.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://include/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://include/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"
DEPENDS = "linux-renesas"
PN = "kernel-module-uvcs"
PR = "r0"
SRC_URI = "file://uvcs-kernel.tar.bz2 \
	file://0001-uvcs-support-board-G1H-r8a7742.patch \
"
S = "${WORKDIR}/uvcs"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
inherit autotools

export UVCS_DRV_SRC_DIR = "${S}/source/uvcs_lkm"
export UVCS_CMN_SRC_DIR = "${S}/source/uvcs_cmn"
export UVCS_CMN_INC_DIR = "${S}/include"
export DRV_CORE_SRC_DIR = "${S}/source/driver_core"

do_compile() {
    cd ${S}/source/makefile/linaro_5_2_1/
    make clean ARCH=arm
    make all ARCH=arm
}

do_install() {
    # Create destination folder
    mkdir -p ${D}/lib/modules/${KERNEL_VERSION}/extra/ ${D}/usr/src/kernel/include

    # Copy kernel module
    cp -f ${S}/source/makefile/linaro_5_2_1/uvcs_cmn.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/uvcs_cmn.ko

    # Copy shared header files
    cp -f ${S}/include/uvcs_cmn.h  ${D}/usr/src/kernel/include
    cp -f ${S}/include/uvcs_types.h  ${D}/usr/src/kernel/include
    cp -f ${S}/source/makefile/linaro_5_2_1/Module.symvers  ${D}/usr/src/kernel/include/uvcs.symvers
}

# Append function to clean extract source
do_cleansstate_prepend() {
        bb.build.exec_func('do_clean_source', d)
}

do_clean_source() {
    rm -f ${KERNELSRC}/include/uvcs_cmn.h ${KERNELSRC}/include/uvcs_types.h
    rm -f ${KERNELSRC}/include/uvcs.symvers
}

PACKAGES = "\
    ${PN} \
    ${PN}-cmn \
    ${PN}-dev \
"

FILES_${PN}-cmn = " \
    /lib/modules/${KERNEL_VERSION}/extra/uvcs_cmn.ko \
"

FILES_${PN}-dev = " \
    /usr/src/kernel/include \
    /usr/src/kernel/include/*.h \
    /usr/src/kernel/include/uvcs.symvers \
"

RPROVIDES_${PN} += "kernel-module-uvcs"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

python do_package_ipk_prepend () {
    d.setVar('ALLOW_EMPTY', '1')
}
KERNEL_MODULE_AUTOLOAD = "uvcs_cmn"
