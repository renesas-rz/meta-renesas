DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.12.9"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas_6.1.inc

LINUX_VERSION ?= "6.12.34"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.12-cip3"
KERNEL_REV ?= "fd5929f36c6609e1d6bd2bcbeaf0436ec1b19f3f"

#SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
