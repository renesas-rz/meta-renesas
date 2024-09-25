SYSROOT_DIRS_append = " /boot"

UBOOT_URI ?= "git://github.com/renesas-rz/renesas-u-boot-cip.git;protocol=https"
UBOOT_BRANCH ?= "v2021.10/rzt2h"
UBOOT_REV ?= "b052bffc69eebfb1b68b42b04178dad09a95da2c"

SRC_URI = "${UBOOT_URI};branch=${UBOOT_BRANCH}"
SRCREV = "${UBOOT_REV}"
