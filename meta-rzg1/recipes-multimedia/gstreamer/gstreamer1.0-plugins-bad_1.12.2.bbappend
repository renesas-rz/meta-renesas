FILESEXTRAPATHS_prepend_rzg1 := '${THISDIR}/${PN}:'
SRC_URI_remove = "http://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"
SRC_URI_append = " \
    git://github.com/renesas-rcar/gst-plugins-bad.git;branch=RCAR-GEN3/1.12.2;name=base \
    git://anongit.freedesktop.org/gstreamer/common;destsuffix=git/common;name=common \
"

SRCREV_base = "db554fad172f2dabb0f7a75ef1e8e4cb35e172c9"
SRCREV_common = "48a5d85ebf4a0bad1c997c83100f710fe2154fbf"
SRCREV_FORMAT = "base"
DEPENDS += "weston virtual/mesa libdrm"

S = "${WORKDIR}/git"

do_configure_prepend() {
    cd ${S}
    ./autogen.sh --noconfigure
    cd ${B}
}

SRC_URI += " \
    file://0001-waylandsink-Add-set-window-position.patch \
    file://0002-waylandsink-Add-set-window-scale-feature.patch \
    file://0003-waylandsink-Add-fullscreen-display-feature.patch \
    file://0004-Solve-issue-horizontal-noise-from-camera-due-to-usin.patch \
    file://0005-camerabin-add-capsfilter-into-wrapper-camerabin-for-.patch \
    file://0006-Change-encode-element-from-theora-to-omxh264enc.patch \
    file://0007-Temperory-disable-audio-as-RCA-camera-do-not-use-it.patch \
    file://0005-waylandsink-Don-t-wait-for-the-wl_surface_frame-call.patch \
    file://0009-waylandsink-Support-Wayland-KMS-to-improve-performan.patch \
    file://0010-Revert-waylandsink-Change-the-size-of-area_surface-s.patch \
    file://0011-waylandsink-Fix-memory-leak-error-in-DU-because-un-c.patch \
    file://0012-waylandsink-fix-memory-leak-in-kms-mode.patch \
"

RDEPENDS_gstreamer1.0-plugins-bad_append = " libwayland-egl gles-user-module "
RDEPENDS_libgstgl-1.0_append = " gles-user-module "
RDEPENDS_gstreamer1.0-plugins-bad-opengl_append = " gles-user-module "

PACKAGECONFIG_append = " faac faad"
