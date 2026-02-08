DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.1.157-cip48"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"
KERNEL_BRANCH ?= "rz-6.1-cip48"
KERNEL_REV ?= "fe13c5ea06a33aaeb0a297893e151b13f95109fe"

SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
