FILESEXTRAPATHS_prepend_rzg1 := '${THISDIR}/${PN}:'
SRC_URI_remove = "http://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"
SRC_URI_append = " git://github.com/renesas-rcar/gst-plugins-bad.git;branch=RCAR-GEN3/1.12.2"

SRCREV = "0a4f4f7c2d0185c91ac3c768a8e8d20dc292f8ee"

DEPENDS += "weston virtual/mesa"


S = "${WORKDIR}/git"

# submodule is extracted before do_populate_lic
addtask do_init_submodule after do_unpack before do_patch

do_init_submodule() {
    export http_proxy=${http_proxy}
    export https_proxy=${https_proxy}
    export HTTP_PROXY=${HTTP_PROXY}
    export HTTPS_PROXY=${HTTPS_PROXY}
    cd ${S}
    git submodule init
    git submodule update
}

do_configure_prepend() {
    cd ${S}
    ./autogen.sh --noconfigure
    cd ${B}
}

SRC_URI += " \
    file://0001-gst1122-waylandsink-Add-set-window-position.patch \
    file://0002-gst1122-waylandsink-Add-set-window-scale.patch \
    file://0003-gst1122-waylandsink-Set-window-fullscreen.patch \
    file://0004-gst1122-waylandsink-Restrict-the-number-of-buffers-in.patch \
    file://0005-gst1122-waylandsink-Ensure-wayland-display-create-queue-even.patch \
    file://0006-gst1122-waylandsink-Don-t-wait-for-the-wl_surface_frame-call.patch \
    file://0007-gst1122-waylandsink-Change-the-color-format-mapping-for-XBGR.patch \
    file://0008-gst1122-waylandsink-Correct-coding-style-by-gst-indent.patch \
    file://waylandsink-Fix-a-potential-build-issue-caused-by-mi.patch \
"

RDEPENDS_gstreamer1.0-plugins-bad += "libwayland-egl"