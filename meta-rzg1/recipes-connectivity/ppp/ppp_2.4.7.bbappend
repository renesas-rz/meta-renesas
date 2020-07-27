#Fix build break with glibc 2.28
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-pppd-Use-openssl-for-the-DES-instead-of-the-libcrypt.patch' if 'Buster' in '${MACHINE_FEATURES}' else ' '}"

#Need openssl for des.h
DEPENDS += "openssl"
do_compile_prepend() {
	if [ ! -f "${PKG_CONFIG_SYSROOT_DIR}/${includedir}/des.h" ] && [ -f "${PKG_CONFIG_SYSROOT_DIR}/${includedir}/openssl/des.h" ]
	then
		ln -s openssl/des.h "${PKG_CONFIG_SYSROOT_DIR}/${includedir}/des.h"
	fi
}
