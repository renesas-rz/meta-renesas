#Fix build SDK error due to missing rpc/rpc.h
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

DEPENDS_remove_libc-musl = "${@' libtirpc' if 'Buster' in '${CIP_MODE}' else ' '}"
DEPENDS += "${@'libtirpc' if 'Buster' in '${CIP_MODE}' else ''}"

IsBuster = "${@'yes' if 'Buster' in '${CIP_MODE}' else ''}"
python () {
   if d.getVar('IsBuster') == 'yes':
	   d.setVar('ASNEEDED','')
}
CFLAGS_remove_libc-musl = "${@' -I${STAGING_INCDIR}/tirpc' if 'Buster' in '${CIP_MODE}' else ' '}"
CFLAGS_append = "${@' -I${STAGING_INCDIR}/tirpc' if 'Buster' in '${CIP_MODE}' else ' '}"
LDFLAGS_append = "${@' -ltirpc' if 'Buster' in '${CIP_MODE}' else ' '}"

SRC_URI += "${@'file://0001-daemon.c-Libtirpc-porting-fixes.patch \
		' if 'Buster' in '${CIP_MODE}' else ' '}"
