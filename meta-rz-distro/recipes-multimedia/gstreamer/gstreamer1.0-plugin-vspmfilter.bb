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

SRC_URI = " \
    ${GST_PLUGIN_VSPMFILTER_URL};protocol=https;branch=${BRANCH} \
    file://0001-Update-correct-base-number-of-VTOP-ioctl.patch \
"

SRC_URI:append:rzg3e-family = " \
    file://0002-Update-find_physical_address-functions-following-MM_.patch \
"

SRCREV ?= "e4e24c82272d0227f2288d4a471b4939699cade7"
SRCREV:rzg3e-family = "3bad93c42be267f909cf2b98bf8b18ebe48a764f"

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
