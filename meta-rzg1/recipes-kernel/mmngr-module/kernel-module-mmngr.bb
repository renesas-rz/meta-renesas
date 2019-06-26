require ../../include/rzg-modules-common.inc
require ../../include/multimedia-control.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://drv/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://drv/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
    file://include/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://include/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"
DEPENDS = "linux-renesas"
PN = "kernel-module-mmngr"
SRC_URI = "file://mmngr.tar.bz2 \
    file://0002-Add-physical-address-translating-feature.patch \
    file://0001-mmngr-Fix-invalid-type-for-argument-variable-of-func.patch \
"
S = "${WORKDIR}/mmngr"

MMNGR_CFG_skrzg1m = "MMNGR_KOELSCH"
MMNGR_CFG_skrzg1e = "MMNGR_ALT"
MMNGR_CFG_iwg20m-g1m = "MMNGR_IWG20M"
MMNGR_CFG_iwg20m-g1n = "MMNGR_IWG20M"
MMNGR_CFG_iwg21m = "MMNGR_LAGER"
MMNGR_CFG_iwg22m = "MMNGR_IWG20M"
MMNGR_CFG_iwg23s = "MMNGR_IWG20M"

do_compile() {
    export MMNGR_CONFIG=${MMNGR_CFG}
    # In case use "DTV", set MMNGR_SSP_CONFIG="MMNGR_SSP_ENABLE"
    export MMNGR_SSP_CONFIG="MMNGR_SSP_DISABLE"
    cd ${S}/drv
    make all ARCH=arm
}

do_install () {
    # Create destination folders
    mkdir -p ${D}/lib/modules/${KERNEL_VERSION}/extra/ ${D}/usr/src/kernel/include

    # Copy shared library for reference from other modules
    cp -f ${S}/drv/Module.symvers ${D}/usr/src/kernel/include/mmngr.symvers

    # Copy kernel module
    cp -f ${S}/drv/mmngr.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/
}

# Append function to clean extract source
do_cleansstate_prepend() {
        bb.build.exec_func('do_clean_source', d)
}

do_clean_source() {
    rm -f ${KERNELSRC}/include/mmngr_private.h
    rm -f ${KERNELSRC}/include/mmngr_public.h
    rm -f ${KERNELSRC}/include/mmngr.symvers
}

PACKAGES = "\
    ${PN}-dev \
"

FILES_${PN}-dev = " \
    /usr/src/kernel/include/mmngr.symvers \
    /usr/src/kernel/include/*.h \
"

RPROVIDES_${PN} += "kernel-module-mmngr"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

do_configure[noexec] = "1"

python do_package_ipk_prepend () {
    d.setVar('ALLOW_EMPTY', '1')
}

KERNEL_MODULE_AUTOLOAD = "mmngr"
