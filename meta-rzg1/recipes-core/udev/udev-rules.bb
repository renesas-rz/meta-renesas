DESCRIPTION = "Custom udev rules for BSP"
SECTION = "core"
PRIORITY = "optional"
LICENSE = "GPLv2+"

LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"

PV = "1.0"
PR = "r0"

S = "${WORKDIR}"

RDEPENDS_${PN} = "udev"

FILESEXTRAPATHS_prepend := '${@ "${THISDIR}/files:" if 'wayland' in '${DISTRO_FEATURES}' else ""}'

SRC_URI := " \
    file://COPYING \
    file://51-touchscreen.rules \
    file://52-vsp2.rules \
"

do_install_append() {
    install -d ${D}${sysconfdir}/udev/rules.d/
    install -m 0644 ${WORKDIR}/51-touchscreen.rules ${D}${sysconfdir}/udev/rules.d/
    install -m 0644 ${WORKDIR}/52-vsp2.rules ${D}${sysconfdir}/udev/rules.d/
}
