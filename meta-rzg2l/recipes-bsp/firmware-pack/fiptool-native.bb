LIC_FILES_CHKSUM = "file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"

require fiptool-native.inc

URL = "git://github.com/renesas-rz/rzg_trusted-firmware-a.git"
BRANCH = "v2.6/rz"
SRCREV = "aed3786384b99dc13a46a8d3af139df28b5642a3"

SRC_URI = "${URL};protocol=https;branch=${BRANCH}"

PV = "2.6+git${SRCPV}"
PR = "r1"
