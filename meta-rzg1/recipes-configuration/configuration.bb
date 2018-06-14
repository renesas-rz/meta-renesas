LICENSE = "CLOSED"
DESCRIPTION = "This is configuration for environments"

FILESEXTRAPATHS_prepend = "${THISDIR}/files:"
SRC_URI = "file://profile "

do_install () {
	install -d ${D}/${ROOT_HOME}
	cp ${S}/../profile ${D}/${ROOT_HOME}/.profile
}

PACKAGES = "${PN}"

FILES_${PN} = " /* "
