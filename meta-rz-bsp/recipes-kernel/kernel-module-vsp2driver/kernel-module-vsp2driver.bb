DESCRIPTION = "VSP2Driver for the RZG2"

LICENSE = "GPL-2.0-only & MIT"
LIC_FILES_CHKSUM = " \
    file://GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://MIT-COPYING;md5=192063521ce782a445a3c9f99a8ad560 \
"
inherit module
require include/rz-modules-common.inc

DEPENDS = "virtual/kernel kernel-module-vspm"
PN = "kernel-module-vsp2driver"
PR = "r0"

VSP2DRIVER_URL = " \
    git://github.com/renesas-rcar/vsp2driver.git"
BRANCH = "rcar-gen3"
SRCREV = "b3a116d8ce68371cac21011ca3b3190ae3576987"

SRC_URI = "${VSP2DRIVER_URL};branch=${BRANCH};protocol=https"

S = "${WORKDIR}/git"

SRC_URI:append = " \
    file://0001-vsp2driver-Change-return-type-of-platform_driver-rem.patch \
    file://0002-vsp2driver-Change-use-of-strlcpy-to-strscpy.patch \
    file://0003-vsp2driver-Rename-media_entity_remote_pad-to-media_p.patch \
    file://0004-vsp2driver-Convert-pipeline-handling-to-video_device.patch \
    file://0005-vsp2driver-Stop-using-entity-pipe-use-media_entity_p.patch \
    file://0006-vsp2driver-Refactor-subdev-pad-ops-to-v4l2_subdev_st.patch \
    file://0007-vsp2driver-Rename-subdev-init_cfg-operation-to-init_.patch \
    file://0008-vsp2driver-Rename-subdev-state-alloc-free.patch \
    file://0009-vsp2driver-Switch-buffer-prepare-fence-wait-to-dma_r.patch \
"

# Build VSP2 driver kernel module without suffix
KERNEL_MODULE_PACKAGE_SUFFIX = ""

do_compile() {
    cd ${S}/vsp2driver
    make all
}

do_install () {
    # Create destination directories
    install -d ${D}/${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/

    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/vsp2driver/Module.symvers ${KERNELSRC}/include/vsp2.symvers

    # Copy kernel module
    install -m 644 ${S}/vsp2driver/vsp2.ko ${D}/${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/

    # Install shared header files to KERNELSRC(STAGING_KERNEL_DIR)
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/vsp2driver/linux/vsp2.h ${KERNELSRC}/include/
}

PACKAGES = "\
    ${PN} \
    ${PN}-dbg \
"

FILES:${PN} = " \
   ${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/vsp2.ko \
    ${sysconfdir}/modules-load.d \
"

RPROVIDES:${PN} += "kernel-module-vsp2driver kernel-module-vsp2"

# Autoload VSP2Driver
KERNEL_MODULE_AUTOLOAD:append = " vsp2"

INSANE_SKIP:${PN}-dbg = "buildpaths"