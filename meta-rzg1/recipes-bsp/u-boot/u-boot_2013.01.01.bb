require u-boot.inc

# This is needs to be validated among supported BSP's before we can
# make it default
DEFAULT_PREFERENCE = "-1"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb"

PV = "v2013.01.01+git${SRCREV}"

SRCREV = "b74f925bbca6de64f27443e8d25d5d689edae99e"
SRC_URI = "git://github.com/renesas-rz/renesas-u-boot-cip.git;branch=2013.01.01/rzg1-iwave;protocol=git \
           file://0001-Enable-checking-PARTUUID-and-allow-booting-by-PARTUU.patch \
           file://0002-Add-alternative-default-name-for-iwg20m-board-dtb.patch \
           file://0001-u-boot-Add-iwg22m-support.patch \
           file://0001-u-boot-Add-iwg23s-support.patch \
           file://0002-u-boot-iwg23s-Add-QoS-support.patch \
           file://0001-u-boot-fix-sd-boot-issue-on-G1N.patch \
"

S = "${WORKDIR}/git"

COMPATIBLE_MACHINE = "(iwg20m|iwg22m|iwg23s|iwg21m)"
