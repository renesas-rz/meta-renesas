FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append += " \
	file://0001-Fix-pulseaudio-mutex-issue-when-do-pause-in-gstreame.patch \
"
