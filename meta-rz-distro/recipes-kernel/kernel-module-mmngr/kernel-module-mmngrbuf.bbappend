FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " \
    file://99-rgnmmbuf.rules \
"

do_install:append() {
    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0644 ${WORKDIR}/99-rgnmmbuf.rules ${D}${sysconfdir}/udev/rules.d/
}

FILES:${PN}:append = " ${sysconfdir}/udev/rules.d/99-rgnmmbuf.rules"
