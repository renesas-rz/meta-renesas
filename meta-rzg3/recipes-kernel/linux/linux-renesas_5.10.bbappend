COMPATIBLE_MACHINE_rzg3s = "(rzg3s-dev|smarc-rzg3s)"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

BRANCH = "${@oe.utils.conditional("IS_RT_BSP", "1", "rzg3s-cip17-rt7", "rzg3s-cip17",d)}"
SRCREV = "${@oe.utils.conditional("IS_RT_BSP", "1", "dba3104dccca586e776be05c52ea6209ff9aa406", "eda8e1a3e8e274080b6595f39a3c102af74c761e",d)}"

LINUX_VERSION = "${@oe.utils.conditional("IS_RT_BSP", "1", "5.10.145-cip17-rt7", "5.10.145-cip17",d)}"

SRC_URI_remove = " \
	file://0001-Fixed-an-issue-that-caused-flicker-when-outputting-t.patch \
 "

IWLWIFI_FIRMWARE = "https://git.kernel.org/pub/scm/linux/kernel/git/iwlwifi/linux-firmware.git/plain/iwlwifi-cc-a0-46.ucode;md5sum=babe453e0bc18ec93768ec6f002d8229;downloadfilename=iwlwifi-cc-a0-46.ucode"

SRC_URI_append = " \
	${@bb.utils.contains('MACHINE_FEATURES', 'ax200-wifi', '${IWLWIFI_FIRMWARE}', '',d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'ax200-wifi', 'file://ax200-wifi.cfg', '',d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'atheros-ar9287-wifi', 'file://atheros-ar9287-wifi.cfg', '',d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'rtl8169-firmware', 'file://rtl8169-firmware.cfg', '',d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'nvme', 'file://nvme.cfg', '',d)} \
 "

BUILTIN_FIRMWARE_DIR = "${STAGING_KERNEL_DIR}/drivers/base/firmware_loader/builtin"
do_download_firmware () {
	if [ -f ${WORKDIR}/iwlwifi-cc-a0-46.ucode ]; then
		install -m 755 ${WORKDIR}/iwlwifi-cc-a0-46.ucode ${BUILTIN_FIRMWARE_DIR}
	fi
}

addtask do_download_firmware after do_configure before do_compile