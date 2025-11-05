SECTION = "bootloaders"
SUMMARY = "Parameter block generator from Trusted Firmware-A"
LICENSE = "BSD-3-Clause"

inherit native

LIC_FILES_CHKSUM = " \
	file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

URL = "git://github.com/renesas-rz/rzg_trusted-firmware-a.git"
SRCREV = "c5c5dfb1fccdc3eff928c4e21d158ebe163b9e64"
SRC_URI = "${URL};protocol=https;nobranch=1"

PV = "v2.10+git"

S = "${WORKDIR}/git"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install () {
	install -d ${D}${bindir}

	if [ -f ${S}/tools/renesas/rzt2h_boot_param/parameter_block_generator.py ]; then
		install -m 0755 ${S}/tools/renesas/rzt2h_boot_param/parameter_block_generator.py \
			${D}${bindir}/parameter-block-gen
	fi
}
