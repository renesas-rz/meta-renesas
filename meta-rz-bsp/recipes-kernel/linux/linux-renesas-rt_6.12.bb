DESCRIPTION = "RT Linux kernel from the Renesas RZ BSP based on linux-6.12.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.59-cip14"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip14-rt"
KERNEL_REV ?= "5d0b4ecb2488d4cdca29c76a3be3cc40b18b6229"
