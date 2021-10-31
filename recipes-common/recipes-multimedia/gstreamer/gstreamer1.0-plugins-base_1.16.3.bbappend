FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
	file://gstpbfilter.conf \
	file://0001-playback-Add-source-for-getting-video-filter-from-fi.patch \
"


do_install_append() {
    install -Dm 644 ${WORKDIR}/gstpbfilter.conf ${D}/etc/gstpbfilter.conf
}

FILES_${PN}_append = " \
    ${sysconfdir}/gstpbfilter.conf \
"
