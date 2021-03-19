LIC_FILES_CHKSUM = "file://docs/license.rst;md5=189505435dbcdcc8caa63c46fe93fa89"

require fiptool-native.inc

URL = "git://git@github.com/renesas-rz/rzg_trusted-firmware-a_private.git"
BRANCH = "develop/202102"
SRCREV = "159d412210a612f968447fe7ffbefce26550bd54"

SRC_URI = "${URL};protocol=ssh;branch=${BRANCH}"

PV = "2.3-rzg+git${SRCPV}"
PR = "r1"
