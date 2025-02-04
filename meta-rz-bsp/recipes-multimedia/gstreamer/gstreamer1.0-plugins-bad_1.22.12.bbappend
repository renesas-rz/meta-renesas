FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:remove = "https://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"

SRC_URI:append = " \
    git://github.com/renesas-rz/gst-plugins-bad.git;branch=RZ/1.22.12;protocol=https \
"
SRCREV = "79f3733bb085d07a78e996bf8d935ad31d43c7b1"

S  = "${WORKDIR}/git"


PACKAGECONFIG:append = "faac faad"
