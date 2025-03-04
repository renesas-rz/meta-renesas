FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:remove = "https://gstreamer.freedesktop.org/src/gstreamer/gstreamer-${PV}.tar.xz"

SRC_URI:append = " \
    git://github.com/renesas-rz/gstreamer1.0.git;branch=RZ/1.22.12;protocol=https \
"

SRCREV = "160c3291156859b98bd7a5ad9e38f3ca01707dea"

S = "${WORKDIR}/git"
