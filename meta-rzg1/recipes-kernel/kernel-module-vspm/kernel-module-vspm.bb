inherit module
require include/rz-modules-common.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://drv/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://drv/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"
DEPENDS = "linux-renesas"
PN = "kernel-module-vspm"
PR = "r0"

SRC_URI = "file://vspm-kernel.tar.bz2"

S = "${WORKDIR}/vspm"
includedir = "${RENESAS_DATADIR}/include"

VSPM_CFG_r8a7742 = "H2CONFIG"
VSPM_CFG_r8a7743 = "M2CONFIG"
VSPM_CFG_r8a7744 = "M2CONFIG"
VSPM_CFG_r8a7745 = "E2CONFIG"
VSPM_CFG_r8a77470 = "C2CONFIG"

do_compile() {
    export VSPM_CONFIG=${VSPM_CFG}
    cd ${S}/drv
    make all ARCH=arm
}

do_install() {
    # Create destination folder
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/drv/Module.symvers ${KERNELSRC}/include/vspm.symvers

    # Install kernel module
    install -m 644 ${S}/drv/vspm.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/

    # Install shared header files to KERNELSRC(STAGING_KERNEL_DIR)
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/include/vspm_if.h ${KERNELSRC}/include/

    install -m 644 ${S}/include/vspm_if.h ${D}/${includedir}/
}

PACKAGES = "\
    ${PN}-dev \
"

FILES_${PN}-dev = " \
    ${includedir}/*.h \
    ${includedir}/vspm.symvers \
"

RPROVIDES_${PN} += "kernel-module-vspm"

python do_package_ipk_prepend () {
    d.setVar('ALLOW_EMPTY', '1')
}

KERNEL_MODULE_AUTOLOAD = "vspm"
