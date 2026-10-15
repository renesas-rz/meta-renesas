DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.12"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.59-cip14"
LINUX_VERSION:rzg3l-family = "6.12.46-cip8"
LINUX_VERSION:rzt2n-family = "6.12.63-cip15"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip14"
KERNEL_REV ?= "1fb07478288ad3bc054318258ea36d010026e363"
KERNEL_BRANCH:rzg3l-family = "rz-6.12-cip8"
KERNEL_REV:rzg3l-family = "e6c894b7436f14ba9ddda9e5807d3e19e9e2e803"
KERNEL_BRANCH:rzt2n-family = "rz-6.12-cip15"
KERNEL_REV:rzt2n-family = "07645517b75978253f061c722b30ca8c62583d5d"

SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
