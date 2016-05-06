require linux.inc
require linux-dtb.inc
require linux-dtb-append.inc
require ../../include/gles-control.inc
require ../../include/multimedia-control.inc

DESCRIPTION = "Linux kernel for the R-Car Generation 2 based board"
COMPATIBLE_MACHINE = "(skrzg1e|skrzg1m)"

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
"


SRC_URI_append = " \
    ${@' file://drm-rzg-du.cfg' \
    if '${USE_MULTIMEDIA}' == '0' or '${USE_GLES_WAYLAND}' == '0' else ''} \
"

SRC_URI_append_skrzg1m = " file://skrzg1m.cfg"

KERNEL_DEVICETREE_append_skrzg1m = '${@ \
	" ${S}/arch/arm/boot/dts/r8a7743-skrzg1m-eavb.dts " if 'skrzg1m-tse' in '${MACHINE_FEATURES}' else \
	""}'

PATCHTOOL_rzg1 = "git"

S = "${WORKDIR}/git"

KERNEL_DEFCONFIG = "shmobile_defconfig"

do_configure_prepend() {
    install -m 0644 ${S}/arch/${ARCH}/configs/${KERNEL_DEFCONFIG} ${WORKDIR}/defconfig || die "No default configuration for ${MACHINE} / ${KERNEL_DEFCONFIG} available."
}
