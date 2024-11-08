DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas_6.1.inc

LINUX_VERSION ?= "6.1.107-cip28"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"
KERNEL_BRANCH = "rz-6.1-cip28"
KERNEL_REV ?= "45c953944500afc055b055a937d8ecc741c81cba"

SRC_URI:append = "${@oe.utils.conditional('IS_DOCKER_ENABLED', '1', ' file://docker.cfg', '', d)}"
