FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:remove = "https://gstreamer.freedesktop.org/src/gst-plugins-base/gst-plugins-base-${PV}.tar.xz"

SRC_URI:append = " \
    file://gstpbfilter.conf \
    git://github.com/renesas-rz/gst-plugins-base.git;branch=RZ/1.22.12;protocol=https \
"
SRCREV = "d3c3dbadd270621c3b1cc9df5d4e6c98f8c135ff"

S  = "${WORKDIR}/git"

do_install:append() {
    install -Dm 644 ${WORKDIR}/gstpbfilter.conf ${D}${sysconfdir}/gstpbfilter.conf
}

FILES:${PN}:append = " ${sysconfdir}/gstpbfilter.conf"


