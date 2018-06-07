FILESEXTRAPATHS_prepend_rzg1 := '${THISDIR}/${PN}:'

DEPENDS += "weston virtual/mesa"

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