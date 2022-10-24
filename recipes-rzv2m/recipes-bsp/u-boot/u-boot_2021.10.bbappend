FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

# if you want to add new patch file, please set the patch file under the directory "u-boot"


# Start RZV2M auto-generated variables
PR = "r1"

SRC_URI_append_r9a09g011gbg += "\
  file://rzv2m_patch/0001-updated-uboot-rzv2m-final.patch \
  file://rzv2m_patch/0002-chg-l2cache-clear.patch \
  file://rzv2m_patch/0003-add-bank-settings.patch \
  file://rzv2m_patch/0004-apply_new-memorymap-kernel-area-address.patch \
  file://rzv2m_patch/0005-fixed-bug-auto-boot-when-no-serial.patch \
  file://rzv2m_patch/0006-modified-text-section-address.patch \
  file://rzv2m_patch/0007-update-memory-map.patch \
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

# Finish RZV2M auto-generated variables

