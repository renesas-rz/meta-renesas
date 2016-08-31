FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append += " \
    file://0002-gst-1.0.7-gst-launch-Add-pad-probe.patch \
"
