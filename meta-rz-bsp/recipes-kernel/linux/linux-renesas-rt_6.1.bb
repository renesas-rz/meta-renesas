DESCRIPTION = "RT Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas.inc

LINUX_VERSION ?= "6.1.157-cip48-rt26"

KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"
KERNEL_BRANCH ?= "rz-6.1-cip48-rt26"
KERNEL_REV ?= "1119683a25954e637478b99c2e6a8d97da156a59"

# These patches are for reference only. They are preliminary.
SRC_URI:append = " \
	file://v6.1/display/0001-drm-bridge-adv7511-Clear-HPD-IRQ-before-powering-on-.patch \
	file://v6.1/display/0002-gpu-drm-bridge-Add-ITE-it6263-LVDS-to-HDMI-bridge-dr.patch \
	file://v6.1/display/0003-arm64-defconfig-enable-LVDS-and-IT6263-LVSD-to-HDMI-.patch \
	file://v6.1/display/0004-arm64-dts-renesas-rzg3e-smarc-lvds-add-macro-to-sele.patch \
	file://v6.1/display/0005-arm64-dts-renesas-r9a09g047e57-smarc-enable-LVDS-sup.patch \
	file://v6.1/display/0006-gpu-drm-bridge-Support-S2R-ITE-it6263.patch \
	file://v6.1/display/0007-drm-bridge-ite-it6263-Support-VESA-24-input-format.patch \
"
