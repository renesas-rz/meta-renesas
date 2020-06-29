FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append += " \
	file://0001-gzip-fseterr-adjust-to-glibc-2.28-libio.h-removal.patch \
"
