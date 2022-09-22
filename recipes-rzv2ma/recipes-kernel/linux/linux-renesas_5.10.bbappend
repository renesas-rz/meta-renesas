FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
   file://patches/rzv2m_patch/0000-Makefile-rzv2m.patch \
   file://patches/rzv2m_patch/0000-headS-rzv2m.patch \
   file://patches/rzv2m_patch/0000-ptrace-rzv2m.patch \
   file://patches/rzv2m_patch/0001-defconfig-add-config-rzv2m.patch \
   file://patches/rzv2m_patch/0002-kconfig-platforms-add-config-rzv2m.patch \
   file://patches/rzv2m_patch/0003-dts-renesas-rzv2m.patch \
   file://patches/rzv2m_patch/0004-dts-Makefile-renesas-rzv2m.patch \
   file://patches/rzv2m_patch/0005-soc-renesas-rzv2m.patch \
   file://patches/rzv2m_patch/0006-include-dt-bindings-clock-rzv2m.patch \
   file://patches/rzv2m_patch/0007-clk-renesas-rzv2m.patch \
   file://patches/rzv2m_patch/0007-fix-lack-of-comma-in-r9a09g011gbg-cpg-mssr-driver.patch \
   file://patches/rzv2m_patch/0011-mmc-renesas-rzv2m.patch \
   file://patches/rzv2m_patch/0012-soc-sys-renesas-rzv2m.patch \
   file://patches/rzv2m_patch/0013-tty-serial-8250-renesas-rzv2m.patch \
   file://patches/rzv2m_patch/0014-include-asm-generic-serial-renesas-rzv2m.patch \
   file://patches/rzv2m_patch/0015-include-uapi-linux-serial-renesas-rzv2m.patch \
   file://patches/rzv2m_patch/0016-include-dt-bindings-power-rzv2m.patch \
   file://patches/rzv2m_patch/0017-modified-dts-defconfig-sdboot-rzv2m.patch \
   file://patches/rzv2m_patch/0018-modified-dts-CMAforDRP-rzv2m.patch \
   file://patches/rzv2m_patch/0019-modified-kernel-memoryarea.patch \
   file://patches/rzv2m_patch/0020_enabled_usb-xhci_and_i2c.patch \
   file://patches/rzv2m_patch/0000_enabled_read-only_mappings.patch \
   file://patches/rzv2m_patch/0021-enabled-udmabuf-rzv2m.patch \
   file://patches/rzv2m_patch/0022-enabled_eth-rzv2m.patch \
   file://patches/rzv2m_patch/0023-preserved-bootargs.patch \
   file://patches/rzv2m_patch/0025-chg-cma-area.patch \
   file://patches/rzv2m_patch/0027-mmc-enable-drv.patch \
   file://patches/rzv2m_patch/0028-enable-pmu-core0.patch \
   file://patches/rzv2m_patch/0030-change-ModelName.patch \
   file://patches/rzv2m_patch/0031-enable-i2c-drv.patch \
   file://patches/rzv2m_patch/0032-enable-pwm-drv.patch \
   file://patches/rzv2m_patch/0033-remake_dts.patch \
   file://patches/rzv2m_patch/0034_bug_fix_dts.patch \
   file://patches/rzv2m_patch/0035-chg-ArchTimerFrequency.patch \
   file://patches/rzv2m_patch/0036_add_hw_tim.patch \
   file://patches/rzv2m_patch/0036-replace_devm_ioremap_nocache_to_devm_ioremap_in_time.patch \
   file://patches/rzv2m_patch/0037-added-cpg_drv.patch \
   file://patches/rzv2m_patch/0038-chg-fix-cpg_drv.patch \
   file://patches/rzv2m_patch/0039-Update-i2c-driver-source-code.patch \
   file://patches/rzv2m_patch/0040-Update-available-devices-evaluation-board.patch \
   file://patches/rzv2m_patch/0041-fixed-bug-cpgdriver-clocksource.patch \
   file://patches/rzv2m_patch/0042-fixed-bug-pwm.patch \
   file://patches/rzv2m_patch/0043-fixed-bug-hw_tim.patch \
   file://patches/rzv2m_patch/0044-modified-gicd-init.patch \
   file://patches/rzv2m_patch/0045-modified-gic-set-affinity.patch \
   file://patches/rzv2m_patch/0046-add-usbrole-setting.patch \
   file://patches/rzv2m_patch/0047_chg_cpg_clock_table.patch \
   file://patches/rzv2m_patch/0048-add-switching-voltage-sd.patch \
   file://patches/rzv2m_patch/0049-enable-usb-peripheral.patch \
   file://patches/rzv2m_patch/0050-add-switching-voltage-emmc.patch \
   file://patches/rzv2m_patch/0051-usb-otg-support.patch \
   file://patches/rzv2m_patch/0051-amend-funtions-for-usb-otg.patch \
   file://patches/rzv2m_patch/0052-remake-sdhi_core_drv.patch \
   file://patches/rzv2m_patch/0052-include-sys_soc-library-and-add-comma-for-SD.patch \
   file://patches/rzv2m_patch/0053-update-pwm-devicetree.patch \
   file://patches/rzv2m_patch/0054-update-i2c-devicetree.patch \
   file://patches/rzv2m_patch/0055-add-csi_driver.patch \
   file://patches/rzv2m_patch/0056-add-pfc_driver.patch \
   file://patches/rzv2m_patch/0056-fix-irq-get-domain-generic-chip-rzv2m-pinctrl.patch \
   file://patches/rzv2m_patch/0057-pwm_disable_debug_log.patch \
   file://patches/rzv2m_patch/0058-remake-devicetree.patch \
   file://patches/rzv2m_patch/0059-fixed-csi_driver.patch \
   file://patches/rzv2m_patch/0060-Add-WDT-driver-source-for-RZV2M.patch \
   file://patches/rzv2m_patch/0061-Add-WDT-dts-config-for-RZV2M.patch \
   file://patches/rzv2m_patch/0061-modify-ioremap-nocache-to-ioremap-for-WDT-driver.patch \
   file://patches/rzv2m_patch/0062-fixed-bug-csi.patch \
   file://patches/rzv2m_patch/0063-apply-ddr-4gb.patch \
   file://patches/rzv2m_patch/0064-chg-gic-init.patch \
   file://patches/rzv2m_patch/0065-fixed-bug-usb-peripheral-driver.patch \
   file://patches/rzv2m_patch/0065-change-usb_role_switch_property-to-role_sw_by_connec.patch \
   file://patches/rzv2m_patch/0066-Enable-uinput-mousedev-kernel-module.patch \
   file://patches/rzv2m_patch/0067-change_adress_map.patch \
   file://patches/rzv2m_patch/0072-Fix-issue-when-detecting-the-USB-3.1-capability.patch \
   file://patches/rzv2m_patch/0073-Add-setting-the-pin-configuration-for-i2c-2.patch \
   file://patches/rzv2m_patch/0074-Modify-i2c-clocks-setting.patch \
   file://patches/rzv2m_patch/0075-bug-fixed-pmu-interrupt.patch \
   file://patches/rzv2m_patch/0076-modified-cpu-idle-thread.patch \
   file://patches/rzv2m_patch/0077-modified-memorymap-for-drpai.patch \
   file://patches/rzv2m_patch/0078-Add-setting-for-the-uvc.patch \
   file://patches/rzv2m_patch/0079-modified-rammap-area-rzv2m-periferal.patch \
   file://patches/rzv2m_patch/0080-modified-endpoint-num-rzv2m-periferal.patch \
   file://patches/rzv2m_patch/0081-trigger-renesas_usb3_role_switch_set-get.patch \
   file://patches/rzv2m_patch/fixed-cpg-driver-for-rzv2m.patch \
   file://patches/rzv2m_patch/fixed-dts-for-rzv2m.patch \
   file://patches/rzv2m_patch/fixed-hwtim-driver-for-rzv2m.patch \
   file://patches/rzv2m_patch/fixed-usb-function-driver-for-rzv2m.patch \
   file://patches/rzv2m_patch/fixed-usb-host-driver-for-rzv2m.patch \
   file://patches/rzv2m_patch/0087-modified-defconfig.patch \
   file://patches/rzv2m_patch/0088_delete_u_dma_buf_config.patch \
