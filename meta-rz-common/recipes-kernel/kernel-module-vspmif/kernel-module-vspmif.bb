DESCRIPTION = "VSP Manager Interface driver for the RZG2"

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://MIT-COPYING;md5=0ebf15a927e436cec699371cd890775c \
"

inherit module
require include/rz-modules-common.inc

DEPENDS = "linux-renesas kernel-module-vspm"
PN = "kernel-module-vspmif"
PR = "r0"

VSPMIF_DRV_URL = " \
    git://github.com/renesas-rcar/vspmif_drv.git"
BRANCH = "rcar_gen3"
SRCREV = "2fdb2838a5625e4231f1cff5d10079acc4954952"

SRC_URI = "${VSPMIF_DRV_URL};branch=${BRANCH}"

SRC_URI_append_rzg2l = " \
	file://0001-Add-ISU-to-vspmif.patch \
	file://0002-Remove-width-height-in-isu_dst_t.patch \
	file://0003-Correcting-variable-type.patch \
	file://0004-Remove-unused-memory.patch \
	file://0005-Correction-32bit-variable.patch \
"

S = "${WORKDIR}/git"
VSPMIF_DRV_DIR = "vspm_if-module/files/vspm_if"

includedir = "${RENESAS_DATADIR}/include"

# Build VSP Manager Interface kernel module without suffix
KERNEL_MODULE_PACKAGE_SUFFIX = ""

do_compile() {
    cd ${S}/${VSPMIF_DRV_DIR}/drv
    make all
}

do_install () {
    # Create destination directories
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/${VSPMIF_DRV_DIR}/drv/Module.symvers ${KERNELSRC}/include/vspm_if.symvers

    # Install kernel module
    install -m 644 ${S}/${VSPMIF_DRV_DIR}/drv/vspm_if.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/

    # Install shared header files to KERNELSRC(STAGING_KERNEL_DIR)
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/${VSPMIF_DRV_DIR}/include/vspm_if.h ${KERNELSRC}/include/

    # Install shared header file
    install -m 644 ${S}/${VSPMIF_DRV_DIR}/include/vspm_if.h ${D}/${includedir}/
}

PACKAGES = "\
    ${PN} \
    ${PN}-dev \
"

FILES_${PN} = " \
    /lib/modules/${KERNEL_VERSION}/extra/vspm_if.ko \
    /etc/modules-load.d/vspm_if.conf \
"

RPROVIDES_${PN} += "kernel-module-vspmif kernel-module-vspm-if"

KERNEL_MODULE_AUTOLOAD = "vspm_if vspmif"
