FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

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
