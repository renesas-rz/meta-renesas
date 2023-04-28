FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRCREV = "c08f788c27243954a0d6231d5e4e9b0ef721c7a4"

SRC_URI_append = "\
	file://rzv2m_patch/0001-updated-uboot-rzv2m-final.patch \
	file://rzv2m_patch/0002-chg-l2cache-clear.patch \
	file://rzv2m_patch/0003-add-bank-settings.patch \
	file://rzv2m_patch/0004-apply_new-memorymap-kernel-area-address.patch \
	file://rzv2m_patch/0005-fixed-bug-auto-boot-when-no-serial.patch \
	file://rzv2m_patch/0006-modified-text-section-address.patch \
	file://rzv2m_patch/0007-update-memory-map.patch \
"

SRC_URI_append_rzv2m = "\
	file://rzv2m_patch/0008-fixed-pfc-emmc.patch \
	file://rzv2m_patch/0009-fixed-mmc-driver-v2m-v2ma.patch \
	file://rzv2m_patch/0010-fixed-dts-mmc-driver-rzv2m.patch \
	file://rzv2m_patch/0011-modified-uboot-configs.patch \
	file://rzv2m_patch/0012-removed-rdk-shutdown-cmd.patch \
	file://rzv2m_patch/0013-added-evk-shutdown-cmd.patch \
	file://rzv2m_patch/0014-modified-uboot-version.patch \
	file://rzv2m_patch/0015-modified-relocate_fdt.patch \
	file://rzv2m_patch/0016-deleted-rdk-files-rzv2m-dev.patch \
	file://rzv2m_patch/0017-added-evk-files-rzv2m-dev.patch \
	file://rzv2m_patch/0018-apply-debug-func-to-fdt-boot-reserve-region.patch \
"

SRC_URI_append_rzv2ma = "\
	file://rzv2ma_patch/0001-added-configuration-file-for-rzv2ma.patch \
	file://rzv2ma_patch/0002-fixed-mmc-driver-v2m-v2ma.patch \
	file://rzv2ma_patch/0003-removed-rdk-shutdown-cmd.patch \
	file://rzv2ma_patch/0004-added-evk-shutdown-cmd.patch \
	file://rzv2ma_patch/0005-modified-file-name-kernel-image.patch \
	file://rzv2ma_patch/0006-deleted-unsupported-files.patch \
	file://rzv2ma_patch/0007-u-boot_setting_usb_phy.patch \
	file://rzv2ma_patch/0008-u-boot_improve_comment.patch \
	file://rzv2ma_patch/0009-modified-uboot-version.patch \
	file://rzv2ma_patch/0010-fix-ether_net_error_correction.patch \
	file://rzv2ma_patch/0011-fix-sdhi_error_correction.patch \
	file://rzv2ma_patch/0012-modified-icb-performance-improvement.patch \
	file://rzv2ma_patch/0013-fix-the-warning-of-u-boot-board.patch \
	file://rzv2ma_patch/0014-fix-the-warning-of-u-boot-cmd.patch \
	file://rzv2ma_patch/0015-fix-the-warning-of-u-boot-mmc.patch \
	file://rzv2ma_patch/0016-fix-the-warning-of-u-boot-net.patch \
	file://rzv2ma_patch/0017-fix-the-warning-of-u-boot-pfc.patch \
	file://rzv2ma_patch/0018-fix-the-warning-of-u-boot-serial.patch \
	file://rzv2ma_patch/0019-removed-icb-settings.patch \
"

EXE_PYTHON = "python3"
PY_FILE = "${B}/${config}/scripts/sum.py"

do_compile_append(){
	rm -f ${B}/${config}/u-boot_param.bin
	python3 ${B}/${config}/source/scripts/sum.py ${B}/${config}/${UBOOT_SYMLINK} ${B}/${config}/u-boot_param.bin
}

do_install_append () {
	install -m 644 ${B}/${config}/u-boot_param.bin ${D}/boot/u-boot_param.bin
}

do_deploy_append  () {
	install -m 644 ${B}/${config}/u-boot_param.bin ${DEPLOYDIR}/u-boot_param.bin
}
