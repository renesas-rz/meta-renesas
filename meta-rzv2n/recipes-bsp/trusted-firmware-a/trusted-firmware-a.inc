FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

LIC_FILES_CHKSUM = " \
	file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

URL = "git://github.com/renesas-rz/rzg_trusted-firmware-a.git"
SRCREV = "5d4e48ee41576c63561b0b3cc6bf7aa0136c7b78"

PV = "v2.7+git"

S = "${WORKDIR}/git"

SRC_URI = " \
	${URL};protocol=https;nobranch=1 \
"
