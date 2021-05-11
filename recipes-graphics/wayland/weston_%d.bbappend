FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
	file://0001-clients-Fix-shell-background-image-setting.patch \
"
