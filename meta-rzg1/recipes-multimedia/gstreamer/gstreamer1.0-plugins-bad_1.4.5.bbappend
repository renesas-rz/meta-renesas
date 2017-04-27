FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI = "gitsm://github.com/renesas-rcar/gst-plugins-bad.git;branch=RCAR-GEN3/1.4.5"
SRC_URI += " \
    file://0001-gl-do-not-check-for-GL-GLU-EGL-GLES2-libs-if-disable.patch \
    file://configure-allow-to-disable-libssh2.patch"
SRCREV = "8cba063cf12ec4819f3dae4b95178288843caa57"

SRC_URI_append += " \
    file://0001-gst145-waylandsink-Add-set-window-position.patch \
    file://0002-gst145-waylandsink-Add-set-window-scale.patch \
    file://0003-gst145-waylandsink-Set-window-fullscreen.patch \
    file://0004-gst145-waylandsink-Restrict-the-number-of-buffers-in.patch \
    file://0005-gst145-waylandsink-Ensure-wayland-display-create-queue-even.patch \
    file://0006-gst145-waylandsink-Don-t-wait-for-the-wl_surface_frame-call.patch \
    file://0007-gst145-waylandsink-Change-the-color-format-mapping-for-XBGR.patch \
    file://0008-gst145-waylandsink-Correct-coding-style-by-gst-indent.patch \
    file://0009-gst-145-waylandsink-Preliminary-for-the-gstdmabuf-allocat.patch \
    file://waylandsink-Fix-a-potential-build-issue-caused-by-mi.patch \
"

DEPENDS += "weston"

S = "${WORKDIR}/git"

do_configure_prepend() {
    cd ${S}
    ./autogen.sh --noconfigure
    cd ${B}
}
RDEPENDS_${PN} = "libwayland-egl"
