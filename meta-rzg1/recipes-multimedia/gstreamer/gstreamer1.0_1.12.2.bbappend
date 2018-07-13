FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI += "file://0001-gst-launch-Add-pad-probe-for-showing-fps.patch \
            file://0002-gst-launch-fix-padprobe-duration-error.patch \
"
