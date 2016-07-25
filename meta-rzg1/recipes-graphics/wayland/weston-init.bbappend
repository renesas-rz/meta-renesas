FILESEXTRAPATHS_prepend := "${THISDIR}/weston-init:"

SRC_URI_append = " file://weston \
		  file://weston-env \
"

do_install_append() {
	install -d ${D}/${sysconfdir}/default
	install -m 755 ${WORKDIR}/weston ${D}/${sysconfdir}/default/weston

	install -d ${D}/${sysconfdir}/profile.d
	install -m 755 ${WORKDIR}/weston-env ${D}/${sysconfdir}/profile.d/weston
}
