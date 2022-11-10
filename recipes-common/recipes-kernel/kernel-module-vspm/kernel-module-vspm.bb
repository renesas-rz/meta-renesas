DESCRIPTION = "VSP Manager for the RZG2"

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://MIT-COPYING;md5=0ebf15a927e436cec699371cd890775c \
"

inherit module
require include/rzg2-modules-common.inc

DEPENDS = "linux-renesas"
PN = "kernel-module-vspm"
PR = "r0"

VSPM_DRV_URL = "git://github.com/renesas-rcar/vspm_drv.git"
BRANCH = "rcar_gen3"
SRCREV = "07787fc1168e7fe37c305aca151a6f756f35874f"

SRC_URI = "${VSPM_DRV_URL};branch=${BRANCH}"

SRC_URI_append_rzg2l = " \
        file://0001-Add-ISU-driver.patch \
        file://0002-Add-option-ISU_CSC_RAW.patch \
        file://0003-Add-ISU-to-VSPM.patch \
        file://0004-Modify-Makefile.patch \
        file://0005-remove-work-around-clock-reset-supply.patch \
        file://0006-Support-MUTUAL-mode-for-ISU.patch \
        file://0007-Update-and-fix-some-small-bugs-of-ISU-driver.patch \
        file://0008-Correcting-variable-type.patch \
	file://0009-Wrong-initialize-value-of-clip.patch \
	file://0010-Fix-wrong-output-size-in-setting-case-rs_par-is-NULL.patch \
	file://0011-Fix-error-cannot-detect-NOOUT-in-case-rs_par-NULL.patch \
	file://0012-vspm_main-Update-isu-clock-enable.patch \
	file://0013-vspm-isu-Check-addr-of-1st-plane-in-parameter-for-RP.patch \
"

S = "${WORKDIR}/git"
VSPM_DRV_DIR = "vspm-module/files/vspm"
includedir = "${RENESAS_DATADIR}/include"

# Build VSP Manager kernel module without suffix
KERNEL_MODULE_PACKAGE_SUFFIX = ""

do_compile() {
    cd ${S}/${VSPM_DRV_DIR}/drv
    make all
}

do_install () {
    # Create destination directories
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/${VSPM_DRV_DIR}/drv/Module.symvers ${KERNELSRC}/include/vspm.symvers

    # Install kernel module
    install -m 644 ${S}/${VSPM_DRV_DIR}/drv/vspm.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/

    # Install shared header files to KERNELSRC(STAGING_KERNEL_DIR)
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/${VSPM_DRV_DIR}/include/vspm_public.h ${KERNELSRC}/include/
    install -m 644 ${S}/${VSPM_DRV_DIR}/include/vspm_cmn.h ${KERNELSRC}/include/
    install -m 644 ${S}/${VSPM_DRV_DIR}/include/vsp_drv.h ${KERNELSRC}/include/
    install -m 644 ${S}/${VSPM_DRV_DIR}/include/fdp_drv.h ${KERNELSRC}/include/

    # Install shared header files
    install -m 644 ${S}/${VSPM_DRV_DIR}/include/vspm_cmn.h ${D}/${includedir}/
    install -m 644 ${S}/${VSPM_DRV_DIR}/include/vsp_drv.h ${D}/${includedir}/
    install -m 644 ${S}/${VSPM_DRV_DIR}/include/fdp_drv.h ${D}/${includedir}/
}

do_install_append_rzg2l () {
    install -m 644 ${S}/${VSPM_DRV_DIR}/include/isu_drv.h ${KERNELSRC}/include/
    install -m 644 ${S}/${VSPM_DRV_DIR}/include/isu_drv.h ${D}/${includedir}/
}

# Should also clean deploy/licenses directory
# for module when do_clean.
do_clean[cleandirs] += "${LICENSE_DIRECTORY}/${PN}"

PACKAGES = " \
    ${PN} \
    ${PN}-dev \
"

FILES_${PN} = " \
    /lib/modules/${KERNEL_VERSION}/extra/vspm.ko \
"

RPROVIDES_${PN} += "kernel-module-vspm"

# Autoload VSPM
KERNEL_MODULE_AUTOLOAD_append = " vspm"
