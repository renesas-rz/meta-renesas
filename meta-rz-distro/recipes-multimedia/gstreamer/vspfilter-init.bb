FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
LICENSE = "CLOSED"

COMPATIBLE_MACHINE = "(hihope-rzg2n|hihope-rzg2h)"

SRC_URI:append = " \
    file://vspfilter-setting.sh \
"

do_install() {
    install -d ${D}/${sysconfdir}/profile.d
    install -m 0755 ${WORKDIR}/vspfilter-setting.sh ${D}/${sysconfdir}/profile.d/vspfilter-setting.sh
}

do_configure[noexec] = "1"
do_patch[noexec] = "1"
do_compile[noexec] = "1"

FILES:${PN} = " \
    ${sysconfdir}/profile.d/vspfilter-setting.sh \
"
