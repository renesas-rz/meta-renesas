FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "${SOURCEFORGE_MIRROR}/faac/faad2-src/faad2-${PV}/${BP}.tar.bz2;name=faad2"
SRC_URI_append = " \
	https://sourceforge.net/projects/faac/files/faad2-src/faad2-${PV}/${BP}.tar.bz2;name=faad2"