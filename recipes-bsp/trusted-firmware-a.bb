LIC_FILES_CHKSUM = "file://docs/license.rst;md5=189505435dbcdcc8caa63c46fe93fa89"

require trusted-firmware-a.inc

URL = "git://git@github.com/renesas-rz/rzg_trusted-firmware-a.git"
BRANCH = "v2.3/rzg2l"
SRCREV = "baee1ff9a7ab159453776930bc5fa36ba5f05b7b"

SRC_URI += "${URL};protocol=ssh;branch=${BRANCH}"

PV = "2.3-rzg+git${SRCPV}"
PR = "r1"
