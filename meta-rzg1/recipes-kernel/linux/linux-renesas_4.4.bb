require linux.inc
require linux-dtb.inc
require linux-dtb-append.inc
require linux-config.inc

DESCRIPTION = "Linux kernel for the R-Car Generation 2 based board"
COMPATIBLE_MACHINE = "(skrzg1e|skrzg1m|iwg20m)"

PV_append = "+git${SRCREV}"

RENESAS_URL="git://git.kernel.org/pub/scm/linux/kernel/git/bwh/linux-cip.git"
SRCREV = "a09e49b41e1bb15e0ec04a8a3b92728de7310c96"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=linux-4.4.y-cip \
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
	file://0030-revert-gpio-rcar-fine-grained-runtime-pm-support.patch \
	file://0030-edit-defconfig-to-support-cma.patch \
	file://0031-r8a7743.dtsi-register-for-2ddmac-change-the-compatib.patch \
	file://0032-Add-FDPM-into-device-tree-of-RZG1M.patch \
	file://0033-linux-renesas-r8a7743-dtsi-add-vcp0-vpc0-prr-vpc1-vp.patch \
	file://0034-linux-renesas-r8a7745-dtsi-add-vcp0-vpc0-prr-vpc1-vp.patch \
	file://0035-r8a7745.dtsi-register-for-2ddmac-vsp1-vspd0.patch \
	file://0036-Add-FDPM-into-device-tree-of-RZG1E.patch \
	file://0037-ARM-dts-r8a7743-multimedia-ip-blocks-use-sysc-power-domain.patch \
	file://0038-ARM-dts-r8a7745-multimedia-ip-blocks-use-sysc-power-domain.patch \
	file://0039-VSPM-modify-device-tree-for-adapting-with-VSPM-update.patch \
	file://vin/0032-adv7180-Add-g_std-operation.patch \
	file://vin/0033-adv7180-Add-cropcap-operation.patch \
	file://vin/0034-adv7180-Add-g_tvnorms-operation.patch \
	file://vin/0035-adv7180-fix-broken-standards-handling.patch \
	file://vin/0036-set-crop-bounds.patch \
	file://vin/0037-Check-width-align.patch \
	file://vin/0038-Fix-pre-clipping-size.patch \
	file://vin/0039-add-g_crop-for-adv7180.patch \
	file://vin/0040-Add-CROPCAP-ioctl.patch \
	file://0041-Fix-adv7511-drm-driver.patch \
	file://0042-enable-cmt0.patch \
	file://vsp/0001-v4l-vsp1-Change-the-type-of-the-rwpf-field-in-struct.patch \
	file://vsp/0002-v4l-vsp1-Store-the-memory-format-in-struct-vsp1_rwpf.patch \
	file://vsp/0003-v4l-vsp1-Move-video-operations-to-vsp1_rwpf.patch \
	file://vsp/0004-v4l-vsp1-Rename-vsp1_video_buffer-to-vsp1_vb2_buffer.patch \
	file://vsp/0005-v4l-vsp1-Move-video-device-out-of-struct-vsp1_rwpf.patch \
	file://vsp/0006-v4l-vsp1-Make-rwpf-operations-independent-of-video-d.patch \
	file://vsp/0007-v4l-vsp1-Support-VSP1-instances-without-any-UDS.patch \
	file://vsp/0008-v4l-vsp1-Move-vsp1_video-pointer-from-vsp1_entity-to.patch \
	file://vsp/0009-v4l-vsp1-Remove-struct-vsp1_pipeline-num_video-field.patch \
	file://vsp/0010-v4l-vsp1-Decouple-pipeline-end-of-frame-processing-f.patch \
	file://vsp/0011-v4l-vsp1-Split-pipeline-management-code-from-vsp1_vi.patch \
	file://vsp/0012-v4l-vsp1-Rename-video-pipeline-functions-to-use-vsp1.patch \
	file://vsp/0013-v4l-vsp1-Extract-pipeline-initialization-code-into-a.patch \
	file://vsp/0014-v4l-vsp1-Reuse-local-variable-instead-of-recomputing.patch \
	file://vsp/0015-v4l-vsp1-Extract-link-creation-to-separate-function.patch \
	file://vsp/0016-v4l-vsp1-Document-the-vsp1_pipeline-structure.patch \
	file://vsp/0017-v4l-vsp1-Fix-typo-in-VI6_DISP_IRQ_STA_DST-register-b.patch \
	file://vsp/0018-v4l-vsp1-Set-the-SRU-CTRL0-register-when-starting-th.patch \
	file://vsp/0019-v4l-vsp1-Remove-unused-module-read-functions.patch \
	file://vsp/0020-v4l-vsp1-Move-entity-route-setup-function-to-vsp1_en.patch \
	file://vsp/0021-v4l-vsp1-Make-number-of-BRU-inputs-configurable.patch \
	file://vsp/0022-v4l-vsp1-Make-the-BRU-optional.patch \
	file://vsp/0023-v4l-vsp1-Move-format-info-to-vsp1_pipe.c.patch \
	file://vsp/0024-v4l-vsp1-Make-the-userspace-API-optional.patch \
	file://vsp/0025-v4l-vsp1-Make-pipeline-inputs-array-index-by-RPF-ind.patch \
	file://vsp/0026-v4l-vsp1-Set-the-alpha-value-manually-in-RPF-and-WPF.patch \
	file://vsp/0027-v4l-vsp1-Don-t-validate-links-when-the-userspace-API.patch \
	file://vsp/0028-v4l-vsp1-Add-VSP-DU-support.patch \
	file://vsp/0029-v4l-vsp1-Disconnect-unused-RPFs-from-the-DRM-pipelin.patch \
	file://vsp/0030-v4l-vsp1-Implement-atomic-update-for-the-DRM-driver.patch \
	file://vsp/0031-v4l-vsp1-Add-support-for-the-R-Car-Gen3-VSP2.patch \
	file://vsp/0032-v4l-vsp1-Add-display-list-support.patch \
	file://vsp/0033-v4l-vsp1-Configure-device-based-on-IP-version.patch \
	file://vsp/0034-drm-Pass-the-user-drm_mode_fb_cmd2-as-const-to-.fb_c.patch \
	file://vsp/0035-drm-Pass-name-to-drm_crtc_init_with_planes.patch \
	file://vsp/0036-drm-Pass-name-to-drm_universal_plane_init.patch \
	file://vsp/0037-drm-Pass-name-to-drm_encoder_init.patch \
	file://vsp/0038-drm-Constify-drm_encoder_slave_funcs.patch \
	file://vsp/0039-drm-rcar-du-Perform-initialization-cleanup-at-probe-.patch \
	file://vsp/0040-drm-rcar-du-Add-default-modes-to-VGA-connector.patch \
	file://vsp/0041-drm-rcar-du-Don-t-update-planes-on-disabled-CRTCs.patch \
	file://vsp/0042-drm-rcar-du-Compute-plane-DDCR4-register-value-direc.patch \
	file://vsp/0043-drm-rcar-du-Refactor-plane-setup.patch \
	file://vsp/0044-drm-rcar-du-Add-VSP1-support-to-the-planes-allocator.patch \
	file://vsp/0045-drm-rcar-du-Add-VSP1-compositor-support.patch \
	file://vsp/0046-drm-rcar-du-Restart-the-DU-group-when-a-plane-source.patch \
	file://vsp/0047-drm-rcar-du-Move-plane-allocator-to-rcar_du_plane.c.patch \
	file://vsp/0048-drm-rcar-du-Expose-the-VSP1-compositor-through-KMS-p.patch \
	file://vsp/0049-drm-rcar-du-Use-the-VSP-atomic-update-API.patch \
	file://vsp/0050-drm-rcar-du-Fix-compile-warning-on-64-bit-platforms.patch \
	file://vsp/0051-drm-rcar-du-Enable-compilation-on-ARM64.patch \
	file://vsp/0052-drm-rcar-du-Drop-LVDS-double-dependency-on-OF.patch \
	file://vsp/0053-drm-rcar-du-Support-up-to-4-CRTCs.patch \
	file://vsp/0054-drm-rcar-du-Output-the-DISP-signal-on-the-ODDF-pin.patch \
	file://vsp/0055-drm-rcar-du-Add-R8A7795-device-support.patch \
	file://vsp/0056-drm-rcar-du-lvds-Avoid-duplication-of-clock-clamp-co.patch \
	file://vsp/0057-drm-rcar-du-lvds-Fix-PLL-frequency-related-configura.patch \
	file://vsp/0058-drm-rcar-du-lvds-Rename-PLLEN-bit-to-PLLON.patch \
	file://vsp/0059-drm-rcar-du-Add-probe-deferral-debug-messages.patch \
	file://vsp/0060-drm-rcar-du-lvds-Add-R-Car-Gen3-support.patch \
	file://vsp/0061-media-v4l-vsp1-Fix-descriptions-of-Gen2-VSP-instance.patch \
	file://vsp/0062-Revert-drm-rcar-du-Output-the-DISP-signal-on-the-ODD.patch \
	file://vsp/0063-drm-rcar-du-r8a7743-support-control-vsp-by-DU.patch \
	file://vsp/0064-v4l-vsp1-Don-t-register-media-device.patch \
	file://0043-Fix-warn-message.patch \
	file://0044-add-drm-panel-support.patch \
	file://0045-add-hann-start-panel.patch \
	file://0046-ARM-dts-skrzg1m-remove-x16-clocks.patch \
	file://vsp/0065-rcar-du-add-vspd-number.patch \
	file://vsp/0066-rcar-du-store-rcar_du_group-for-vsp_device.patch \
	file://vsp/0067-rcar-du-call-vsp-methods-only-if-device-is-present.patch \
	file://vsp/0068-rcar-du-update-planes-which-don-t-have-vsp-device.patch \
	file://vsp/0069-ARM-dts-r8a7745-support-vspdu.patch \
	file://vsp/0070-drm-rcar-du-enable-rendering-througth-vsp-device.patch \
	file://ARM-shmobile-timer-Fix-preset_lpj-leading-to-too-sho.patch \
	file://da9063-using-RTC-to-reboot-silk-board.patch \
	file://iwg20m/0001-ARM-DTS-Initial-support-device-tree-for-iwg20m.patch \
	file://iwg20m/0002-ARM-DTS-iwg20m-Add-support-eMMC.patch \
	file://iwg20m/0003-ARM-shmobile-r8a7743-Allow-booting-secondary-CPU-cor.patch \
	file://iwg20m/0004-net-ethernet-ravb-add-support-r8a7743-SoC.patch \
	file://iwg20m/0005-pinctrl-sh-pfc-r8a7743-add-pinmux-for-ravb.patch \
	file://iwg20m/0006-ARM-config-shmobile-enable-ethernet-AVB.patch \
	file://iwg20m/0007-ARM-DTS-r8a7743-add-definition-for-ether-AVB.patch \
	file://iwg20m/0008-ARM-DTS-iwg20m-enable-ethernet-AVB.patch \
	file://iwg20m/0009-ARM-DTS-iwg20m-add-support-SDIO.patch \
	file://iwg20m/0010-ARM-DTS-iwg20m-enable-USB-ports.patch \
	file://iwg20m/0011-ARM-DTS-iwg20m-Enable-SPI.patch \
	file://iwg20m/0012-spi-sh-msiof-add-IDs-for-for-spi-of-r8a7743-SoC.patch \
	file://iwg20m/0013-ARM-config-shmobile-enable-SPI.patch \
	file://iwg20m/0014-ARM-config-shmobile-enable-JFFS2-file-system.patch \
	file://iwg20m/0015-ARM-DTS-iwg20m-enable-i2c-control-for-RTC.patch \
	file://iwg20m/0016-ARM-DTS-iwg20m-enable-remained-scif-channels.patch \
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

	kernel_configure_variable USB_U_ETHER n
	kernel_configure_variable USB_ETH m

	yes '' | oe_runmake oldconfig
}


## for gles-kernel-module
do_compile_append() {
	cp ${KBUILD_OUTPUT}/vmlinux ${STAGING_KERNEL_BUILDDIR}/vmlinux

}
