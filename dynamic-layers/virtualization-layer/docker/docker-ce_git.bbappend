do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${WORKDIR}/docker.init ${D}${sysconfdir}/init.d/docker.init
}
