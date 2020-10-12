#Fix build error with glib 2.28
# glob/globc: undefined reference to `__alloca'
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-4.2-Fix-glob-detection-to-avoid-build-error-with-glib.patch' if 'Buster' in '${CIP_MODE}' else ' '}"
