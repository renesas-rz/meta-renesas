require include/rz-modules-common.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"

DEPENDS = "linux-renesas kernel-module-vspm"
PN = "kernel-module-vsp2"
PR = "r0"

SRCREV = "8c172771d0fdec0ab7afb69a05f611370bd96489"
SRC_URI = " \
    git://github.com/renesas-devel/vsp2driver.git;protocol=git;branch=RCAR-GEN2/1.0.0 \
    file://0001-port-vsp2-to-kernel-4.4.patch \
    file://0002-fix-vsp2_exit-call.patch \
    file://0003-Support-exbuf-ioctl-command.patch \
    file://0004-vsp2-Port-vsp2-driver-to-Linux-kernel-v5.10.83-cip1.patch \
"
S = "${WORKDIR}/git"
includedir = "${RENESAS_DATADIR}/include"

#do_configure[noexec] = "1"

do_compile() {
    export VSP2_VSPMDIR=${KERNELSRC}/include
    export VSP2_VSPMSYMVERS=vspm.symvers
    cd ${S}/drv
    make all ARCH=arm
}

do_install() {
    # Create destination folder
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/drv/Module.symvers ${KERNELSRC}/include/vsp2.symvers

    # Install kernel module
    install -m 644 ${S}/drv/vsp2.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -m 644 ${S}/drv/Module.symvers ${D}/${includedir}/vsp2.symvers
}

PACKAGES = "\
    ${PN} \
    ${PN}-dev \
"

FILES_${PN}-dev = " \
    ${includedir}/vsp2.symvers \
"

RPROVIDES_${PN} += "kernel-module-vsp2"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

KERNEL_MODULE_AUTOLOAD = "vsp2"
