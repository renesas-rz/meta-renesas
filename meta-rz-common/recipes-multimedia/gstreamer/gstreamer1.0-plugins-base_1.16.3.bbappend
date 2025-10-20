FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "https://gstreamer.freedesktop.org/src/gst-plugins-base/gst-plugins-base-${PV}.tar.xz"

SRC_URI_append = " \
	file://gstpbfilter.conf \
	git://github.com/renesas-rz/gst-plugins-base.git;branch=RZ/1.16.3;protocol=https \
"

SRCREV = "88f333c8f72db2804b950029e9ba0bec68104bcf"

S  = "${WORKDIR}/git"


do_install_append() {
    install -Dm 644 ${WORKDIR}/gstpbfilter.conf ${D}/etc/gstpbfilter.conf
    if [ "${USE_OMX_COMMON}" = "1" ]; then
        sed -i "s/videoconvert/vspmfilter/g" ${D}/etc/gstpbfilter.conf
    fi
}

FILES_${PN}_append = " \
    ${sysconfdir}/gstpbfilter.conf \
"
LIC_FILES_CHKSUM = " \
    file://COPYING;md5=6762ed442b3822387a51c92d928ead0d \
"
