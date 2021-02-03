#Fix build break with glibc 2.28
LICENSE = "GPL-3.0-with-GCC-exception & GPLv3"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "${@'file://0058-libsanitizer-Use-pre-computed-size-of-struct-ustat-f.patch \
' if 'Buster' in '${CIP_MODE}' else ' '}"
