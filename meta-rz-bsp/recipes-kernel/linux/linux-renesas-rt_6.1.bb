DESCRIPTION = "RT Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas_6.1.inc

LINUX_VERSION ?= "6.1.141-cip43-rt23"
LINUX_VERSION:rzg3e-family = "6.1.107-cip28-rt15"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"
KERNEL_BRANCH ?= "rz-6.1-cip43-rt23"
KERNEL_REV ?= "863c6a456dba9791a06d8c5c5d3ed65ec3fcc1f8"

KERNEL_BRANCH:rzg3e-family = "rz-6.1-cip28-rt15"
KERNEL_REV:rzg3e-family = "c02c397b2cc99e594e0d398364f2b82a4eaa6780"
