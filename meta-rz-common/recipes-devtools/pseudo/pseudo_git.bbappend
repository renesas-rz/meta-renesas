FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " \
    file://0001-avoid-openat2-usage-via-syscall.patch \
"