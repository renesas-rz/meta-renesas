FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

LIC_FILES_CHKSUM = " \
        file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

SRC_URI = " \
	git://github.com/renesas-rz/rzg_trusted-firmware-a.git;nobranch=1;protocol=https \
"

SRCREV = "cca4398c9dfa3a375295630234367caccad5a285"

S = "${WORKDIR}/git"

PV = "v2.7+git"
