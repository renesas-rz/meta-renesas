FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

# Install USB3.0 firmware to rootfs
USB3_FIRMWARE_V2 = "https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/r8a779x_usb3_v2.dlmem;md5sum=645db7e9056029efa15f158e51cc8a11"
USB3_FIRMWARE_V3 = "https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/r8a779x_usb3_v3.dlmem;md5sum=687d5d42f38f9850f8d5a6071dca3109"

SRC_URI:append:rzg2h-family = " \
	${USB3_FIRMWARE_V2} \
	${USB3_FIRMWARE_V3} \
	${@bb.utils.contains('MACHINE_FEATURES','usb3','file://usb3.cfg','',d)} \
"

# Install regulatory database firmware to rootfs
REGULATORY_DB = "https://git.kernel.org/pub/scm/linux/kernel/git/sforshee/wireless-regdb.git/plain/regulatory.db?h=master-2023-09-01;md5sum=712009958781c0e8b00b736c5084ec43;downloadfilename=regulatory.db"
REGULATORY_DB_P7S = "https://git.kernel.org/pub/scm/linux/kernel/git/sforshee/wireless-regdb.git/plain/regulatory.db.p7s?h=master-2023-09-01;md5sum=89ceedb9d1c909be3147e2f9deebab7b;downloadfilename=regulatory.db.p7s"

# Install Bluetooth firmware to rootfs
BLUETOOTH_FW = " https://git.ti.com/cgit/wilink8-bt/ti-bt-firmware/plain/TIInit_11.8.32.bts;md5sum=665b7c25be21933acc30dda44cfcace6;downloadfilename=TIInit_11.8.32.bts"

SRC_URI:append:rzg2h-family = " \
	${REGULATORY_DB} \
	${REGULATORY_DB_P7S} \
	${BLUETOOTH_FW} \
	file://wifi.cfg \
	file://bluetooth.cfg \
"

FIRMWARE_DIR = "${STAGING_KERNEL_DIR}/drivers/base/firmware_loader/builtin"
do_download_firmware() {
    :
}

do_download_firmware:rzg2h-family () {
       install -m 755 ${WORKDIR}/r8a779x_usb3_v*.dlmem ${FIRMWARE_DIR}
       install -m 755 ${WORKDIR}/regulatory* ${FIRMWARE_DIR}
       mkdir -p ${FIRMWARE_DIR}/ti-connectivity
       install -m 755 ${WORKDIR}/TIInit_11.8.32.bts ${FIRMWARE_DIR}/ti-connectivity
}
addtask do_download_firmware after do_configure before do_compile

SRC_URI:append:rzg2h-family = " \
	${@oe.utils.ifelse("${ECC_FULL}" == "1"," \
	file://v6.12/usb/0001-usb-add-dma-mempool-for-EHCI-and-OHCI.patch \
	file://v6.12/usb/0002-arm64-dts-renesas-add-mempool-for-EHCI-and-OHCI-devi.patch \
	", "")} \
"

# These patches are for reference only. They are preliminary.
SRC_URI:append = " \
	file://v6.12/display/0001-drm-bridge-adv7511-Clear-HPD-IRQ-before-powering-on-.patch \
	file://v6.12/display/0002-drm-bridge-ite-it6263-Support-S2R-ITE-it6263.patch \
"

# Remove these patches for RZ/T2N as the IT6263 driver do not exist in the kernel tree.
SRC_URI:remove:rzt2n-family = " \
	file://v6.12/display/0001-drm-bridge-adv7511-Clear-HPD-IRQ-before-powering-on-.patch \
	file://v6.12/display/0002-drm-bridge-ite-it6263-Support-S2R-ITE-it6263.patch \
"

SRC_URI:append:rzt2n-family = " \
	file://v6.12/t2n/0001-Revert-drivers-phy-renesas-phy-rcar-gen3-usb2-Suppor.patch \
	file://v6.12/t2n/0002-phy-renesas-rcar-gen3-usb2-store-drvdata-pointer-in-.patch \
	file://v6.12/t2n/0003-phy-renesas-rcar-gen3-usb2-Allow-SoC-specific-OBINT-.patch \
	file://v6.12/t2n/0004-phy-renesas-rcar-gen3-usb2-Add-support-for-RZ-T2H-So.patch \
	file://v6.12/t2n/0005-phy-renesas-rcar-gen3-usb2-Move-debug-print-after-re.patch \
	file://v6.12/t2n/0006-phy-renesas-rcar-gen3-usb2-Fix-ID-check-logic-with-V.patch \
	file://v6.12/t2n/0007-phy-renesas-rcar-gen3-usb2-Remove-redundant-ternary-.patch \
	file://v6.12/t2n/0008-phy-renesas-rcar-gen3-usb2-Simplify-ID-VBUS-detectio.patch \
	file://v6.12/t2n/0009-phy-renesas-rcar-gen3-usb2-Add-support-for-RZ-T2N-So.patch \
	file://v6.12/t2n/0010-usb-renesas_usbhs-Fix-a-resource-leak-in-usbhs_pipe_.patch \
	file://v6.12/t2n/0011-usb-renesas_usbhs-use-proper-DMAENGINE-API-for-termi.patch \
	file://v6.12/t2n/0012-usb-renesas_usbhs-fix-use-after-free-in-ISR-during-d.patch \
	file://v6.12/t2n/0013-usb-renesas_usbhs-Fix-power-off-ordering-on-unbind.patch \
	file://v6.12/t2n/0014-phy-renesas-rcar-gen3-usb2-Select-RZ-T2N-role-from-V.patch \
	file://v6.12/t2n/0015-arm64-dts-renesas-r9a07g076m48-dev-Add-renesas-no-ot.patch \
"
