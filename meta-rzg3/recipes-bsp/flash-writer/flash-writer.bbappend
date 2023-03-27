require include/rzg2l-security-config.inc
inherit python3native

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI = " \
	file://FlashWriter.bin;subdir=${BPN} \
	file://FlashWriter.mot;subdir=${BPN} \
	"
SRC_URI[FlashWriter.bin.md5sum] = "f57f27b3d186cf4765cf2dd4b9343bcb"
SRC_URI[FlashWriter.bin.sha256sum] = "e5d18cd9ab6ef3a7a2eb59fe582ea589d441914215c609e1da93ed547274decc"
SRC_URI[FlashWriter.mot.md5sum] = "d78d10b248c2dc97f932f2887227bd0b"
SRC_URI[FlashWriter.mot.sha256sum] = "e6643dc1a98a981f5f72350c711d1de6ddc8bd61f019745069d8085d930ada0c"

PV = "0127"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

DEPENDS = " \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", " \
		python3-pycryptodome-native python3-pycryptodomex-native secprv-native bptool-native fiptool-native \
	", "",d)}"

S = "${WORKDIR}/${BPN}"
BUILD_TBB_DIR = "${S}/build_tbb"

do_configure[noexec] = "1"

do_compile () {
	#create certification binary
	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		mkdir -p ${BUILD_TBB_DIR}/tmp

		python3 ${MANIFEST_GENERATION_KCERT} \
			-info ${DIRPATH_MANIFEST_GENTOOL}/info/flash_${IMG_AUTH_MODE}_g3s_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem \
			-certout ${BUILD_TBB_DIR}/tmp/flash_writer-kcert.bin

		python3 ${MANIFEST_GENERATION_CCERT} \
			-info ${DIRPATH_MANIFEST_GENTOOL}/info/flash_${IMG_AUTH_MODE}_g3s_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem \
			-imgin ${S}/FlashWriter.bin \
			-certout ${BUILD_TBB_DIR}/tmp/flash_writer-ccert.bin \
			-imgout ${BUILD_TBB_DIR}/tmp/flash_writer-sign.bin

		objcopy -I binary --pad-to=0x00000400 ${BUILD_TBB_DIR}/tmp/flash_writer-kcert.bin \
			${BUILD_TBB_DIR}/tmp/flash_writer-kcert_pad.bin
		objcopy -I binary --pad-to=0x00000C00 ${BUILD_TBB_DIR}/tmp/flash_writer-ccert.bin \
			${BUILD_TBB_DIR}/tmp/flash_writer-ccert_pad.bin

		cat ${BUILD_TBB_DIR}/tmp/flash_writer-kcert_pad.bin \
			${BUILD_TBB_DIR}/tmp/flash_writer-ccert_pad.bin \
			${BUILD_TBB_DIR}/tmp/flash_writer-sign.bin > ${BUILD_TBB_DIR}/tmp/flash_writer-image.bin

		bptool ${BUILD_TBB_DIR}/tmp/flash_writer-image.bin ${BUILD_TBB_DIR}/tmp/flash_writer-bparm.bin 0x107000 scif

		objcopy -I binary -O elf64-little --add-section .parm=${BUILD_TBB_DIR}/tmp/flash_writer-bparm.bin \
			--set-section-flags .parm=alloc --adjust-section-vma .parm=0xA1E00 \
			--adjust-section-vma .data=0x107000 ${BUILD_TBB_DIR}/tmp/flash_writer-image.bin \
			${BUILD_TBB_DIR}/tmp/flash_writer_bp_tbb.elf
		objcopy -O srec --srec-forceS3 ${BUILD_TBB_DIR}/tmp/flash_writer_bp_tbb.elf \
			${BUILD_TBB_DIR}/tmp/flash_writer_bp_tbb.mot
	fi

	# Convert to srec
	objcopy -I binary -O srec --adjust-vma=0xA1E00 --srec-forceS3 ${S}/FlashWriter.bin ${S}/FlashWriter.srec
}

do_deploy () {
	# Create deploy folder
	install -d ${DEPLOYDIR}

	# Copy fip images
	install -m 0644  ${S}/FlashWriter.srec ${DEPLOYDIR}/FlashWriter-${MACHINE}.srec
	install -m 0644  ${S}/FlashWriter.mot ${DEPLOYDIR}/FlashWriter-${MACHINE}.mot

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		install -m 0644  ${BUILD_TBB_DIR}/tmp/flash_writer_bp_tbb.elf ${DEPLOYDIR}/FlashWriter-${MACHINE}_bp_TBB.elf
		install -m 0644  ${BUILD_TBB_DIR}/tmp/flash_writer_bp_tbb.mot ${DEPLOYDIR}/FlashWriter-${MACHINE}_bp_TBB.mot
	fi
}

addtask deploy before do_build after do_compile
