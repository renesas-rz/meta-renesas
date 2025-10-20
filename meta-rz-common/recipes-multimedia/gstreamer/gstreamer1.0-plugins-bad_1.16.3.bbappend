FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_remove = "https://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"

SRC_URI_append = " \ 
	git://github.com/renesas-rz/gst-plugins-bad.git;branch=RZ/1.16.3;protocol=https \
"
SRCREV = "4911f1dfc737005e6ee278fa7ca66c4d3af8a2bb"


DEPENDS += "weston virtual/libgles2 mmngr-user-module mmngrbuf-user-module"
DEPENDS += "${@bb.utils.contains('MACHINE_FEATURES', 'bayer2raw', bb.utils.contains('BBFILE_COLLECTIONS', 'rz-graphics', 'bayer2raw', '', d), '', d)}"


S = "${WORKDIR}/git"

do_configure_prepend() {
    cd ${S}
    ./autogen.sh --noconfigure
    cd ${B}
}

RDEPENDS_${PN} += "mmngr-user-module mmngrbuf-user-module"
RDEPENDS_gstreamer1.0-plugins-bad-bayersink += "bayer2raw"
RDEPENDS_gstreamer1.0-plugins-bad-bayerconvert += "bayer2raw"

PACKAGECONFIG_append = " faac faad"
