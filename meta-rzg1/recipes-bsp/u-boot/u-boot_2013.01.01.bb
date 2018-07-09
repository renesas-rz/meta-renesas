require u-boot.inc

# This is needs to be validated among supported BSP's before we can
# make it default
DEFAULT_PREFERENCE = "-1"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb"

PV = "v2013.01.01+git${SRCREV}"

SRCREV = "c89c6d5ea30c62fcf85e19e27c77c6e7ce26c42b"
SRC_URI = "git://github.com/renesas-rz/renesas-u-boot-cip.git;branch=2013.01.01/rzg1-iwave;protocol=git \
"

S = "${WORKDIR}/git"

COMPATIBLE_MACHINE = "(iwg20m|iwg21m|iwg22m)"
