FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "${SOURCEFORGE_MIRROR}/project/pcre/pcre/${PV}/pcre-${PV}.tar.bz2"
SRC_URI_append = " \
	https://sourceforge.net/projects/pcre/files/pcre/${PV}/pcre-${PV}.tar.bz2"