SUMMARY = "Multimedia kernel modules package groups"
LICENSE = "GPLv2 & MIT"

require include/omx-control.inc

DEPENDS = "kernel-module-mmngr kernel-module-mmngrbuf \
    kernel-module-vspm kernel-module-vspmif \
"

DEPENDS += '${@bb.utils.contains("USE_VIDEO_OMX", "1", "kernel-module-uvcs-drv", "", d )}'

PR = "r0"

inherit packagegroup

PACKAGES = " \
    packagegroup-multimedia-kernel-modules \
"

RDEPENDS_packagegroup-multimedia-kernel-modules = " \
    kernel-module-mmngr \
    kernel-module-mmngrbuf \
    kernel-module-vspm \
    kernel-module-vspmif \
"

RDEPENDS_packagegroup-multimedia-kernel-modules += " \
    ${@bb.utils.contains("USE_VIDEO_OMX", "1", "kernel-module-uvcs-drv", "", d )} \
"
