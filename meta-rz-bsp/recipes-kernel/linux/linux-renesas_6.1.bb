DESCRIPTION = "Linux kernel from the Renesas RZ BSP based on linux-6.1.y-cip"

require recipes-kernel/linux/linux-yocto.inc
require linux-renesas_6.1.inc

LINUX_VERSION ?= "6.1.107-cip28"
KBUILD_DEFCONFIG ?= "defconfig"
KCONFIG_MODE ?= "alldefconfig"

KERNEL_URL ?= "git://github.com/renesas-rz/rz_linux-cip.git"

KERNEL_BRANCH ?= "rz-6.1-cip28"
KERNEL_REV ?= "b225337e5493e30aa39abc8c0705e8eecdba3b91"

SRC_URI:append = "${@bb.utils.contains('DISTRO_FEATURES','docker', ' file://docker.cfg', '', d)}"

# These patches are for reference only. They are preliminary.
SRC_URI:append = " \
	file://0001-gpu-drm-bridge-Add-ITE-it6263-LVDS-to-HDMI-bridge-dr.patch \
	file://0002-arm64-defconfig-enable-LVDS-and-IT6263-LVSD-to-HDMI-.patch \
	file://0003-arm64-dts-renesas-rzg3e-smarc-lvds-add-macro-to-sele.patch \
	file://0004-arm64-dts-renesas-r9a09g047e54-smarc-enable-LVDS-sup.patch \
"
