FILESEXTRAPATHS_prepend_rzg1 := '${THISDIR}/${PN}:'

SRC_URI += " \
    file://0001-gst1122-v4l2src-Add-NV16-color-format-support.patch \
    file://0002-gst1122-v4l2src-support-v4l2src-for-rcar.patch \
    file://0006-gst1122-Add-the-Copyright-year.patch \
    file://0007-gst1122-v4l2src-Support-crop-function.patch \
    file://0008-gst1122-v4l2src-Update-feature-for-crop-function.patch \
    file://0001-qtmux-remove-checking-PTS-in-gst_qt_mux_add_buffer.patch \
    file://0009-v4l2object-Support-enable-cont-frame-capture-configu.patch \
"
EXTRA_OECONF_append = " --enable-cont-frame-capture"