FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_remove = "https://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"

SRC_URI_append = " \
    git://github.com/renesas-rcar/gst-plugins-bad.git;branch=RCAR-GEN3e/1.16.3;name=base \
    file://0001_fix_waylandsink_fullscreen.patch \
"

SRCREV_base = "3ef17d3c57e12f9d7536e464656b871a8949fa5b"

DEPENDS += "weston"

S = "${WORKDIR}/git"

do_configure_prepend() {
    cd ${S}
    ./autogen.sh --noconfigure
    cd ${B}
}

PACKAGECONFIG_append = " faac faad"
