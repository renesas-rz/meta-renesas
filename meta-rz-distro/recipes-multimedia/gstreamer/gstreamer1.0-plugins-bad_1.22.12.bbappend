FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:remove = "https://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"

SRC_URI:append = " \
    git://github.com/renesas-rz/gst-plugins-bad.git;branch=RZ/1.22.12;protocol=https \
"
SRCREV = "e07995fa6e7c24868008826f177d9eaf9c1f88e1"

S  = "${WORKDIR}/git"


PACKAGECONFIG:append = "faac faad"
