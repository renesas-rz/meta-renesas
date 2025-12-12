FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:remove = "https://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"

SRC_URI:append = " \
    git://github.com/renesas-rz/gst-plugins-bad.git;branch=RZ/1.22.12;protocol=https \
    file://0001-New-libbayersink-Bayer-to-RAW-converter-and-display-.patch \
    file://0002-ext-bayerconvert-add-bayerconvert-plugin.patch \
"
SRCREV = "87016cd5868939f82e4b504030917aafcc6a3614"

S  = "${WORKDIR}/git"

DEPENDS += "bayer2raw virtual/libgles2 mmngr-user-module mmngrbuf-user-module"

RDEPENDS:gstreamer1.0-plugins-bad-bayersink += "bayer2raw"
RDEPENDS:gstreamer1.0-plugins-bad-bayerconvert += "bayer2raw"

PACKAGECONFIG:append = "faac faad"
