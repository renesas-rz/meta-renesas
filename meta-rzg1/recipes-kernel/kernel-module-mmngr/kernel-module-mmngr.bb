inherit module
require include/rz-modules-common.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://drv/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://drv/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
    file://include/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://include/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"

DEPENDS = "linux-renesas"
PN = "kernel-module-mmngr"
PR = "r0"

SRC_URI = "file://mmngr.tar.bz2"
S = "${WORKDIR}/mmngr"
includedir = "${RENESAS_DATADIR}/include"

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
    install -d ${INCSHARED}
    make all ARCH=arm
}

do_install () {
    # Create destination directories
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/drv/Module.symvers ${KERNELSRC}/include/mmngr.symvers

    # Install kernel module
    install -m 644 ${S}/drv/mmngr.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/

    # Install shared header files to KERNELSRC(STAGING_KERNEL_DIR)
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/include/mmngr_public.h ${KERNELSRC}/include/
    install -m 644 ${S}/include/mmngr_private.h ${KERNELSRC}/include/

    # Install shared header file to ${includedir}
    install -m 644 ${S}/include/mmngr_public.h ${D}/${includedir}/
    install -m 644 ${S}/include/mmngr_private.h ${D}/${includedir}/
    install -m 644 ${S}/drv/Module.symvers ${D}/${includedir}/mmngr.symvers
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
PACKAGES_${PN} += " \
    FILES_${PN}-staticdev \
"

FILES_${PN}-dev := " \
    ${includedir}/mmngr.symvers \
    ${includedir}/*.h \
"

RPROVIDES_${PN} += "kernel-module-mmngr"

python do_package_ipk_prepend () {
    d.setVar('ALLOW_EMPTY', '1')
}

KERNEL_MODULE_AUTOLOAD = "mmngr"
