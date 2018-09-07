FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "${SOURCEFORGE_MIRROR}/tcl/${BPN}${PV}-src.tar.gz"
SRC_URI_append = " \
	https://sourceforge.net/projects/tcl/files/Tcl/${PV}/${BPN}${PV}-src.tar.gz"