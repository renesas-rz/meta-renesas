FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " \
	file://0001-Add-support-for-setting-position-on-xdg_surface.patch \
"

