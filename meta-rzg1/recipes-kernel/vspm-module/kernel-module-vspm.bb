require ../../include/rzg-modules-common.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://drv/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://drv/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"
DEPENDS = "linux-renesas"
PN = "kernel-module-vspm"
PR = "r0"

SRC_URI = "file://vspm-kernel.tar.bz2 \
"

S = "${WORKDIR}/vspm"

VSPM_CFG_r8a7742 = "H2CONFIG"
VSPM_CFG_r8a7743 = "M2CONFIG"
VSPM_CFG_r8a7744 = "M2CONFIG"
VSPM_CFG_r8a7745 = "E2CONFIG"
VSPM_CFG_r8a77470 = "C2CONFIG"

sysroot_stage_all_append () {
    # add shared header files
    sysroot_stage_dir ${D}/usr/src/kernel/include ${SYSROOT_DESTDIR}${includedir}
}

do_compile() {
    export VSPM_CONFIG=${VSPM_CFG}
    cd ${S}/drv
    make all ARCH=arm
}

do_install() {
    # Create destination folder
    mkdir -p ${D}/lib/modules/${KERNEL_VERSION}/extra/ ${D}/usr/src/kernel/include

    # Copy kernel module
    cp -f ${S}/drv/vspm.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/

    # Copy shared header files
    cp -f ${S}/drv/Module.symvers ${D}/usr/src/kernel/include/vspm.symvers

    # Copy for vspm-user-module
    cp -f ${KERNELSRC}/include/vspm_if.h ${BUILDDIR}/include
}

# Append function to clean extract source
do_cleansstate_prepend() {
        bb.build.exec_func('do_clean_source', d)
}

do_clean_source() {
    rm -f ${KERNELSRC}/include/vspm_public.h
    rm -f ${KERNELSRC}/include/vsp_drv.h
    rm -f ${KERNELSRC}/include/tddmac_drv.h
    rm -f ${KERNELSRC}/include/vspm_if.h
    rm -f ${BUILDDIR}/include/vspm_if.h
    rm -f ${KERNELSRC}/include/vspm.symvers
}

PACKAGES = "\
    ${PN}-dev \
"

FILES_${PN}-dev = " \
    /usr/src/kernel/include \
    /usr/src/kernel/include/*.h \
    /usr/src/kernel/include/vspm.symvers \
"

RPROVIDES_${PN} += "kernel-module-vspm"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

do_configure[noexec] = "1"

python do_package_ipk_prepend () {
    d.setVar('ALLOW_EMPTY', '1')
}

KERNEL_MODULE_AUTOLOAD = "vspm"
