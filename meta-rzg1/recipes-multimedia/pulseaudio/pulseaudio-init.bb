SUMMARY = "Startup script for the PulseAudio sound server"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "							\
	file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302 \
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
