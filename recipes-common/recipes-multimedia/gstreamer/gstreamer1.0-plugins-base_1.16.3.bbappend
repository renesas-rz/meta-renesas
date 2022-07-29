FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
	file://gstpbfilter.conf \
	file://0001-playback-Add-source-for-getting-video-filter-from-fi.patch \
"


do_install_append() {
    install -Dm 644 ${WORKDIR}/gstpbfilter.conf ${D}/etc/gstpbfilter.conf
    if [ "${USE_OMX_COMMON}" = "1" ]; then
        sed -i "s/videoconvert/vspmfilter/g" ${D}/etc/gstpbfilter.conf
    fi
}

FILES_${PN}_append = " \
    ${sysconfdir}/gstpbfilter.conf \
"
