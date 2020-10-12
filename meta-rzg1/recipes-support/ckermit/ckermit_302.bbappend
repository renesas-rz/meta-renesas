#Fix build break with glibc 2.28
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://ckermit-9.0.302-fix_build_with_glibc_2_28_and_earlier.patch' if '${GLIBCVERSION}' >= '2.28' else ' '}"
