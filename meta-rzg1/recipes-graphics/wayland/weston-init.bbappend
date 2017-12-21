FILESEXTRAPATHS_prepend := "${THISDIR}/weston-init:"

SRC_URI_append = " file://weston \
		  file://weston-env \
		  file://weston.ini \
"

INITSCRIPT_PARAMS = "start 9 5 2 . stop 9 0 1 6 ."

do_install_append() {
	install -d ${D}/${sysconfdir}/default
	install -m 755 ${WORKDIR}/weston ${D}/${sysconfdir}/default/weston

	install -d ${D}/${sysconfdir}/profile.d
	install -m 755 ${WORKDIR}/weston-env ${D}/${sysconfdir}/profile.d/weston

	install -D -m 644 ${WORKDIR}/weston.ini ${D}/etc/xdg/weston/weston.ini
}
