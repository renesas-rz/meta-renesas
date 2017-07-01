DEPENDS += "gstreamer libxml2"
EXTRA_OECONF := "${@'${EXTRA_OECONF}'.replace('--disable-experimental', '--enable-experimental')}"
EXTRA_OECONF += "--with-plugins=h264parse,videoparsers"

TARGET_CFLAGS += "-D_GNU_SOURCE"
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

FILES_${PN} += "${bindir}"
require gst-plugins-private-libs.inc
