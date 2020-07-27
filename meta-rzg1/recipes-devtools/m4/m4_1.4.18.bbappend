#Fix build break with glibc 2.28
# | ../../m4-1.4.18/lib/freadahead.c:92:3: error: #error "Please port gnulib freadahead.c to your platform! Look at the definition of fflush, fread, ungetc on your system, then report this to bug-gnulib."
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://m4-1.4.18-glibc-change-work-around.patch' if 'Buster' in '${MACHINE_FEATURES}' else ' '}"
