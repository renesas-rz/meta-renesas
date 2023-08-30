inherit module
require include/rz-modules-common.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://drv/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://drv/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"

DEPENDS = "linux-renesas kernel-module-mmngr"
PN = "kernel-module-fdpm"
PR = "r0"
SRC_URI = "file://fdpm-kernel.tar.bz2"
S = "${WORKDIR}/fdpm"
includedir = "${RENESAS_DATADIR}/include"

FDPM_CFG_r8a7742 = "H2CONFIG"
FDPM_CFG_r8a7743 = "M2CONFIG"
FDPM_CFG_r8a7744 = "M2CONFIG"
FDPM_CFG_r8a7745 = "E2CONFIG"
FDPM_CFG_r8a77470 = "C2CONFIG"

KERNEL_HEADER_PATH = "${KERNELSRC}/include/linux"
FDPM_INSTALL_HEADERS="fdpm_drv.h fdpm_public.h fdpm_api.h"

do_compile() {
    # Build kernel module
    export FDPM_CONFIG=${FDPM_CFG}
    export FDPM_MMNGRDIR=${KERNELSRC}/include
    export FDPM_MMNGRSYMVERS=mmngr.symvers
    cd ${S}/drv
    make all ARCH=arm
}

do_install() {
    # Create destination directories
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Copy driver and header files
    install -m 644 ${S}/drv/fdpm.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/

    for f in ${FDPM_INSTALL_HEADERS} ; do
        install -m 644 ${KERNEL_HEADER_PATH}/${f} ${D}/${includedir}/
    done

    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/drv/Module.symvers ${KERNELSRC}/include/fdpm.symvers
    install -m 644 ${S}/drv/Module.symvers ${D}/${includedir}/fdpm.symvers
}

# Append function to clean extract source
do_cleansstate_prepend() {
        bb.build.exec_func('do_clean_source', d)
}

do_clean_source() {
    # Check if kernel source exists before doing cleansstate
    if [ -d ${KERNELSRC} ] ; then
        for f in fdpm.symvers ${FDPM_INSTALL_HEADERS} ; do
            find ${KERNELSRC} -name ${f} -delete
        done
    fi
}

PACKAGES = "\
    ${PN}-dev \
"

FILES_${PN}-dev = " \
    ${includedir}/*.h \
    ${includedir}/fdpm.symvers \
"

RPROVIDES_${PN} += "kernel-module-fdpm"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

do_configure[noexec] = "1"

python do_package_ipk_prepend () {
    d.setVar('ALLOW_EMPTY', '1')
}

KERNEL_MODULE_AUTOLOAD = "fdpm"
