FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "http://share.basyskom.com/demos/smarthome_src.tar.gz"
SRC_URI_append = " \
	http://support.garz-fricke.com/mirror/smarthome_src.tar.gz"