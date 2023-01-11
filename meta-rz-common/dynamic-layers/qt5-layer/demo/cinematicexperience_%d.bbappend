FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
	file://0001-Add-exit-button-for-cinematic-demo.patch \
	file://exit.png \
"

do_install_append() {
	install ${WORKDIR}/exit.png ${D}${datadir}/${P}/content/images
}
