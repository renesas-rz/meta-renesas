require linux.inc
require linux-dtb.inc
require linux-dtb-append.inc
require linux-config.inc

DESCRIPTION = "Linux kernel for the R-Car Generation 2 based board"
COMPATIBLE_MACHINE = "(skrzg1e|skrzg1m)"

PV_append = "+git${SRCREV}"

RENESAS_URL="git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git"
SRCREV = "0d1912303e54ed1b2a371be0bba51c384dd57326"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=linux-4.4.y \
	file://ARM-dts-porter-fix-bootargs.patch \
	file://ARM-dts-silk-fix-bootargs.patch \
	file://i2c-rcar-make-sure-clocks-are-on-when-doing-clock-calculation.patch \
	file://i2c-rcar-rework-hw-init.patch \
	file://i2c-rcar-remove-unused-IOERROR-state.patch \
	file://i2c-rcar-remove-spinlock.patch \
	file://i2c-rcar-refactor-setup-of-a-msg.patch \
	file://i2c-rcar-init-new-messages-in-irq.patch \
	file://i2c-rcar-don-t-issue-stop-when-HW-does-it-automatically.patch \
	file://i2c-rcar-check-master-irqs-before-slave-irqs.patch \
	file://i2c-rcar-revoke-START-request-early.patch \
	file://pinctrl-sh-pfc-r8a7794-fix-GP2-29-muxing.patch \
	file://pinctrl-sh-pfc-only-use-dummy-states-for-non-DT-platforms.patch \
	file://ARM-dts-r8a7794-Reference-both-DMA-controllers-in-SDHI-nodes.patch \
	file://ARM-shmobile-porter-add-HS-USB-DT-support.patch \
	file://ARM-dts-porter-remove-enable-prop-from-HS-USB-device-node.patch \
	file://ARM-shmobile-porter-add-CAN0-DT-support.patch \
	file://ARM-dts-porter-add-DU-DT-support.patch \
	file://ARM-dts-porter-add-sound-support.patch \
	file://ARM-shmobile-silk-add-SDHI1-DT-support.patch \
	file://ARM-shmobile-r8a7794-Add-DU0-clock.patch \
	file://ARM-shmobile-r8a7794-Add-DU-node-to-device-tree.patch \
	file://ARM-dts-silk-add-DU-DT-support.patch \
	file://pinctrl-sh-pfc-r8a7794-Add-SSI-pin-groups.patch \
	file://pinctrl-sh-pfc-r8a7794-Add-audio-clock-pin-groups.patch \
	file://ARM-dts-r8a7794-add-audio-clocks.patch \
	file://ARM-dts-r8a7794-add-MSTP5-clocks-v2.patch \
	file://ARM-dts-r8a7794-add-MSTP10-clocks-v2.patch \
	file://ARM-dts-r8a7794-add-Audio-DMAC-support.patch \
	file://ARM-dts-r8a7794-add-sound-support-v2.patch \
	file://ARM-dts-silk-add-sound-support.patch \
	file://0001-add-pormat-for-mem2mem-playback.patch \
	file://0002-port-upstream-sysc-driver.patch \
	file://0003-add-DT-smp-support.patch \
	file://0004-add-sysc-support-for-r8a7743-and-r8a7745.patch \
	file://0005-move-serial-console-to-sc10.patch \
	file://0006-add-da9063-support.patch \
	file://0007-add-r8a7743-SoC.patch \
	file://0008-add-skrzg1m-dts.patch \
	file://0009-change-da9063-I2C-address.patch \
	file://0010-switch-of-usbhs-ip-block.patch \
	file://0011-use-preffered-log-methods.patch \
	file://0012-rejoin-broken-lines.patch \
	file://0013-r8a7794-move-serial-console-to-sc10.patch \
	file://0014-ARM-dts-r8a7794-add-IIC-clocks.patch \
	file://0015-ARM-dts-r8a7794-Add-IIC-nodes.patch \
	file://0016-add-smp-and-sysc-to-r8a7794.patch \
	file://0017-add-r8a7794-quirk-for-sgx-clock.patch \
	file://0018-add-sgx-to-r8a7794-dtsi.patch \
	file://0019-add-gpio-keys-and-da9063-pmic.patch \
	file://0020-add-r8a7745-SoC.patch \
	file://0021-add-skrzg1e-dts.patch \
	file://0022-pinctrl-sh-pfc-r8a7745-add-EtherAVB-and-DU-pin-group.patch \
	file://0023-skrzg1e-enable-PFC-DU.patch \
	file://0024-drm-rcar-du-Output-the-DISP-signal-on-the-DISP-pin.patch \
	file://0025-fix-z-and-z2-clk-for-r8a7793-and-r8a7794.patch \
	file://0026-app-operation-points-for-cpufreq-working.patch \
	file://0027-add-for-clk-driver-RZG-support.patch \
	file://0028-media-media-adv7180-increase-delay-after-reset-to-5m.patch \
	file://0029-add-gpio-keys-to-skrzg1m.patch \
	file://0030-edit-defconfig-to-support-cma.patch \
	file://0031-r8a7743.dtsi-register-for-2ddmac-change-the-compatib.patch \
	file://0032-Add-FDPM-into-device-tree-of-RZG1M.patch \
	file://0033-linux-renesas-r8a7743-dtsi-add-vcp0-vpc0-prr-vpc1-vp.patch \
	file://0034-linux-renesas-r8a7745-dtsi-add-vcp0-vpc0-prr-vpc1-vp.patch \
"


S = "${WORKDIR}/git"


SRC_URI_append_skrzg1m = " file://skrzg1m.cfg"

PATCHTOOL_rzg1 = "git"

KERNEL_DEFCONFIG = "shmobile_defconfig"

do_configure_prepend() {
    install -m 0644 ${S}/arch/${ARCH}/configs/${KERNEL_DEFCONFIG} ${WORKDIR}/defconfig || die "No default configuration for ${MACHINE} / ${KERNEL_DEFCONFIG} available."
}


do_configure_append() {
	
	connfigure_ext3
	connfigure_ext4
	configure_usb_storage
	connfigure_touchscreen
	configure_common

	yes '' | oe_runmake oldconfig
}


## for gles-kernel-module
do_compile_append() {
	cp ${KBUILD_OUTPUT}/vmlinux ${STAGING_KERNEL_BUILDDIR}/vmlinux

}

