FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

LIC_FILES_CHKSUM = " \
	file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

URL = "git://github.com/renesas-rz/rzg_trusted-firmware-a.git"
SRCREV = "ac42ae2d33a0770c5ee160ab1b2fe263e67bd680"

PV = "v2.7+git"

S = "${WORKDIR}/git"

SRC_URI = " \
	${URL};protocol=https;nobranch=1 \
"
