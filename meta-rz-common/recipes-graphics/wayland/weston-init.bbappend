FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
	file://weston.sh \
	file://weston.ini \
"

do_install_append() {
	if [ "X${EXT_GFX_BACKEND}" = "X1" ]; then
		sed -e "/^After=/s/$/ dbus.service multi-user.target/" \
		    -e "s/\$OPTARGS/--idle-time=0 \$OPTARGS/" \
		    -i ${D}/${systemd_system_unitdir}/weston@.service
	fi

	# Use own weston.ini file
	install -d ${D}/${sysconfdir}/xdg/weston
	install -m 0755 ${WORKDIR}/weston.ini ${D}/${sysconfdir}/xdg/weston/weston.ini

        # Set XDG_RUNTIME_DIR to /run/user/$UID (e.g. run/user/0)
        install -d ${D}/${sysconfdir}/profile.d
        install -m 0755 ${WORKDIR}/weston.sh ${D}/${sysconfdir}/profile.d/weston.sh

	# Fix weston.service and weston@.service run simultaneously.
	mv ${D}/${sysconfdir}/init.d/weston ${D}/${sysconfdir}/init.d/weston@
}

FILES_${PN}_append = " \
	${sysconfdir}/profile.d/weston.sh \
"

INITSCRIPT_NAME = "weston@"
