#Fix build error with glib 2.28
# | ../../../findutils-4.6.0/gl/lib/freadahead.c:92:3: error: #error "Please port gnulib freadahead.c to your platform! Look at the definition of fflush, fread, ungetc on your system, then report this to bug-gnulib."
# |   #error "Please port gnulib freadahead.c to your platform! Look at the definition of fflush, fread, ungetc on your system, then report this to bug-gnulib."
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-Fix-build-error-with-glibc-2.28.patch' if 'Buster' in '${MACHINE_FEATURES}' else ' '}"

