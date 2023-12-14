FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
	${@oe.utils.conditional("USE_ECC", "1", "file://0001-arm64-dts-renesas-r9a07g054l2-dev-smarc-update-memor.patch", "", d)} \
"
