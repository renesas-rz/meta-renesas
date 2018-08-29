FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "git://github.com/thp/qt5-opengles2-test.git"
SRC_URI_append = " \
	git://github.com/smk-embedded/qt5-opengles2-test.git"