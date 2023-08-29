FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

USB3_FW = "https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/r8a779x_usb3_v1.dlmem?h=20230625;md5sum=5a3cb919ba099d9cd21cf3685eb59b5d;downloadfilename=r8a779x_usb3_v1.dlmem"
REGULATORY_DB = "https://git.kernel.org/pub/scm/linux/kernel/git/sforshee/wireless-regdb.git/plain/regulatory.db?h=master-2019-06-03;md5sum=ce7cdefff7ba0223de999c9c18c2ff6f;downloadfilename=regulatory.db"
REGULATORY_DB_P7S = "https://git.kernel.org/pub/scm/linux/kernel/git/sforshee/wireless-regdb.git/plain/regulatory.db.p7s?h=master-2019-06-03;md5sum=489924336479385e2c35c21d10eb3ca2;downloadfilename=regulatory.db.p7s"

SRC_URI_append = " \
	file://rzg1_common.cfg \
	file://patches.scc \
	${USB3_FW} \
	${REGULATORY_DB} \
	${REGULATORY_DB_P7S} \
"

SRC_URI_append_iwg22m = " \
	file://iwg22m.cfg \
"

SRC_URI_append_iwg20m-g1m = " \
	file://iwg20m.cfg \
"

SRC_URI_append_iwg20m-g1n = " \
	file://iwg20m.cfg \
"

SRC_URI_append_iwg21m = " \
	file://iwg21m.cfg \
"

SRC_URI_append_iwg23s = " \
	file://iwg23s.cfg \
	file://patches_iwg23s.scc \
"

FIRMWARE_DIR = "${STAGING_KERNEL_DIR}/drivers/base/firmware_loader/builtin/"
do_download_firmware () {
       install -m 755 ${WORKDIR}/r8a779x_usb3_v1.dlmem ${FIRMWARE_DIR}
       install -m 755 ${WORKDIR}/regulatory.db ${FIRMWARE_DIR}
       install -m 755 ${WORKDIR}/regulatory.db.p7s ${FIRMWARE_DIR}
}
addtask do_download_firmware after do_configure before do_compile

KBUILD_DEFCONFIG = "shmobile_defconfig"
KCONFIG_MODE = "alldefconfig"