SUMMARY = "Multimedia user libraries modules package groups"
LICENSE = "GPL-2.0-only & MIT"

PACKAGE_ARCH = "${TUNE_PKGARCH}"

DEPENDS = "mmngr-user-module mmngrbuf-user-module \
    vspmif-user-module \
"

PR = "r0"

inherit packagegroup

PACKAGES = " \
    packagegroup-multimedia-libs \
"

RDEPENDS:packagegroup-multimedia-libs = " \
    mmngr-user-module mmngrbuf-user-module \
    vspmif-user-module \
"
