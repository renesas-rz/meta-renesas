require linux.inc
require linux-dtb.inc
require linux-dtb-append.inc
require linux-config.inc

DESCRIPTION = "Linux kernel for the R-Car Generation 2 based board"
COMPATIBLE_MACHINE = "(skrzg1e|skrzg1m|iwg20m|iwg22m)"

PV_append = "+git${SRCREV}"

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "d4f4b028e64d52e4e75939d2fb819a22dc178cbf"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=rvc/g1e-dev \
"


S = "${WORKDIR}/git"


SRC_URI_append_skrzg1m = " file://skrzg1m.cfg"

PATCHTOOL_rzg1 = "git"

KERNEL_DEFCONFIG = "shmobile_defconfig"

do_configure_prepend() {
    install -m 0644 ${S}/arch/${ARCH}/configs/${KERNEL_DEFCONFIG} ${WORKDIR}/defconfig || die "No default configuration for ${MACHINE} / ${KERNEL_DEFCONFIG} available."
}


do_configure_append() {

	configure_ext3
	configure_ext4
	configure_usb_storage
	configure_touchscreen
	configure_LVDS_panel
	configure_common

	yes '' | oe_runmake oldconfig
}

do_configure_append_skrzg1m() {

	configure_cma_skrzg1m

	yes '' | oe_runmake oldconfig
}

do_configure_append_iwg20m() {

	configure_cma_iwg20m
	configure_ravb
	configure_rcar_can
	configure_rcar_pwm

	kernel_configure_variable USB_U_ETHER n
	kernel_configure_variable USB_ETH m
	kernel_configure_variable RTC_DRV_BQ32K y
	kernel_configure_variable SND_SOC_SGTL5000 y
	kernel_configure_variable RENESAS_WDT y
	kernel_configure_variable VIDEO_TVP5150 y
	kernel_configure_variable USB_XHCI_HCD y
	kernel_configure_variable USB_XHCI_PCI y
	kernel_configure_variable USB_XHCI_PLATFORM y
	kernel_configure_variable USB_XHCI_RCAR y
	kernel_configure_variable_str EXTRA_FIRMWARE r8a779x_usb3_v1.dlmem
	kernel_configure_variable MEDIA_USB_SUPPORT y
	kernel_configure_variable MEDIA_CAMERA_SUPPORT y
	kernel_configure_variable USB_VIDEO_CLASS y
	kernel_configure_variable VIDEO_V4L2 y
	kernel_configure_variable USB_VIDEO_CLASS y
	kernel_configure_variable SOC_CAMERA_OV772X y
	kernel_configure_variable TOUCHSCREEN_EDT_FT5X06 y

# configure for USB OTG
	kernel_configure_variable USB_OHCI_LITTLE_ENDIAN y
	kernel_configure_variable USB_GADGETFS m
	kernel_configure_variable USB_LIBCOMPOSITE m
	kernel_configure_variable USB_MASS_STORAGE m
	kernel_configure_variable USB_F_MASS_STORAGE m
	kernel_configure_variable USB_EHCI_ROOT_HUB_TT y
	kernel_configure_variable USB_XHCI_HCD_DEBUGGING y
	kernel_configure_variable USB_OTG y
	kernel_configure_variable USB_ARCH_HAS_OHCI y
	kernel_configure_variable USB_ARCH_HAS_EHCI y
	kernel_configure_variable USB_ARCH_HAS_XHCI y

	yes '' | oe_runmake oldconfig
}


## for gles-kernel-module
do_compile_append() {
	cp ${KBUILD_OUTPUT}/vmlinux ${STAGING_KERNEL_BUILDDIR}/vmlinux

}
