DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.12"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.43-cip7"
LINUX_VERSION:rzg3l-family = "6.12.46-cip8"

PV = "${LINUX_VERSION}+git"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip7"
KERNEL_REV ?= "03d16609f9f970a5c1af057dff88d475a26328fc"

KERNEL_BRANCH:rzg3l-family = "rzg3l-6.12-cip8"
KERNEL_REV:rzg3l-family = "5d171f88f035ad2066008e9b8c41c6b45076e153"

SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
SRC_URI:append:rzg3l-family = " \
	${@bb.utils.contains('IMAGE_INSTALL', 'linux-firmware-bcm4373', 'file://bcm.cfg', '',d)} \
"
