SUMMARY = "GStreamer VSP filter plugin"
SECTION = "multimedia"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING.LIB;md5=4fbd65380cdd255951079008b364516c"

COMPATIBLE_MACHINE = "(hihope-rzg2h|hihope-rzg2n)"

RENESAS_VSPFILTER_URL ?= "gitsm://github.com/renesas-rcar/gst-plugin-vspfilter.git;branch=RCAR-GEN3e/1.0.4;protocol=https"

VSPFILTER_CONF:hihope-rzg2n = "gstvspfilter-${MACHINE}_r8a774b1.conf"
VSPFILTER_CONF:hihope-rzg2h = "gstvspfilter-${MACHINE}_r8a774e1.conf"

SRC_URI = " \
    ${RENESAS_VSPFILTER_URL} \
    file://${VSPFILTER_CONF} \
    file://0001-vspfilter-Increase-number-of-buffers.patch \
"

SRCREV = "5984661366b7b0bdc79fb34b6dfbaaf9dba24623"

S = "${WORKDIR}/git"


inherit meson pkgconfig

DEPENDS += "gstreamer1.0 gstreamer1.0-plugins-base pkgconfig"

EXTRA_AUTORECONF:append = " -I ${STAGING_DATADIR}/aclocal"

FILES:${PN} = " \
    ${libdir}/gstreamer-1.0/libgstvspfilter.so \
    ${sysconfdir}/gstvspfilter.conf \
"

FILES:${PN}-dev = "${libdir}/gstreamer-1.0/libgstvspfilter.la"

FILES:${PN}-staticdev = "${libdir}/gstreamer-1.0/libgstvspfilter.a"

FILES:${PN}-dbg = " \
    ${libdir}/gstreamer-1.0/.debug \
    ${prefix}/src \
"

do_install:append() {
    install -Dm 644 ${WORKDIR}/${VSPFILTER_CONF} ${D}/etc/gstvspfilter.conf
}

RDEPENDS:${PN} = "kernel-module-vsp2driver gstreamer1.0 gstreamer1.0-plugins-base"
