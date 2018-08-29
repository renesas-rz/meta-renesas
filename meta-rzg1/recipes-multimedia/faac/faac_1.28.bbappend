FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "${SOURCEFORGE_MIRROR}/faac/${BP}.tar.gz"
SRC_URI_append = " \
	https://sourceforge.net/projects/faac/files/faac-src/${BP}/${BP}.tar.gz"