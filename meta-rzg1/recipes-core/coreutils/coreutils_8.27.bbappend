#Fix build error with glib 2.28
# glob/globc: undefined reference to `__alloca'
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-Fix-build-error-with-glibc-2.28.patch' if 'Buster' in '${MACHINE_FEATURES}' else ' '}"