"

SRC_URI_append = " \
   file://patches/rzv2ma_patch/0001-modified-pfc-for-v2ma.patch \
   file://patches/rzv2ma_patch/0002-added-device-ch-for-v2ma.patch \
   file://patches/rzv2ma_patch/0003-update-cpg-function-forV2MA.patch \
   file://patches/rzv2ma_patch/0004-apply-dualcore-spin-table.patch \
   file://patches/rzv2ma_patch/0005-modified-socName.patch \
   file://patches/rzv2ma_patch/0006-modified-memoryMap-v2ma.patch \
   file://patches/rzv2ma_patch/0007-delete-udma-buf-node-forV2MA.patch \
   file://patches/rzv2ma_patch/0008-device-tree-for-rzv2ma.patch \
   file://patches/rzv2ma_patch/0009-added-config-r9a09g055ma3gbg.patch \
   file://patches/rzv2ma_patch/0010-Fix-cannot-detect-SD-Card_after_reboot_board.patch \
   file://patches/rzv2ma_patch/0011-fixed-memorymap-for-rzv2ma.patch \
   file://patches/rzv2ma_patch/0012-remove-old-cpg-driver-rzv2m.patch \
   file://patches/rzv2ma_patch/0013-add-new-cpg-driver-rzv2ma.patch \
   file://patches/rzv2ma_patch/0014-modified-cpg-core-clk-setting.patch \
   file://patches/rzv2ma_patch/0015-add-poweroff-reset-driver-rzv2m.patch \
   file://patches/rzv2ma_patch/0016-add-dts-config-poweroff-reset-driver-rzv2m.patch \
   file://patches/rzv2ma_patch/0017-fix-interupt-handler-pwm.patch \
   file://patches/rzv2ma_patch/0018-added-watchdog-timer-ch1.patch \
   file://patches/rzv2m_patch/0089-RZV2M_WC-A-conf-local.conf-Cip_Core-0.patch \
   file://patches/rzv2m_patch/0090-RZV2M_WC-A-conf-local.conf-Cip_Core-0_serial.patch \
   file://patches/rzv2ma_patch/0019-bugfix-reset-controller-rzv2ma.patch \
   file://patches/rzv2ma_patch/0020-add-dma-driver-support-v2ma.patch \
   file://patches/rzv2ma_patch/0023-update-to-support-MEMtoMEM-DMA-testing.patch \
   file://patches/rzv2ma_patch/0024-reflect-dma-MtoM-all-channels.patch \
   file://patches/rzv2ma_patch/0025-Add-PCIe-dts-config-driver.patch \
   file://patches/rzv2ma_patch/0026-added-thermal-sensor-driver.patch \
   file://patches/rzv2ma_patch/0027-deleted-unsupported-files.patch \
   file://patches/rzv2ma_patch/0028-bugfix-dts-regulator-vccq-sdhi0.patch \
   file://patches/rzv2ma_patch/0029-disable-config-thermal-rcar-ems.patch \
"

