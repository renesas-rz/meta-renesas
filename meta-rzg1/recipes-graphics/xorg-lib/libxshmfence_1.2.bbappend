#Fix build error with glibc due to memfd_create (add from version 2.27)
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://configure.ac_call_AC_USE_SYSTEM_EXTENSIONS.patch' if 'Buster' in '${CIP_MODE}' else ' '}"
