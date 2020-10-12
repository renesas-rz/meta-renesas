#Fix build break with glibc 2.27 or newer
#  | ../bison-3.0.4/lib/fseterr.c:77:3: error: #error "Please port gnulib fseterr.c to your platform! Look at the definitions of ferror and clearerr on your system, then report this to bug-gnulib."
#  |   #error "Please port gnulib fseterr.c to your platform! Look at the definitions of ferror and clearerr on your system, then report this to bug-gnulib."
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-Fix-build-error-with-glibc-2.27-or-newer.patch' if 'Buster' in '${CIP_MODE}' else ' '}"
