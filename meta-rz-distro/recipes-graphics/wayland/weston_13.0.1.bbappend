FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " \
	file://0001-Add-support-setting-position-for-xdg_surface.patch \
"

