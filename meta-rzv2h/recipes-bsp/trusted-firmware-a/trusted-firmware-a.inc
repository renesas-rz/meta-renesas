FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

LIC_FILES_CHKSUM = " \
	file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

URL = "git://github.com/renesas-rz/rzg_trusted-firmware-a.git"
SRCREV = "bee53e1a5f2f009a1af320a871d8bac25ad09a5e"

PV = "v2.7+git"

S = "${WORKDIR}/git"

SRC_URI = "${URL};protocol=https;nobranch=1"
