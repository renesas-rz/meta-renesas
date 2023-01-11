FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += " \
	${@oe.utils.conditional("QT_DEMO", "1", " \
		file://weston-demo.ini ", "", d)} \
"

DEPENDS += " ${@oe.utils.conditional("QT_DEMO", "1", "qtdemo-extrafiles", "", d)} "

do_install_append() {
	if [ "${QT_DEMO}" = "1" ]; then
		# Configure own launcher with exist weston configuration
		cat ${WORKDIR}/weston-demo.ini >> ${D}/etc/xdg/weston/weston.ini
	fi
}
