DESCRIPTION = "RT Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas_6.1.inc

LINUX_VERSION ?= "6.1.141-cip43"
LINUX_VERSION:rzg3e-family = "6.1.107-cip28"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"
KERNEL_BRANCH ?= "rz-6.1-cip43-rt23"
KERNEL_REV ?= "ea863add447961c3916081723349dfd89465f64f"

KERNEL_BRANCH:rzg3e-family = "rz-6.1-cip28-rt15"
KERNEL_REV:rzg3e-family = "c02c397b2cc99e594e0d398364f2b82a4eaa6780"
