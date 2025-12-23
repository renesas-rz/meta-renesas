DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.12"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.59-cip14"
LINUX_VERSION:rzg3l-family = "6.12.46-cip8"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip14"
KERNEL_REV ?= "ecafe317091236136b9c71840cd2fb8f4538d9cc"
KERNEL_BRANCH:rzg3l-family = "rzg3l-6.12-cip8"
KERNEL_REV:rzg3l-family = "8287bbc97c8ed449ab24b0f18c118ab1cb569ea9"

SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
SRC_URI:append:rzg3l-family = " \
	${@bb.utils.contains('IMAGE_INSTALL', 'linux-firmware-bcm4373', 'file://bcm.cfg', '',d)} \
"
