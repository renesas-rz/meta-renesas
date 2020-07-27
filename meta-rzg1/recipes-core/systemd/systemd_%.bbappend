PACKAGECONFIG_remove = "timesyncd"

# Fix build errors with glibc 2.28
#   src/basic/missing_syscall.h:236:19: error: static declaration of 'renameat2' follows non-static declaration
#   src/basic/missing_syscall.h:68:19: error: static declaration of 'memfd_create' follows non-static declaration
#   src/basic/fileio.c:1398:14: error: implicit declaration of function 'memfd_create'; did you mean 'timer_create'? [-Werror=implicit-function-declaration]
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-Fix-build-errors-with-glibc-2.28.patch' if 'Buster' in '${MACHINE_FEATURES}' else ' '}"
