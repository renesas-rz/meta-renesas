require ../../include/rzg-modules-common.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://drv/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://drv/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"

DEPENDS = "linux-renesas kernel-module-mmngr"
PN = "kernel-module-fdpm"
PR = "r0"
SRC_URI = " \
    file://fdpm-kernel.tar.bz2 \
    file://0001-fdpm-Remove-unsed-variable-and-correct-type-of-varia.patch \
"
S = "${WORKDIR}/fdpm"

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
    # Create destination folder
    mkdir -p ${D}/lib/modules/${KERNEL_VERSION}/extra ${D}/usr/src/kernel/include

    # Copy driver and header files
    cp -f ${S}/drv/fdpm.ko ${D}/lib/modules/${KERNEL_VERSION}/extra

    # Copy header files to destination
    for f in ${FDPM_INSTALL_HEADERS} ; do
        cp -f ${KERNEL_HEADER_PATH}/${f} ${D}/usr/src/kernel/include
    done
    cp -f ${S}/drv/Module.symvers ${D}/usr/src/kernel/include/fdpm.symvers
}

# Append function to clean extract source
do_cleansstate_prepend() {
        bb.build.exec_func('do_clean_source', d)
}

do_clean_source() {
    # Check if kernel source exists before doing cleansstate
    if [ -d ${KERNELSRC} ] ; then
        for f in fdpm_drv.h fdpm.symvers ${FDPM_INSTALL_HEADERS} ; do
            find ${KERNELSRC} -name ${f} -delete
        done
    fi
}

PACKAGES = " \
    ${PN}-dev \
"

FILES_${PN}-dev = " \
    /usr/src/kernel/include/*.h \
    /usr/src/kernel/include/fdpm.symvers \
"

RPROVIDES_${PN} += "kernel-module-fdpm"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

do_configure[noexec] = "1"

python do_package_ipk_prepend () {
    d.setVar('ALLOW_EMPTY', '1')
}

KERNEL_MODULE_AUTOLOAD = "fdpm"
