# base recipe: meta/recipes-support/libgcrypt/libgcrypt_1.8.4.bb
# base branch: warrior
# base commit: c8125e68c6160c5fad45fb64ac43f66924970ce9

SUMMARY = "General purpose cryptographic library based on the code from GnuPG"
HOMEPAGE = "http://directory.fsf.org/project/libgcrypt/"
BUGTRACKER = "https://bugs.g10code.com/gnupg/index"
SECTION = "libs"

# helper program gcryptrnd and getrandom are under GPL, rest LGPL
LICENSE = "GPLv2+ & LGPLv2.1+ & GPLv3+"
LICENSE_${PN} = "LGPLv2.1+"
LICENSE_${PN}-dev = "GPLv2+ & LGPLv2.1+"
LICENSE_dumpsexp-dev = "GPLv3+"

LIC_FILES_CHKSUM = "file://COPYING;md5=94d55d512a9ba36caa9b7df079bae19f \
                    file://COPYING.LIB;md5=bbb461211a33b134d42ed5ee802b37ff \
                    file://LICENSES;md5=840e3bcb754e5046ffeda7619034cbd8"

inherit debian-package-buster
require libgcrypt20.inc

DEPENDS = "libgpg-error"

FILESPATH_append = ":${COREBASE}/meta/recipes-support/libgcrypt/files:"
SRC_URI += " \
           file://0001-Add-and-use-pkg-config-for-libgcrypt-instead-of-conf.patch \
           file://0003-tests-bench-slope.c-workaround-ICE-failure-on-mips-w.patch \
           file://0002-libgcrypt-fix-building-error-with-O2-in-sysroot-path.patch \
           file://0004-tests-Makefile.am-fix-undefined-reference-to-pthread.patch \
           file://0001-Prefetch-GCM-look-up-tables.patch \
           file://0002-AES-move-look-up-tables-to-.data-section-and-unshare.patch \
           file://0003-GCM-move-look-up-table-to-.data-section-and-unshare-.patch \
"

BINCONFIG = "${bindir}/libgcrypt-config"

inherit autotools texinfo binconfig-disabled pkgconfig

EXTRA_OECONF = "--disable-asm"
EXTRA_OEMAKE_class-target = "LIBTOOLFLAGS='--tag=CC'"

PACKAGECONFIG ??= "capabilities"
PACKAGECONFIG[capabilities] = "--with-capabilities,--without-capabilities,libcap"

do_configure_prepend () {
	# Else this could be used in preference to the one in aclocal-copy
	rm -f ${S}/m4/gpg-error.m4
}

# libgcrypt.pc is added locally and thus installed here
do_install_append() {
	install -d ${D}/${libdir}/pkgconfig
	install -m 0644 ${B}/src/libgcrypt.pc ${D}/${libdir}/pkgconfig/
}

PACKAGES =+ "dumpsexp-dev"

FILES_${PN}-dev += "${bindir}/hmac256"
FILES_dumpsexp-dev += "${bindir}/dumpsexp"

BBCLASSEXTEND = "native nativesdk"
