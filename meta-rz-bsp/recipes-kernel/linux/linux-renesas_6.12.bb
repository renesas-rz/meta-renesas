DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.12"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.12.43-cip7"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip7"
KERNEL_REV ?= "03d16609f9f970a5c1af057dff88d475a26328fc"
SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
