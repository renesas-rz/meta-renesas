DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.12"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.59-cip14"
LINUX_VERSION:rzg3l-family = "6.12.46-cip8"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip14"
KERNEL_REV ?= "c288c58870b1b5701181f11ae741d829a1506cf6"
KERNEL_BRANCH:rzg3l-family = "rz-6.12-cip8"
KERNEL_REV:rzg3l-family = "e6c894b7436f14ba9ddda9e5807d3e19e9e2e803"

SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