SRC_URI_append = " \
	file://gsx.cfg \
"

# Install USB3.0 firmware to rootfs
USB3_FIRMWARE_V2 = "https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/r8a779x_usb3_v2.dlmem;md5sum=645db7e9056029efa15f158e51cc8a11"
USB3_FIRMWARE_V3 = "https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/r8a779x_usb3_v3.dlmem;md5sum=687d5d42f38f9850f8d5a6071dca3109"

SRC_URI_append = " \
	${USB3_FIRMWARE_V2} \
	${USB3_FIRMWARE_V3} \
	${@bb.utils.contains('MACHINE_FEATURES','usb3','file://usb3.cfg','',d)} \
"

# Install regulatory database firmware to rootfs
REGULATORY_DB = "https://git.kernel.org/pub/scm/linux/kernel/git/sforshee/wireless-regdb.git/plain/regulatory.db?h=master-2019-06-03;md5sum=ce7cdefff7ba0223de999c9c18c2ff6f;downloadfilename=regulatory.db"
REGULATORY_DB_P7S = "https://git.kernel.org/pub/scm/linux/kernel/git/sforshee/wireless-regdb.git/plain/regulatory.db.p7s?h=master-2019-06-03;md5sum=489924336479385e2c35c21d10eb3ca2;downloadfilename=regulatory.db.p7s"

# Install Bluetooth firmware to rootfs
BLUETOOTH_FW = " https://git.ti.com/cgit/wilink8-bt/ti-bt-firmware/plain/TIInit_11.8.32.bts;md5sum=665b7c25be21933acc30dda44cfcace6;downloadfilename=TIInit_11.8.32.bts"

SRC_URI_append = " \
	${REGULATORY_DB} \
	${REGULATORY_DB_P7S} \
	${BLUETOOTH_FW} \
	file://wifi.cfg \
	file://bluetooth.cfg \
"

FIRMWARE_DIR = "${STAGING_KERNEL_DIR}/drivers/base/firmware_loader/builtin"
do_download_firmware () {
       install -m 755 ${WORKDIR}/r8a779x_usb3_v*.dlmem ${FIRMWARE_DIR}
       install -m 755 ${WORKDIR}/regulatory* ${FIRMWARE_DIR}
       mkdir -p ${FIRMWARE_DIR}/ti-connectivity
       install -m 755 ${WORKDIR}/TIInit_11.8.32.bts ${FIRMWARE_DIR}/ti-connectivity
}
addtask do_download_firmware after do_configure before do_compile
