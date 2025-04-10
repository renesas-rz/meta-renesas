DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas_6.1.inc

LINUX_VERSION ?= "6.1.107-cip28"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "${@oe.utils.conditional('IS_RT_BSP', '1', 'rz-6.1-cip28-rt15', 'rz-6.1-cip28',d)}"
KERNEL_REV ?= "${@oe.utils.conditional('IS_RT_BSP', '1', '33264e760bd27ce56d0bb4a479dec7e1f2808630', '6a5b01367bb71ad228b19dc3743081e744487a92',d)}"

SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
