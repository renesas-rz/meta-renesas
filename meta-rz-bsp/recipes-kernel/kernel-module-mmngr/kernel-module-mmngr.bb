DESCRIPTION = "Memory Manager Kernel module for Renesas RZG2L/RZG3E"

require mmngr_drv.inc

PN = "kernel-module-mmngr"
PR = "r0"

S = "${WORKDIR}/git"
MMNGR_DRV_DIR = "mmngr_drv/mmngr/mmngr-module/files/mmngr"

SRC_URI:append = " \
    file://0001-Add-physical-address-translating-feature.patch \
    file://0002-mmngr-Get-start-address-of-MMP-area-from-DT.patch \
    file://0003-Do-not-parse-and-init-lossy-mem-area-for-RZ-G2L-Seri.patch \
    file://0004-mmngr-Add-MM_OMXBUF_SIZE-for-RZG2L-and-RZG3E-OMX.patch \
    file://0005-mmngr_drv-mmngr-module-drv-Update-physical-convert-f.patch \
    file://0006-mmngr-lock-mm-read-before-finding-VMA.patch \
    file://0007-mmngr-Update-following-kernel-6.1.patch \
    file://0008-mmngr-Do-not-parse-and-init-lossy-memory-area-for-RZ.patch \
    file://0009-mmngr-Fix-compilation-warnings-to-avoid-build-failur.patch \
    file://0010-mmngr-Update-following-kernel-6.12.patch \
    file://0011-mmngr-module-mmngr_drv-Change-return-type-of-mm_cnv_.patch \
"

MMNGR_CFG:rzg3e-family ?= "MMNGR_RZG3E"
MMNGR_CFG:rzg2l-family ?= "MMNGR_RZG2L"

includedir = "/usr/local/include"
SSTATE_ALLOW_OVERLAP_FILES += "${STAGING_INCDIR}"

# Build Memory Manager kernel module without suffix
KERNEL_MODULE_PACKAGE_SUFFIX = ""

do_compile() {
    export MMNGR_CONFIG=${MMNGR_CFG}
    export MMNGR_SSP_CONFIG="MMNGR_SSP_DISABLE"
    export MMNGR_IPMMU_MMU_CONFIG="IPMMU_MMU_DISABLE"

    cd ${S}/${MMNGR_DRV_DIR}/drv
    install -d ${INCSHARED}
    make all
}

do_install () {
    # Create destination directories
    install -d ${D}/${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/${MMNGR_DRV_DIR}/drv/Module.symvers ${KERNELSRC}/include/mmngr.symvers

    # Install kernel module
    install -m 644 ${S}/${MMNGR_DRV_DIR}/drv/mmngr.ko ${D}/${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/

    # Install shared header files to KERNELSRC(STAGING_KERNEL_DIR)
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/${MMNGR_DRV_DIR}/include/mmngr_public.h ${KERNELSRC}/include/
    install -m 644 ${S}/${MMNGR_DRV_DIR}/include/mmngr_private.h ${KERNELSRC}/include/
    install -m 644 ${S}/${MMNGR_DRV_DIR}/include/mmngr_public_cmn.h ${KERNELSRC}/include/
    install -m 644 ${S}/${MMNGR_DRV_DIR}/include/mmngr_private_cmn.h ${KERNELSRC}/include/

    # Install shared header file to ${includedir}
    install -m 644 ${S}/${MMNGR_DRV_DIR}/include/mmngr_public_cmn.h ${D}/${includedir}/
    install -m 644 ${S}/${MMNGR_DRV_DIR}/include/mmngr_private_cmn.h ${D}/${includedir}/
}

PACKAGES = "\
    ${PN} \
    ${PN}-dev \
    ${PN}-dbg \
"

FILES:${PN} = " \
    ${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/mmngr.ko \
"

RPROVIDES:${PN} += "kernel-module-mmngr"

KERNEL_MODULE_AUTOLOAD = "mmngr"

INSANE_SKIP:${PN}-dbg = "buildpaths"
