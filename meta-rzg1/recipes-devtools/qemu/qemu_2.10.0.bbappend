#Fix build SDK error due to confict memfd_create fucntion with glibc
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "${@'file://memfd-fix-configure-test.patch' if 'Buster' in '${CIP_MODE}' else ' '}"
