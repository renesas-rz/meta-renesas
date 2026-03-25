DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.12"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.59-cip14"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip14"
KERNEL_REV ?= "bbdfd56496c1079c4abfa4f50bb0989ee63e7281"
SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
