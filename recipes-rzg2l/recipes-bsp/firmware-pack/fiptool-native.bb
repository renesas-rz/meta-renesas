LIC_FILES_CHKSUM = "file://docs/license.rst;md5=713afe122abbe07f067f939ca3c480c5"

require fiptool-native.inc

URL = "git://git@github.com/renesas-rz/rzg_trusted-firmware-a.git"
BRANCH = "v2.5/rzg2l"
SRCREV = "1939ffd728e1af90fd76b083ee471feef9128db6"

SRC_URI = "${URL};protocol=ssh;branch=${BRANCH}"

PV = "2.5-rzg+git${SRCPV}"
PR = "r1"
