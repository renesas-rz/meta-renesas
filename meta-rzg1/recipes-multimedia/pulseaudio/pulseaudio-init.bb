SUMMARY = "Startup script for the PulseAudio sound server"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "							\
	file://${COREBASE}/LICENSE;md5=4d92cd373abda3937c2bc47fbc49d690	\
"

SRC_URI = "								\
	file://pulseaudio.init						\
"

S = "${WORKDIR}"

do_install() {
	install -d ${D}/${sysconfdir}/init.d
	install -m755 ${WORKDIR}/pulseaudio.init ${D}/${sysconfdir}/init.d/pulseaudio
}

DEPENDS_${PN} = "pulseaudio"

inherit update-rc.d

INITSCRIPT_NAME = "pulseaudio"
INITSCRIPT_PARAMS = "start 20 2 3 4 5 . stop 20 0 1 6 ."
