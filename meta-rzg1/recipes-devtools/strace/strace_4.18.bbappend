#Fix build break with glibc 2.28
#   .../recipe-sysroot/usr/include/bits/statx.h:25:8: error: redefinition of 'struct statx_timestamp'
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-Workaround-for-build-error-with-glibc-2.28.patch' if '${GLIBCVERSION}' >= '2.28' else ' '}"
