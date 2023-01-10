SECTION = "bootloaders"
SUMMARY = "Fiptool from Trusted Firmware-A"
LICENSE = "MIT"

inherit native

DEPENDS = "openssl-native"

S = "${WORKDIR}/git"

do_configure () {
	sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/fiptool/Makefile
	sed -i '/^INCLUDE_PATHS/ s,$, \$\{BUILD_CFLAGS},' ${S}/tools/fiptool/Makefile
	sed -i 's^OPENSSL_DIR.*=.*$^OPENSSL_DIR = ${STAGING_DIR_NATIVE}/${prefix_native}^' ${S}/tools/fiptool/Makefile
}

do_compile () {
	oe_runmake fiptool
}

do_install () {
    install -d ${D}${bindir}
    install ${S}/tools/fiptool/fiptool ${D}${bindir}
}
