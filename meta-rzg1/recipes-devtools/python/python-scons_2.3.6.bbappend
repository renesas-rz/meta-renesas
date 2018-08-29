FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "${SOURCEFORGE_MIRROR}/scons/scons-${PV}.tar.gz"
SRC_URI_append = " \
	https://sourceforge.net/projects/scons/files/scons/${PV}/scons-${PV}.tar.gz"