require linux.inc
require linux-dtb.inc
require linux-dtb-append.inc
require ../../include/gles-control.inc
require ../../include/multimedia-control.inc

DESCRIPTION = "Linux kernel for the R-Car Generation 2 based board"
COMPATIBLE_MACHINE = "(skrzg1e|skrzg1m|iwg20m)"

PV_append = "+git${SRCREV}"

RENESAS_BACKPORTS_URL="git://git.kernel.org/pub/scm/linux/kernel/git/horms/renesas-backport.git"
SRCREV = "165e12ce2d7839e755debbec78dfa43b54345275"
SRC_URI = " \
	${RENESAS_BACKPORTS_URL};protocol=git;branch=bsp/v3.10.31-ltsi/rcar-gen2-1.9.7 \
"

SRC_URI_append = " \
	file://0001-add-support-of-r8a7743-and-r8a7745.patch \
	file://0002-add-can-to-r8a7743-DT.patch \
	file://0002-add-SKRZG1M-and-SKRZG1E.patch \
	file://0003-can-add-Renesas-R-Car-CAN-driver.patch \
	file://0006-can-rcar_can-support-all-input-clocks.patch \
	file://0007-can-rcar_can-document-device-tree-bindings.patch \
	file://0008-can-rcar_can-add-device-tree-support.patch \
	file://0011-i2c-busses-rcar-Workaround-arbitration-loss-error.patch \
	file://0012-gpu-rcar-du-add-RGB-connector.patch \
	file://0013-gpu-rcar-du-Set-interlace-to-false-by-default-for-r8.patch \
	file://0014-ARM-shmobile-defconfig-Enable-SCI-DMA-support.patch \
	file://0015-ARM-shmobile-defconfig-Enable-Bluetooth.patch \
	file://0016-ARM-shmobile-defconfig-Add-ATAG-DTB-compatibility.patch \
	file://0018-media-V4L-Add-mem2mem-ioctl-and-file-operation-helpe.patch \
	file://0019-add-drivers-for-r8a7743-and-r8a7745.patch \
	file://0020-add-r8a7743-can-pin-groups.patch \
    \
	file://ext/0004-drm-rcar-du-parse-dt-adv7511-i2c-address.patch \
	file://ext/0005-Fix-ADV7511-subchips-offsets.patch \
	file://ext/0006-usb-xhci-rcar-Change-RCar-Gen2-usb3-firmware-to-upstream-name.patch \
	file://ext/0007-xhci-rcar-add-firmware-for-R-Car-H2-M2-USB-3.0-host-.patch \
	file://ext/0008-spi-sh-msiof-request-gpios-for-cs-gpios.patch \
	file://0027-add-ravb-compatible-for-r8a7743.patch \
	file://0028-added-avb-pins-for-r8a7743.patch \
	file://0029-added-avb-to-r8a7743.dtsi.patch \
	file://0030-created-avb-dts.patch \
	file://0031-r8a7743-Update-clock-and-pin-control-settings.patch \
	file://0035-audio-fix-non-audio-at-boot-up-randomly.patch \
	file://0036-Add-GPIO-button-for-RZG1M-Starter-Kit.patch \
	file://0039-Add-sysfs-for-pwm-from-kernel-v3.11.patch \
	file://0040-Fix-issue-limit-setting-value-lower-2s-of-period.patch \
	file://0041-Bluetooth-btusb-Add-Realtek-8723-8761-support.patch \
	file://0042-INTC-workaround.patch \
"


SRC_URI_append = " \
    ${@' file://drm-rzg-du.cfg' \
    if '${USE_MULTIMEDIA}' == '0' or '${USE_GLES_WAYLAND}' == '0' else ''} \
"

SRC_URI_append_skrzg1m = " file://skrzg1m.cfg"

SRC_URI_append_iwg20m = " \
	file://0032-iwg20m-Add-support-for-iWave-iwg20m-board.patch \
	file://0033-iwg20m-Fix-issue-HDMI-output-is-clone-from-LVDS.patch \
	file://0034-i2c-Revert-commit-Move-pm_runtime-to-fix-iWave-VIN2.patch \
	file://0037-USB2.0-OTG-Enable-USB2.0-OTG-Like-Connector-on-iWave.patch \
	file://0038-Fix-issue-ov7725-soc_cam.patch \
"


