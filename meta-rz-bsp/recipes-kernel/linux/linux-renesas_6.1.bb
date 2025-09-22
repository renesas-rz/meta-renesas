DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.1.141-cip43"
LINUX_VERSION:rzg3e-family = "6.1.107-cip28"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"
KERNEL_BRANCH ?= "rz-6.1-cip43"
KERNEL_REV ?= "f12a03d8f2cf971734190c35aeaac98dde815b2d"

KERNEL_BRANCH:rzg3e-family = "rz-6.1-cip28"
KERNEL_REV:rzg3e-family = "2a3b0840b41348bd98c6179fffa1a6707c1bacf6"

KERNEL_BRANCH:rzv2n-family = "rzv2n-6.1-cip43"
KERNEL_REV:rzv2n-family = "dc9ee1801eda881de2a63084d347396d22ebae06"

# These patches are for reference only. They are preliminary.
SRC_URI:append:rzg3e-family = " \
	file://0001-gpu-drm-bridge-Add-ITE-it6263-LVDS-to-HDMI-bridge-dr.patch \
	file://0002-arm64-defconfig-enable-LVDS-and-IT6263-LVSD-to-HDMI-.patch \
	file://0003-arm64-dts-renesas-rzg3e-smarc-lvds-add-macro-to-sele.patch \
	file://0004-arm64-dts-renesas-r9a09g047e54-smarc-enable-LVDS-sup.patch \
	file://0005-gpu-drm-bridge-Support-S2R-ITE-it6263.patch \
"

SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"
