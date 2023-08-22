SECTION = "bootloaders"
SUMMARY = "Bptool from Trusted Firmware-A"
LICENSE = "BSD-3-Clause"

inherit native

require recipes-bsp/trusted-firmware-a/trusted-firmware-a.inc

do_configure () {
        sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/renesas/rz_boot_param/g3s/Makefile
        sed -i '/^INCLUDE_PATHS/ s,$, \$\{BUILD_CFLAGS},' ${S}/tools/renesas/rz_boot_param/g3s/Makefile
}

do_compile () {
	cd ${S}/tools/renesas/rz_boot_param/g3s
	oe_runmake bptool
}

do_install () {
	install -d ${D}${bindir}
	install ${S}/tools/renesas/rz_boot_param/g3s/bptool ${D}${bindir}
}