KERNEL_DEVICETREE_append_skrzg1m = '${@ \
	" ${S}/arch/arm/boot/dts/r8a7743-skrzg1m-eavb.dts " if 'skrzg1m-tse' in '${MACHINE_FEATURES}' else \
	""}'

PATCHTOOL_rzg1 = "git"

S = "${WORKDIR}/git"

KERNEL_DEFCONFIG = "shmobile_defconfig"
KERNEL_DEFCONFIG_iwg20m = "iw_rainbowg20m_defconfig"

do_configure_prepend() {
    install -m 0644 ${S}/arch/${ARCH}/configs/${KERNEL_DEFCONFIG} ${WORKDIR}/defconfig || die "No default configuration for ${MACHINE} / ${KERNEL_DEFCONFIG} available."
}

do_configure_append_skrzg1m() {
    kernel_configure_variable PWM=y  
 
    yes '' | oe_runmake oldconfig
}

do_configure_append_skrzg1e() {
    kernel_configure_variable PWM=y  
 
    yes '' | oe_runmake oldconfig
}

do_configure_append() {
    kernel_configure_variable PWM_SYSFS=y  
    kernel_configure_variable PWM_RENESAS_PWM=y
	kernel_configure_variable PWM_TIMER_SUPPORT=y  

# Enable bluetooth suport
    kernel_configure_variable   BT y
    kernel_configure_variable   BT_RFCOMM y
    kernel_configure_variable   BT_RFCOMM_TTY y
    kernel_configure_variable   BT_BNEP y
    kernel_configure_variable   BT_BNEP_MC_FILTER y
    kernel_configure_variable   BT_BNEP_PROTO_FILTER y
    kernel_configure_variable   BT_HIDP y
    kernel_configure_variable   BT_HCIBTUSB y
    kernel_configure_variable   BT_HCIBTSDIO y
    kernel_configure_variable   BT_HCIUART y
    kernel_configure_variable   BT_HCIUART_H4 y
    kernel_configure_variable   BT_HCIUART_BCSP y
    kernel_configure_variable   BT_HCIUART_ATH3K y
    kernel_configure_variable   BT_HCIUART_LL y
    kernel_configure_variable   BT_HCIUART_3WIRE y
    kernel_configure_variable   BT_HCIBCM203X y
    kernel_configure_variable   BT_HCIBPA10X y
    kernel_configure_variable   BT_HCIBFUSB y
    kernel_configure_variable   BT_HCIVHCI y
    kernel_configure_variable   BT_MRVL y
    kernel_configure_variable   BT_MRVL_SDIO y
    kernel_configure_variable   BT_ATH3K y

# Enable wifi suport
    kernel_configure_variable   CFG80211=y
    kernel_configure_variable   MAC80211=y
    kernel_configure_variable   MAC80211_MESH=y
    kernel_configure_variable   CFG80211_WEXT=y
    kernel_configure_variable   LIB80211=y
    kernel_configure_variable   LIB80211_CRYPT_WEP=y
    kernel_configure_variable   LIB80211_CRYPT_CCMP=y
    kernel_configure_variable   LIB80211_CRYPT_TKIP=y

    yes '' | oe_runmake oldconfig
}

# Different settings for PWM
SRC_URI_append_skrzg1m = " \
	file://skrzg1m/0001-Add-pwm-pinfc-setting-for-r8a7743-skrzg1m.patch \
	file://skrzg1m/0002-Add-pwm-support-on-device-tree-for-skrzg1m-board.patch \
"

SRC_URI_append_skrzg1e = " \
	file://skrzg1e/0001-Add-pwm-pinfc-setting-for-r8a7745-skrzg1e.patch \
	file://skrzg1e/0002-Add-pwm-support-on-device-tree-for-skrzg1e-board.patch \
"

SRC_URI_append_iwg20m = " \
	file://iWave/0001-Add-pwm-pin-function-controller-setting-for-r8a7743-.patch \
	file://iWave/0002-Add-pwm-support-on-device-tree-for-iWave-board.patch \
"
