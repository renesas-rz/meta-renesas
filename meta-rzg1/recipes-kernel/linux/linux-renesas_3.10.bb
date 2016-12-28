require linux.inc
require linux-dtb.inc
require linux-dtb-append.inc
require ../../include/gles-control.inc
require ../../include/multimedia-control.inc

DESCRIPTION = "Linux kernel for the R-Car Generation 2 based board"
COMPATIBLE_MACHINE = "(skrzg1e|skrzg1m|iwg20m|iwg21m)"

PV_append = "+git${SRCREV}"

RENESAS_BACKPORTS_URL="git://git.kernel.org/pub/scm/linux/kernel/git/horms/renesas-backport.git"
SRCREV = "34547b2a5032ce6dca24b745d608d2f3baac187f"
SRC_URI = " \
	${RENESAS_BACKPORTS_URL};protocol=git;branch=bsp/v3.10.31-ltsi/rcar-gen2-1.9.8 \
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
	file://0035_Fix_machine_compatible_SKRZG1E_and_SKRZG1M.patch\
	file://0042-INTC-workaround.patch \
"


SRC_URI_append = " \
    ${@' file://drm-rzg-du.cfg' \
    if '${USE_MULTIMEDIA}' == '0' or '${USE_GLES_WAYLAND}' == '0' else ''} \
"

SRC_URI_append_skrzg1m = " file://skrzg1m.cfg"

SRC_URI_append_iwg20m = "  \
    file://iwg20m/0001-RZ-G1-SoC-add-watchdog-driver.patch \
    file://iwg20m/0002-iwg20m-add-dts-defconfig-boar-info.patch \
    file://iwg20m/0003-iwg20m-update-spi-msiof.patch \
    file://iwg20m/0004-fix-r8a7743.dtsi-clock-issue.patch \
    file://iwg20m/0005-iwg20m-add-dtsi-for-g1m.patch \
    file://iwg20m/0006-iwg20m-g1n-add-dts.patch \
    file://iwg20m/0007-iwg20m-g1n-add-dtsi.patch \
    file://iwg20m/0008-rzg1-soc-add-firmware-for-usb3.0.patch \
    file://iwg20m/0009-fix-clk-for-i2c-and-change-name-usb3.0-fw.patch \
    file://iwg20m/0010-iwg20m-add-logo-image-and-update-logo-driver.patch \
    file://iwg20m/0011-iwg20m-fix-sgtl5000-driver-to-detect-mic-and-headpho.patch \
    file://iwg20m/0012-iwg20m-config-static-dev-mmc2-emmc-mmc1-usd-mmc0-sd.patch \
    file://iwg20m/0013-iwg20m-update-source-lvds-du-adv7511.patch \
    file://iwg20m/0014-iwg20m-add-driver-for-ov7725-cam.patch \
    file://iwg20m/0015-iwg20m-sata-led-driver-enable.patch \
    file://iwg20m/0016-iwg20m-update-touch-backlight-viddecoder.patch \
    file://iwg20m/0017-iwg20m-Fix-issue-HDMI-output-is-clone-from-LVDS.patch \
    file://iwg20m/0018-i2c-Revert-commit-Move-pm_runtime-to-fix-iWave-VIN2.patch \
    file://iwg20m/0019-iwg20m-update-file-board-info.patch \
    file://iwg20m/0020-add-ov5640-camera-driver.patch \
    file://iwg20m/0021-solve-conflict-ov5640-adv7511-i2c-cec-addr.patch \  
    file://iwg20m/0022-iwg20m-support-usb-otg.patch \
    file://iwg20m/0023-iwg20m-add-pwm-in-pfc-and-dts.patch \
    file://iwg20m/0024-Fix-issue-ov7725-soc_cam.patch \
"

SRC_URI_append_iwg21m = "  \
    file://iwg21m/0001-iwg21m-add-dts-defconfig-boar-info.patch \
    file://iwg21m/0002-iwg21m-add-ata-change.patch \
    file://iwg21m/0003-iwg21m-add-configure-compatible-for-clk-gen-rcar.patch \
    file://iwg21m/0003-rzg1-soc-add-firmware-for-usb3.0.patch \
    file://iwg21m/0004-iwg21m-add-machine-compatible-r8a7742-for-spi-sh-msiof.patch \
    file://iwg21m/0005-iwg21m-add-match-of-compatible-gpio-driver.patch \
    file://iwg21m/0006-iwg21m-add-match-of-compatible-gpu-driver.patch \
    file://iwg21m/0007-iwg21m-add-match-of-compatible-i2c-driver.patch \
    file://iwg21m/0008-iwg21m-add-match-of-compatible-touchscreen-driver.patch \
    file://iwg21m/0010-iwg21m-add-match-of-compatible-media-driver.patch \
    file://iwg21m/0011-iwg21m-add-match-of-compatible-mmc-driver.patch \
    file://iwg21m/0012-iwg21m-add-match-of-compatible-can-ethernet-driver.patch \
    file://iwg21m/0013-iwg21m-add-match-of-compatible-pci-phy-driver.patch \
    file://iwg21m/0014-iwg21m-add-match-of-compatible-pinctrl-driver.patch \
    file://iwg21m/0015-iwg21m-add-match-of-compatible-pwm-sh-spi-driver.patch \
    file://iwg21m/0016-iwg21m-add-match-of-compatible-usb-driver.patch \
    file://iwg21m/0017-iwg21m-add-match-of-compatible-video-logo.patch \
    file://iwg21m/0018-iwg21m-add-match-of-compatible-watchdog-driver.patch \
    file://iwg21m/0019-iwg21m-add-match-of-compatible-header-files.patch \
"

KERNEL_DEVICETREE_append_skrzg1m = '${@ \
	" ${S}/arch/arm/boot/dts/r8a7743-skrzg1m-eavb.dts " if 'skrzg1m-tse' in '${MACHINE_FEATURES}' else \
	""}'

PATCHTOOL_rzg1 = "git"

S = "${WORKDIR}/git"

KERNEL_DEFCONFIG = "shmobile_defconfig"
KERNEL_DEFCONFIG_iwg20m = "iwg20m_defconfig"
KERNEL_DEFCONFIG_iwg21m = "iwg21m_defconfig"

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

