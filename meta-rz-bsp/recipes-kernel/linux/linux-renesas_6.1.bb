DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas_6.1.inc

LINUX_VERSION ?= "6.1.107-cip28"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URI ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "${@oe.utils.conditional('IS_RT_BSP', '1', 'rz-6.1-cip28-rt15', 'rz-6.1-cip28',d)}"
KERNEL_REV ?= "${@oe.utils.conditional('IS_RT_BSP', '1', 'c7ad553460a647a6140c632535c9dd53756245d0', 'ae4158ad47cf45d140caf4a32d4d825e37e4849d',d)}"

SRC_URI:append = "${@oe.utils.conditional('IS_DOCKER_ENABLED', '1', ' file://docker.cfg', '', d)}"
