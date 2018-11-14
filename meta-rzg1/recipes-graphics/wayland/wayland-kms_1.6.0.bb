SUMMARY = "KMS library for Wayland"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://wayland-kms.c;md5=ada5e501886979a97a13ecc3957524a5"

PV = "1.6.0+git${SRCREV}"

SRCREV = "229a635a7972ac38532f944c799ecd16abf6aea2"
SRC_URI = "git://github.com/thayama/wayland-kms;protocol=git;branch=master"

COMPATIBLE_MACHINE = "(r8a7742|r8a7743|r8a7744|r8a7745|r8a77470)"
S = "${WORKDIR}/git"
DEPENDS = "libdrm wayland gles-user-module wayland-native"

inherit autotools pkgconfig

FILES_${PN} = "${libdir}/libwayland-kms.so.*"
FILES_${PN}-dev = " \
    ${libdir}/libwayland-kms.la \
    ${libdir}/libwayland-kms.so \
    ${libdir}/pkgconfig/* \
    ${includedir}/* \
"
FILES_${PN}-staticdev += "${libdir}/libwayland-kms.a"
