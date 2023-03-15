inherit systemd

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "v4l2-init.service"

SRC_URI = " \
	file://v4l2-init.service \
	file://COPYING.MIT \
"

S = "${WORKDIR}"

FILES_${PN} += " \
	${systemd_unitdir}/system/v4l2-init.service \
"

do_install() {
	install -d ${D}/${systemd_unitdir}/system
	install -m 0644 ${WORKDIR}/v4l2-init.service ${D}/${systemd_unitdir}/system
}
