#Fix build break with glibc 2.28
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-xfree86-Silence-a-new-glibc-warning.patch' if 'Buster' in '${MACHINE_FEATURES}' else ' '}"
