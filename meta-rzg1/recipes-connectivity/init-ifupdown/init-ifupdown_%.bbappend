FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = " file://interfaces_autoWlan"

do_install_append () {
	install -d ${D}/${sysconfdir}/network
	cp ${S}/interfaces_autoWlan ${D}/${sysconfdir}/network/interfaces
}
