#Fix build break with glibc 2.28
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "${@'file://0004-fix-ftbfs-glibc-2.28.patch \
' if 'Buster' in '${CIP_MODE}' else ' '}"
