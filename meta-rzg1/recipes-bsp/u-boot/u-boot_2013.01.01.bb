require u-boot.inc

# This is needs to be validated among supported BSP's before we can
# make it default
DEFAULT_PREFERENCE = "-1"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb"

PV = "v2013.01.01+git${SRCREV}"

SRCREV = "fe16aa4fb779567d1b7da7c3cf22eaa9555fb483"
SRCREV_iwg23s = "8374e64a1265a580dd628ce9fa7948d7b9c26438"

SRC_URI = " \
    git://github.com/renesas-rz/renesas-u-boot-cip.git;branch=2013.01.01/rzg1-iwave;protocol=git \
    file://0001-rzg1-Update-BSP_VERSION-to-Linux5.10.patch \
"

SRC_URI_iwg23s = " \
    git://github.com/renesas-rz/renesas-u-boot-cip.git;branch=2013.01.01/rzg1-iwave-g1c;protocol=git \
    file://0001-rzg1-iwg23s-Update-BSP_VERSION-to-Linux5.10.patch \
"

SRC_URI_append = " \
    file://0001-Fix-missing-compiler-gccX.h-for-GCC-8-and-above.patch \
"

S = "${WORKDIR}/git"

COMPATIBLE_MACHINE = "(iwg20m-g1m|iwg20m-g1n|iwg21m|iwg22m|iwg23s)"
