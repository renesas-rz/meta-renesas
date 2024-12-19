FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:remove = "https://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"

SRC_URI:append = " \
    git://github.com/renesas-rz/gst-plugins-bad.git;branch=RZ/1.22.12;protocol=https \
"
SRCREV = "728304b71301f909142bd2d29099a8fc370e5e25"

S  = "${WORKDIR}/git"


PACKAGECONFIG:append = "faac faad"
