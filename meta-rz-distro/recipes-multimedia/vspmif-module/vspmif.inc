LICENSE = "MIT"
LIC_FILES_CHKSUM = " \
    file://COPYING.MIT;md5=30a99e0d36a3da1f5cf93c070ad7888a \
"

require include/rz-distro-common.inc

VSPMIF_LIB_URL = "git://github.com/renesas-rz/vspmif_lib"
BRANCH = "main"
SRCREV = "e50531758a672f7454feb76733343afdfbabe9bc"

SRC_URI = "${VSPMIF_LIB_URL};branch=${BRANCH};protocol=https"

# This module is machine specific.
PACKAGE_ARCH = "${MACHINE_ARCH}"
