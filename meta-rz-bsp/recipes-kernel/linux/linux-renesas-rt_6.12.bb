DESCRIPTION = "RT Linux kernel from the Renesas RZ BSP based on linux-6.12.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.59-cip14"
LINUX_VERSION:rzt2n-family= "6.12.63-cip15"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip14-rt"
KERNEL_REV ?= "197e2b7ac8885618d0db4489e86392040f794987"
KERNEL_BRANCH:rzt2n-family= "rz-6.12-cip15-rt"
KERNEL_REV:rzt2n-family= "9a045a3457e7421be6cbf61a837bf5b099104401"
