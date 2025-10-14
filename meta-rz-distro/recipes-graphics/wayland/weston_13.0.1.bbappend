FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " \
	file://0001-Add-support-setting-position-for-xdg_surface.patch \
	file://0002-Fix-issue-window-always-appears-at-top-left-of-the-s.patch \
"

