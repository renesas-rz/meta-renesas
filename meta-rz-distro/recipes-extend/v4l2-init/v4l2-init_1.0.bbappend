FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " \
	file://v4l2-init.sh \
"

do_install:append () {
	install -d ${D}/root
	install -m 0744 ${WORKDIR}/v4l2-init.sh ${D}/root/v4l2-init.sh
}

FILES:${PN} += " /root/v4l2-init.sh "
RDEPENDS:${PN} += "bash"
