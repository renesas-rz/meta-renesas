FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:remove = "https://gstreamer.freedesktop.org/src/gst-plugins-good/gst-plugins-good-${PV}.tar.xz"

SRC_URI:append = " \
    git://github.com/renesas-rz/gst-plugins-good.git;branch=RZ/1.22.12;protocol=https \
"
SRCREV = "93c06eee9526652b5adccca31abf442d866634d2"

DEPENDS += "mmngrbuf-user-module"

S = "${WORKDIR}/git"

EXTRA_OEMESON:append = " \
    -Dignore-fps-of-video-standard=true \
"

EXTRA_OEMESON:append_rzg2h = " \
     -Dcont-frame-capture=true \
"

