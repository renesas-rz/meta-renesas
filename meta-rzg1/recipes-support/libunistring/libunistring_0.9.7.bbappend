#Fix build error with glibc due to memfd_create (added from version 2.27)
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-Fix-build-error-with-glibc-2.28.patch' if '${GLIBCVERSION}' >= '2.27' else ' '}"
