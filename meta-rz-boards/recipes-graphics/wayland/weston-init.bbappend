FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " \
	file://weston.sh \
	file://weston.ini \
"

do_install:append() {
	# Set the idle timeout to 0. (A value of 0 effectively disables the timeout.) and add log weston
	sed -e "/^ExecStart/s/$/ --idle-time=0/g" \
		-i ${D}/${systemd_system_unitdir}/weston.service

	# Set XDG_RUNTIME_DIR to /run/user/$UID (e.g. run/user/0)
	install -d ${D}/${sysconfdir}/profile.d
	install -m 0755 ${WORKDIR}/weston.sh ${D}/${sysconfdir}/profile.d/weston.sh
}

USERADD_PARAM:${PN} = "--system --home /home/weston --shell /bin/sh --user-group -G video,input,render,wayland weston"
