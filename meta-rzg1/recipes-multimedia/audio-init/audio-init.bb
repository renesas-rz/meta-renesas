UMMARY = "Startup script for Setting DVC sound module"
LICENSE = "CLOSED"

SRC_URI = "file://init.sh"

S = "${WORKDIR}"

do_install() {
        install -d ${D}/${sysconfdir}/profile.d
        install -m755 ${WORKDIR}/init.sh ${D}/${sysconfdir}/profile.d/audio-init.sh
}
