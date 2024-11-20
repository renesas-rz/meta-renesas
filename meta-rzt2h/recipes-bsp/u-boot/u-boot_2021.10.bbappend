SYSROOT_DIRS_append = " /boot"

UBOOT_URI ?= "git://github.com/renesas-rz/renesas-u-boot-cip.git;protocol=https"
UBOOT_BRANCH ?= "v2021.10/rzt2h"
UBOOT_REV ?= "63a9aca0bf415575a9c75ce68b2fe3a0c0c16f34"

SRC_URI = "${UBOOT_URI};branch=${UBOOT_BRANCH}"
SRCREV = "${UBOOT_REV}"
