LIC_FILES_CHKSUM = "file://docs/license.rst;md5=189505435dbcdcc8caa63c46fe93fa89"

require fiptool-native.inc

URL = "git://git@gitlab.renesas.solutions/spl2/civil-infrastructure-platform/rz-g2l-trusted-firmware-a.git"
BRANCH = "master"
SRCREV = "5d12dd135b69239f4128a5ab87652dc602fcafd9"

SRC_URI = "${URL};protocol=ssh;branch=${BRANCH}"

PV = "2.3-spl2+git${SRCPV}"
PR = "r1"
