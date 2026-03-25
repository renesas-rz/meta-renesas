DESCRIPTION = "RT Linux kernel from the Renesas RZ BSP based on linux-6.12.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.59-cip14"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip14-rt"
KERNEL_REV ?= "74fb6bf0be81f687d8a563cdf895b0f2d1a0684f"
