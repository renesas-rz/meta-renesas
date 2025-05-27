FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_remove = "https://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"

SRC_URI_append = " \
    gitsm://github.com/renesas-rcar/gst-plugins-bad.git;branch=RCAR-GEN3e/1.16.3;name=base \
    file://0001_fix_waylandsink_fullscreen.patch \
    file://0002-waylandsink-Add-set-window-position.patch \
    file://0003-waylandsink-Add-property-out-w-out-h-to-display-expe.patch \
    file://0004-waylandsink-Add-mising-code-for-scale-feature.patch \
    file://0005-gstreamer-waylandsink-disable-subsurface-in-fullscre.patch \
    file://0006-waylandsink-Add-support-for-I420-in-dmabuf.patch \
    ${@bb.utils.contains('MACHINE_FEATURES', 'bayer2raw', bb.utils.contains('BBFILE_COLLECTIONS', 'rz-graphics', 'file://0007-New-libbayersink-Bayer-to-RAW-converter-and-display-.patch', '', d), '', d)} \
    ${@bb.utils.contains('MACHINE_FEATURES', 'bayer2raw', bb.utils.contains('BBFILE_COLLECTIONS', 'rz-graphics', 'file://0008-ext-bayerconvert-add-bayerconvert-plugin.patch', '', d), '', d)} \
 "

SRC_URI_append_rzg2l = " \
    file://0001-gstreamer-waylandsink-Add-stride-restriction-to-buff.patch \
    ${@bb.utils.contains('MACHINE_FEATURES', 'bayer2raw', bb.utils.contains('BBFILE_COLLECTIONS', 'rz-graphics', 'file://0002-ext-bayersink-Remove-EGL_PIXMAP_BIT-while-using-mali.patch', '', d), '', d)} \
"

SRCREV_base = "3ef17d3c57e12f9d7536e464656b871a8949fa5b"

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
