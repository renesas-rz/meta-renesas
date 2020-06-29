FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append += " \
           file://0001-weston-fix-error-undefined-reference-to-major.patch \
           "
