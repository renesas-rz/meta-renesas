FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

DEPENDS += " kernel-module-mmngr mmngr-user-module kernel-module-mmngrbuf mmngrbuf-user-module"

SRC_URI += " \
    file://0001-gst-launch-fix-padprobe-duration-error.patch \
"
