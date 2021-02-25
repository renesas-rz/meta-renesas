# Workaround build error with glib 2.28 that enabled --enable-obsolete-rpc
#    | ../rpcbind-0.2.4/src/security.c:29:10: fatal error: rpcsvc/yp.h: No such file or directory
#    |  #include <rpcsvc/yp.h>
#    |           ^~~~~~~~~~~~~
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append = " file://0001-Avoid-build-error-with-glibc-enable-obsolete-rpc.patch"
