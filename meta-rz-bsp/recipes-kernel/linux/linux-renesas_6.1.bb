DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas_6.1.inc

LINUX_VERSION ?= "6.1.141-cip43"
LINUX_VERSION:rzg3e-family = "6.1.107-cip28"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"
KERNEL_BRANCH ?= "rz-6.1-cip43"
KERNEL_REV ?= "d8049723a5153164c6c08a6f950820a9fe014536"

KERNEL_BRANCH:rzg3e-family = "rz-6.1-cip28"
KERNEL_REV:rzg3e-family = "2a3b0840b41348bd98c6179fffa1a6707c1bacf6"

SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
