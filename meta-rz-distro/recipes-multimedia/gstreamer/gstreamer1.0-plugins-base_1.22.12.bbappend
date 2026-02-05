FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:remove = "https://gstreamer.freedesktop.org/src/gst-plugins-base/gst-plugins-base-${PV}.tar.xz"

SRC_URI:append = " \
    file://gstpbfilter.conf \
    git://github.com/renesas-rz/gst-plugins-base.git;branch=RZ/1.22.12;protocol=https \
"
SRCREV = "66da448e0d15a4b1e7b638299092b4b549dba974"

S  = "${WORKDIR}/git"

do_install:append() {
    install -Dm 644 ${WORKDIR}/gstpbfilter.conf ${D}${sysconfdir}/gstpbfilter.conf
    sed -i "s/default/vspmfilter/g" ${D}/etc/gstpbfilter.conf
}

FILES:${PN}:append = " ${sysconfdir}/gstpbfilter.conf"


