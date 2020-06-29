FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append += " \
           file://0001-xserver-xorg-fix-error-implicit-declaration-of-funct.patch \
           "
