inherit systemd

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "v4l2-init.service"

SRC_URI = " \
	file://v4l2-init.service \
	file://COPYING.MIT \
"

SRC_URI_append_rzg2l = " \
	file://v4l2-init-rzg2l.sh \
"

SRC_URI_append_rzg2h = " \
	file://v4l2-init-rzg2hmne.sh \
"

SRC_URI_append_rzv2m = " \
	file://v4l2-init-rzg2hmne.sh \
"

SRC_URI_append_rzv2ma = " \
	file://v4l2-init-rzg2hmne.sh \
"

S = "${WORKDIR}"

FILES_${PN} += " \
	${systemd_unitdir}/system/v4l2-init.service \
	/home/root/v4l2-init.sh \
"

do_install() {
	install -d ${D}/home/root
	install -m 0744 ${WORKDIR}/v4l2-init*.sh ${D}/home/root/v4l2-init.sh
	install -d ${D}/${systemd_unitdir}/system
	install -m 0644 ${WORKDIR}/v4l2-init.service ${D}/${systemd_unitdir}/system
}
