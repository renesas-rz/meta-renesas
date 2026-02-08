DESCRIPTION = "RT Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.1.157-cip48-rt26"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"
KERNEL_BRANCH ?= "rz-6.1-cip48-rt26"
KERNEL_REV ?= "b93bb30ce47ba33ce4ede69984b8cf004a7d0bcd"
