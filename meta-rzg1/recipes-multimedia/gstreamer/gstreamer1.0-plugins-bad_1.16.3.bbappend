FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_append = " \
    file://0001-waylandsink-Add-kms-display.patch \
    file://0002-waylandsink-fix-memory-leak-in-kms-mode.patch \
"
