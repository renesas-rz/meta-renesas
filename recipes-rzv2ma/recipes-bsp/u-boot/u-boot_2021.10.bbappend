FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

# if you want to add new patch file, please set the patch file under the directory "u-boot"


# Start RZV2MA auto-generated variables
PR = "r1"

SRC_URI_append_r9a09g055ma3gbg += "\
  file://rzv2m_patch/0001-updated-uboot-rzv2m-final.patch \
  file://rzv2m_patch/0003-add-bank-settings.patch \
  file://rzv2m_patch/0004-apply_new-memorymap-kernel-area-address.patch \
  file://rzv2m_patch/0005-fixed-bug-auto-boot-when-no-serial.patch \
  file://rzv2m_patch/0006-modified-text-section-address.patch \
  file://rzv2m_patch/0007-update-memory-map.patch \
  file://rzv2ma_patch/0001-added-configuration-file-for-rzv2ma.patch \
  file://rzv2ma_patch/0002-fixed-mmc-driver-v2m-v2ma.patch \
  file://rzv2ma_patch/0003-removed-rdk-shutdown-cmd.patch \
  file://rzv2ma_patch/0004-added-evk-shutdown-cmd.patch \
  file://rzv2ma_patch/0005-modified-file-name-kernel-image.patch \
  file://rzv2ma_patch/0006-deleted-unsupported-files.patch \
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

# Finish RZ/V2MA auto-generated variables

