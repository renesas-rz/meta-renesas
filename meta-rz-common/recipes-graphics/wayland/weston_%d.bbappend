FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
	file://0001-clients-Fix-shell-background-image-setting.patch \
	file://0002-xdg-shell-Allow-fullscreen-surfaces-to-not-cover-the.patch \
	file://0003-Add-support-setting-position-for-xdg_surface-and-wl_.patch \
"
