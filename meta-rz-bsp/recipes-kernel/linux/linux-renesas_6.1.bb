DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas_6.1.inc

LINUX_VERSION ?= "6.1.107-cip28"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "${@oe.utils.conditional('IS_RT_BSP', '1', 'rz-6.1-cip28-rt15', 'rz-6.1-cip28',d)}"
KERNEL_REV ?= "${@oe.utils.conditional('IS_RT_BSP', '1', '548939de3e9bcf276aa5f57b9e94ad0d1cd02a3e', '01ee5bf965402940a930fc08af9e54ad204b8259',d)}"

SRC_URI:append = "${@oe.utils.conditional('IS_DOCKER_ENABLED', '1', ' file://docker.cfg', '', d)}"
