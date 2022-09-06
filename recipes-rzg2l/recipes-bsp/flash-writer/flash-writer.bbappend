require include/rzg2l-security-config.inc
inherit python3native

DEPENDS_append = " \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", "python3-pycryptodome-native python3-pycryptodomex-native secprv-native bootparameter-native", "",d)} \
"

SRC_URI_append += " \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", "file://0001-flash-writer-supports-secure-boot.patch", "",d)} \
"
BUILD_TBB_DIR = "${S}/build_tbb"
PMIC_BUILD_TBB_DIR = "${S}/build_pmic_tbb"

do_compile_append() {
	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		oe_runmake OUTPUT_DIR=${BUILD_TBB_DIR} clean
		oe_runmake BOARD=${BOARD} OUTPUT_DIR=${BUILD_TBB_DIR} TRUSTED_BOARD_BOOT=ENABLE

		mkdir -p ${BUILD_TBB_DIR}/tbb
		FILE_NAME=$(find "${BUILD_TBB_DIR}" -name "*_TBB.bin" -maxdepth 1 -printf "%f\n" )

		python3 ${MANIFEST_GENERATION_KCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -certout ${BUILD_TBB_DIR}/tbb/flash_writer-kcert.bin

		python3 ${MANIFEST_GENERATION_CCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -imgin ${BUILD_TBB_DIR}/${FILE_NAME} \
			-certout ${BUILD_TBB_DIR}/tbb/flash_writer-ccert.bin -imgout ${BUILD_TBB_DIR}/tbb/flash_writer-sign.bin

		objcopy -I binary --adjust-vma=0x00012000 --pad-to=0x12400 ${BUILD_TBB_DIR}/tbb/flash_writer-kcert.bin
		objcopy -I binary --adjust-vma=0x00012400 --pad-to=0x13000 ${BUILD_TBB_DIR}/tbb/flash_writer-ccert.bin

		cat ${BUILD_TBB_DIR}/tbb/flash_writer-kcert.bin ${BUILD_TBB_DIR}/tbb/flash_writer-ccert.bin \
			${BUILD_TBB_DIR}/tbb/flash_writer-sign.bin > ${BUILD_TBB_DIR}/tbb/flash_writer-image.bin

		bootparameter ${BUILD_TBB_DIR}/tbb/flash_writer-image.bin ${BUILD_TBB_DIR}/tbb/${FILE_NAME}
		cat ${BUILD_TBB_DIR}/tbb/flash_writer-image.bin >> ${BUILD_TBB_DIR}/tbb/${FILE_NAME}

		objcopy -I binary -O srec --adjust-vma=0x00011E00 --srec-forceS3 ${BUILD_TBB_DIR}/tbb/${FILE_NAME} \
			${BUILD_TBB_DIR}/tbb/${FILE_NAME%.*}.mot

		if [ "${PMIC_SUPPORT}" = "1" ]; then
			oe_runmake OUTPUT_DIR=${PMIC_BUILD_TBB_DIR} clean
			oe_runmake BOARD=${PMIC_BOARD} OUTPUT_DIR=${PMIC_BUILD_TBB_DIR} TRUSTED_BOARD_BOOT=ENABLE

			mkdir -p ${PMIC_BUILD_TBB_DIR}/tbb
			FILE_NAME=$(find "${PMIC_BUILD_TBB_DIR}" -name "*_TBB.bin" -maxdepth 1 -printf "%f\n" )

			python3 ${MANIFEST_GENERATION_KCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
				-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -certout ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-kcert_pmic.bin

			python3 ${MANIFEST_GENERATION_CCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
				-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -imgin ${PMIC_BUILD_TBB_DIR}/${FILE_NAME} \
				-certout ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-ccert_pmic.bin -imgout ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-sign_pmic.bin

			objcopy -I binary --adjust-vma=0x00012000 --pad-to=0x12400 ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-kcert_pmic.bin
			objcopy -I binary --adjust-vma=0x00012400 --pad-to=0x13000 ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-ccert_pmic.bin

			cat ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-kcert_pmic.bin ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-ccert_pmic.bin ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-sign_pmic.bin > ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-image_pmic.bin

			bootparameter ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-image_pmic.bin ${PMIC_BUILD_TBB_DIR}/tbb/${FILE_NAME}
			cat ${PMIC_BUILD_TBB_DIR}/tbb/flash_writer-image_pmic.bin >> ${PMIC_BUILD_TBB_DIR}/tbb/${FILE_NAME}

			objcopy -I binary -O srec --adjust-vma=0x00011E00 --srec-forceS3 ${PMIC_BUILD_TBB_DIR}/tbb/${FILE_NAME} \
				${PMIC_BUILD_TBB_DIR}/tbb/${FILE_NAME%.*}.mot
		fi
	fi
}

do_deploy_append() {
	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		install -m 644 ${BUILD_TBB_DIR}/tbb/*.mot ${DEPLOYDIR}
		if [ "${PMIC_SUPPORT}" = "1" ]; then
				install -m 644 ${PMIC_BUILD_TBB_DIR}/tbb/*.mot ${DEPLOYDIR}
		fi
	fi
}
