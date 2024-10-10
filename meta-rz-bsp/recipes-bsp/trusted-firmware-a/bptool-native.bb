SECTION = "bootloaders"
SUMMARY = "Bptool from Trusted Firmware-A"
LICENSE = "BSD-3-Clause"

inherit native

LIC_FILES_CHKSUM = " \
	file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

URL = "git://github.com/renesas-rz/rzg_trusted-firmware-a.git"
SRCREV = "2b0c18857eebc7a973f611500f6615e991e2625e"
SRC_URI = "${URL};protocol=https;nobranch=1"

PV = "v2.7+git"

S = "${WORKDIR}/git"

do_configure () {
        sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/renesas/rz_boot_param/Makefile
        sed -i '/^INCLUDE_PATHS/ s,$, \$\{BUILD_CFLAGS},' ${S}/tools/renesas/rz_boot_param/Makefile
}

EXTRA_OEMAKE = "DEST_OFFSET_ADR=0x08004000"

do_compile () {
	cd ${S}/tools/renesas/rz_boot_param
	oe_runmake bptool
}

do_install () {
	install -d ${D}${bindir}
	install ${S}/tools/renesas/rz_boot_param/bptool ${D}${bindir}
}
