DESCRIPTION = "RT Linux kernel from the Renesas RZ BSP based on linux-6.12.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.43-cip7"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip7-rt"
KERNEL_REV ?= "be1f7505aa30da8da520b0e2fd5320eadebd851b"
