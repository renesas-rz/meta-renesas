FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_remove = "https://gstreamer.freedesktop.org/src/gst-plugins-good/gst-plugins-good-${PV}.tar.xz"
SRC_URI_append = " \
    git://github.com/renesas-rz/gst-plugins-good.git;branch=RZ/1.16.3;protocol=https \
"

SRCREV = "58f1eea1eeed684fc49c16d79a8cadfe3ad1f67c"

DEPENDS += "mmngrbuf-user-module"
RDEPENDS_${PN} += "mmngrbuf-user-module"

S = "${WORKDIR}/git"

EXTRA_OEMESON_append = " \
    -Dignore-fps-of-video-standard=true \
"

EXTRA_OEMESON_append_rzg2h = " \
     -Dcont-frame-capture=true \
"
LIC_FILES_CHKSUM = " \
    file://COPYING;md5=a6f89e2100d9b6cdffcea4f398e37343 \
"
