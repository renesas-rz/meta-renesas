FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_remove = "https://gstreamer.freedesktop.org/src/gstreamer/gstreamer-${PV}.tar.xz"
SRC_URI_append = " \
	git://github.com/renesas-rz/gstreamer1.0.git;branch=RZ/1.16.3;protocol=https \
"
SRCREV = "7d21d62b391e99e667822e75704f7b540b800d92"

S = "${WORKDIR}/git"
