FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " \
	file://0001-Add-support-for-setting-position-on-xdg_surface.patch \
	file://0002-compositor-Directly-use-a-timerfd-instead-of-a-wl_ev.patch \
	file://0003-compositor-Upgrade-repaint-timer-precision-to-nsec.patch \
"

