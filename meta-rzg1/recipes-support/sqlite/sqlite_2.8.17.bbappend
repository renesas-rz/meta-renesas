FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "http://www.hwaci.com/sw/sqlite/sqlite-${PV}.tar.gz"
SRC_URI_append = " \
	http://www.sqlite.org/sqlite-${PV}.tar.gz"