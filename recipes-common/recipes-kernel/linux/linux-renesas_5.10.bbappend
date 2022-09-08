FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append = " \
    file://0001-clk-renesas-rzg2l-Fix-reset-status-function.patch \
"
