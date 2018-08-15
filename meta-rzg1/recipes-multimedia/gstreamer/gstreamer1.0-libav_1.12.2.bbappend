FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_append = " \
    file://0001-libav-down-rank-H264-type-in-libav-to-ensure-playbin.patch \
"
