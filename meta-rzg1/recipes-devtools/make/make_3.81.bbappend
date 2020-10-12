#Fix build error with glib 2.28
# glob/globc: undefined reference to `__alloca'
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-Fix-glob-detection-to-avoid-build-error-with-glibc-2.patch' if '${GLIBCVERSION}' >= '2.28' else ' '}"
