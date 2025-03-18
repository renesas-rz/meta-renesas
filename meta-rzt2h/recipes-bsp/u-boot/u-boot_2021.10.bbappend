SYSROOT_DIRS_append = " /boot"

UBOOT_URI ?= "git://github.com/renesas-rz/renesas-u-boot-cip.git;protocol=https"
UBOOT_BRANCH ?= "v2021.10/rzt2h"
UBOOT_REV ?= "0adf5cb2dbbe47d304f7276aa4000b1cc4575fe7"

SRC_URI = "${UBOOT_URI};branch=${UBOOT_BRANCH}"
SRCREV = "${UBOOT_REV}"
