SUMMARY = "Multimedia kernel modules package groups"
LICENSE = "GPL-2.0-only & MIT"

PACKAGE_ARCH = "${TUNE_PKGARCH}"

DEPENDS = "kernel-module-mmngr kernel-module-mmngrbuf \
    kernel-module-vspm kernel-module-vspmif \
"

PR = "r0"

inherit packagegroup

PACKAGES = " \
    packagegroup-multimedia-kernel-modules \
"

RDEPENDS:packagegroup-multimedia-kernel-modules = " \
    kernel-module-mmngr \
    kernel-module-mmngrbuf \
    kernel-module-vspm \
    kernel-module-vspmif \
"
