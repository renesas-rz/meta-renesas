SUMMARY = "GStreamer VSPM filter plugin"
SECTION = "multimedia"
LICENSE = "LGPL-2.0-only"
DEPENDS = "gstreamer1.0 gstreamer1.0-plugins-base pkgconfig vspmif-user-module kernel-module-mmngr mmngr-user-module mmngrbuf-user-module"
RDEPENDS:${PN} = "gstreamer1.0 gstreamer1.0-plugins-base vspmif-user-module kernel-module-mmngr mmngr-user-module mmngrbuf-user-module"
LIC_FILES_CHKSUM = "file://COPYING.LIB;md5=6762ed442b3822387a51c92d928ead0d"
inherit autotools pkgconfig

GST_PLUGIN_VSPMFILTER_URL = "git://github.com/renesas-rz/rzg_gstreamer_vspmfilter"

BRANCH ?= "rz_g2l"
BRANCH:rzg3e-family = "rz_g2"
BRANCH:rzg2h-family = "rz_g2"

SRC_URI = " \
    ${GST_PLUGIN_VSPMFILTER_URL};protocol=https;branch=${BRANCH} \
    file://0001-Update-correct-base-number-of-VTOP-ioctl.patch \
"

SRCREV ?= "f8966fd8d5e43806626e983499f83e381e9d9056"
SRCREV:rzg3e-family = "bdf95b989066ea841b1ee406c9761e7b89c00421"
SRCREV:rzg2h-family = "bdf95b989066ea841b1ee406c9761e7b89c00421"

S = "${WORKDIR}/git"
PV = "1.22.12"

FILES:${PN} = " \
    ${libdir}/gstreamer-1.0/libgstvspmfilter.so \
"

FILES:${PN}-dev = "${libdir}/gstreamer-1.0/libgstvspmfilter.la"
FILES:${PN}-staticdev = "${libdir}/gstreamer-1.0/libgstvspmfilter.a"
FILES:${PN}-dbg = " \
    ${libdir}/gstreamer-1.0/.debug \
    ${prefix}/src"
