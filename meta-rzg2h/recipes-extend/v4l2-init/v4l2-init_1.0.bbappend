FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " \
	file://v4l2-init.sh \
"

do_install_append () {
	install -d ${D}/home/root
	install -m 0744 ${WORKDIR}/v4l2-init.sh ${D}/home/root/v4l2-init.sh
}

FILES_${PN} += " /home/root/v4l2-init.sh "
