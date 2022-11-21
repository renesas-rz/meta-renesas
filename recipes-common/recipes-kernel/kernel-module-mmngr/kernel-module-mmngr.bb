DESCRIPTION = "Memory Manager Kernel module for Renesas RZG2"
RENESAS_DATADIR ?= "/usr/local"
require mmngr_drv.inc

DEPENDS = "linux-renesas"
PN = "kernel-module-mmngr"
PR = "r0"

S = "${WORKDIR}/git"
MMNGR_DRV_DIR = "mmngr_drv/mmngr/mmngr-module/files/mmngr"

SRC_URI_append = " \
    file://0001-Add-physical-address-translating-feature.patch \
    file://0002-mmngr_drv-mmngr-Add-checking-NULL-vma-in-mm_cnv_addr.patch \
    file://0003-mmngr-Get-start-address-of-MMP-area-from-DT.patch \
    file://0004-Do-not-parse-and-init-lossy-mem-area-for-RZ-G2L-Seri.patch \
    file://0005-mmngr-module-mmngr_drv-add-support-IPMMU-for-RZG2M.patch \
    file://0006-mmngr-module-mmngr_drv-add-support-IPMMU-for-RZG2N.patch \
    file://0007-mmngr-module-mmngr_drv-add-support-IPMMU-for-RZG2E.patch \
    file://0008-mmngr-module-mmngr_drv-add-support-IPMMU-for-RZ-G2H.patch \
    file://0009-mmngr_drv-mmngr-Add-IPMMU-support-for-RZ-G2M-v3.0.patch \
    file://0010-mmngr_drv-mmngr-Update-PA-VA-mapping-table-for-HiHop.patch \
    file://0011-mmngr-change-address-setting-for-H3N-Swap-mode.patch \
    file://0012-Add-RZ-V2L-into-rzg2l_match-to-not-parse-and-init-lo.patch \
"

SRC_URI_append_rzg2l = " \
    file://0001-Reduce-MM_OMXBUF_SIZE-for-omx.patch \
    file://0002-Fix-ioctl-MM_IOC_VTOP-hang-up.patch \
    file://0003-mmngr_drv-mmngr-module-drv-Update-physical-convert-f.patch \
    file://0004-mmngr-lock-mm-read-before-finding-VMA.patch \
"

MMNGR_CFG ?= "MMNGR_SALVATORX"
MMNGR_CFG_ek874 = "MMNGR_EBISU"

includedir = "${RENESAS_DATADIR}/include"
SSTATE_DUPWHITELIST += "${STAGING_INCDIR}"

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
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/${MMNGR_DRV_DIR}/drv/Module.symvers ${KERNELSRC}/include/mmngr.symvers

    # Install kernel module
    install -m 644 ${S}/${MMNGR_DRV_DIR}/drv/mmngr.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/

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
"

FILES_${PN} = " \
    /lib/modules/${KERNEL_VERSION}/extra/mmngr.ko \
"

RPROVIDES_${PN} += "kernel-module-mmngr"

KERNEL_MODULE_AUTOLOAD = "mmngr"
