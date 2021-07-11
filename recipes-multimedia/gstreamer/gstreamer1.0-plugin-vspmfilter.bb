SUMMARY = "GStreamer VSPM filter plugin"
SECTION = "multimedia"
LICENSE = "LGPLv2"
DEPENDS = "gstreamer1.0 gstreamer1.0-plugins-base pkgconfig vspmif-user-module kernel-module-mmngr kernel-module-mmngrbuf mmngr-user-module mmngrbuf-user-module"
LIC_FILES_CHKSUM = "file://COPYING.LIB;md5=6762ed442b3822387a51c92d928ead0d"
inherit autotools pkgconfig

SRC_URI = " \
    file://vspmfilter.tar.xz \
    file://0001-Modify-vspmfilter-for-deinterlace.patch \
    file://0002-Fix-issue-vspmfilter-cannot-plugin.patch \
    file://0003-Support-Resize-and-Color-fomat.patch \
"

S = "${WORKDIR}/vspmfilter"
PV = "1.16.3"

FILES_${PN} = " \
    ${libdir}/gstreamer-1.0/libgstvspmfilter.so \
"

FILES_${PN}-dev = "${libdir}/gstreamer-1.0/libgstvspmfilter.la"
FILES_${PN}-staticdev = "${libdir}/gstreamer-1.0/libgstvspmfilter.a"
FILES_${PN}-dbg = " \
    ${libdir}/gstreamer-1.0/.debug \
    ${prefix}/src"
