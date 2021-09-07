FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
	file://weston.sh \
	file://weston.ini \
	file://init \
"

do_install_append() {
	# Use own weston.ini file
	install -d ${D}/${sysconfdir}/xdg/weston
	install -m 0755 ${WORKDIR}/weston.ini ${D}/${sysconfdir}/xdg/weston/weston.ini

        # Set XDG_RUNTIME_DIR to /run/user/$UID (e.g. run/user/0)
        install -d ${D}/${sysconfdir}/profile.d
        install -m 0755 ${WORKDIR}/weston.sh ${D}/${sysconfdir}/profile.d/weston.sh

	# Install own weston service
	install -Dm 0755 ${WORKDIR}/init ${D}/${sysconfdir}/init.d/weston
}

FILES_${PN}_append = " \
	${sysconfdir}/xdg/weston/weston.init \
	${sysconfdir}/profile.d/weston.sh \
"
