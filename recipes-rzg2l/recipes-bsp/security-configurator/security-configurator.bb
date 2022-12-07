DESCRIPTION = "RZ Security Configurator"
LICENSE = "CLOSED"

require include/rzg2l-security-config.inc
inherit deploy python3native

PV = "v1.11"

SRC_URI = " file://security_configurator.zip "

DEPENDS = " \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", "python3-pycryptodome-native python3-pycryptodomex-native secprv-native bootparameter-native", "",d)} \
"

COMPATIBLE_MACHINE = "(smarc-rzg2l|smarc-rzg2lc|smarc-rzg2ul|smarc-rzv2l)"

BOARD_smarc-rzg2l      = "RZG2L_SMARC"
BOARD_smarc-rzg2lc     = "RZG2LC_SMARC"
BOARD_smarc-rzg2ul     = "RZG2UL_SMARC"
BOARD_smarc-rzv2l      = "RZV2L_SMARC"

PMIC_BOARD_smarc-rzg2l = "RZG2L_SMARC_PMIC"
PMIC_BOARD_smarc-rzv2l = "RZV2L_SMARC_PMIC"

S = "${WORKDIR}/security_configurator"

BUILD_DIR = "${S}/build/${BOARD}"
BUILD_PMIC_DIR = "${S}/build_pmic/${BOARD}"

BUILD_TBB_DIR = "${S}/build_tbb/${BOARD}"
BUILD_PMIC_TBB_DIR = "${S}/build_pmic_tbb/${BOARD}"

do_compile() {
	oe_runmake BOARD=${BOARD} OUTDIR=${BUILD_DIR}

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		oe_runmake BOARD=${PMIC_BOARD} OUTDIR=${BUILD_PMIC_DIR};
	fi

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		oe_runmake BOARD=${BOARD} OUTDIR=${BUILD_TBB_DIR} TRUSTED_BOARD_BOOT=1

		mkdir -p ${BUILD_TBB_DIR}/tmp
		IMAGE_FILE=$(find "${BUILD_TBB_DIR}" -name "Security_Configurator*.bin" -maxdepth 1 -printf "%f\n" )
		
		python3 ${MANIFEST_GENERATION_KCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -certout ${BUILD_TBB_DIR}/tmp/sec-cfg-kcert.bin

		python3 ${MANIFEST_GENERATION_CCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -imgin ${BUILD_TBB_DIR}/${IMAGE_FILE} \
			-certout ${BUILD_TBB_DIR}/tmp/sec-cfg-ccert.bin -imgout ${BUILD_TBB_DIR}/tmp/sec-cfg-image.bin

		objcopy -I binary --adjust-vma=0x00012000 --pad-to=0x12400 ${BUILD_TBB_DIR}/tmp/sec-cfg-kcert.bin
		objcopy -I binary --adjust-vma=0x00012400 --pad-to=0x13000 ${BUILD_TBB_DIR}/tmp/sec-cfg-ccert.bin

		cat ${BUILD_TBB_DIR}/tmp/sec-cfg-kcert.bin ${BUILD_TBB_DIR}/tmp/sec-cfg-ccert.bin \
			${BUILD_TBB_DIR}/tmp/sec-cfg-image.bin > ${BUILD_TBB_DIR}/tmp/${IMAGE_FILE}

		bootparameter ${BUILD_TBB_DIR}/tmp/${IMAGE_FILE} ${BUILD_TBB_DIR}/${IMAGE_FILE%.*}_TBB.bin
		cat ${BUILD_TBB_DIR}/tmp/${IMAGE_FILE} >> ${BUILD_TBB_DIR}/${IMAGE_FILE%.*}_TBB.bin

		objcopy -I binary -O srec --adjust-vma=0x00011E00 --srec-forceS3 ${BUILD_TBB_DIR}/${IMAGE_FILE%.*}_TBB.bin \
			${BUILD_TBB_DIR}/${IMAGE_FILE%.*}_TBB.srec
	
		if [ "${PMIC_SUPPORT}" = "1" ]; then
			oe_runmake BOARD=${PMIC_BOARD} OUTDIR=${BUILD_PMIC_TBB_DIR} TRUSTED_BOARD_BOOT=1

			mkdir -p ${BUILD_PMIC_TBB_DIR}/tmp
			IMAGE_FILE=$(find "${BUILD_PMIC_TBB_DIR}" -name "Security_Configurator*.bin" -maxdepth 1 -printf "%f\n" )
			
			python3 ${MANIFEST_GENERATION_KCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
				-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -certout ${BUILD_PMIC_TBB_DIR}/tmp/sec-cfg-kcert.bin

			python3 ${MANIFEST_GENERATION_CCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
				-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -imgin ${BUILD_PMIC_TBB_DIR}/${IMAGE_FILE} \
				-certout ${BUILD_PMIC_TBB_DIR}/tmp/sec-cfg-ccert.bin -imgout ${BUILD_PMIC_TBB_DIR}/tmp/sec-cfg-image.bin

			objcopy -I binary --adjust-vma=0x00012000 --pad-to=0x12400 ${BUILD_PMIC_TBB_DIR}/tmp/sec-cfg-kcert.bin
			objcopy -I binary --adjust-vma=0x00012400 --pad-to=0x13000 ${BUILD_PMIC_TBB_DIR}/tmp/sec-cfg-ccert.bin

			cat ${BUILD_PMIC_TBB_DIR}/tmp/sec-cfg-kcert.bin ${BUILD_PMIC_TBB_DIR}/tmp/sec-cfg-ccert.bin \
				${BUILD_PMIC_TBB_DIR}/tmp/sec-cfg-image.bin > ${BUILD_PMIC_TBB_DIR}/tmp/${IMAGE_FILE}

			bootparameter ${BUILD_PMIC_TBB_DIR}/tmp/${IMAGE_FILE} ${BUILD_PMIC_TBB_DIR}/${IMAGE_FILE%.*}_TBB.bin
			cat ${BUILD_PMIC_TBB_DIR}/tmp/${IMAGE_FILE} >> ${BUILD_PMIC_TBB_DIR}/${IMAGE_FILE%.*}_TBB.bin

			objcopy -I binary -O srec --adjust-vma=0x00011E00 --srec-forceS3 ${BUILD_PMIC_TBB_DIR}/${IMAGE_FILE%.*}_TBB.bin \
				${BUILD_PMIC_TBB_DIR}/${IMAGE_FILE%.*}_TBB.srec
		fi
	fi
}

do_install[noexec] = "1"

do_deploy() {
	install -d ${DEPLOYDIR}
	
	install -m 644 ${BUILD_DIR}/*.srec ${DEPLOYDIR}

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 644 ${BUILD_PMIC_DIR}/*.srec ${DEPLOYDIR}
	fi

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		install -m 644 ${BUILD_TBB_DIR}/*_TBB.srec ${DEPLOYDIR}
		
		if [ "${PMIC_SUPPORT}" = "1" ]; then
			install -m 644 ${BUILD_PMIC_TBB_DIR}/*_TBB.srec ${DEPLOYDIR}
		fi
	fi
}

addtask deploy after do_compile
