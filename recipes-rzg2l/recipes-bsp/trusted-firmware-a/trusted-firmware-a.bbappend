require include/rzg2l-security-config.inc
inherit python3native

DEPENDS_append = " \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", "python3-pycryptodome-native python3-pycryptodomex-native secprv-native", "",d)} \
"

SEC_FLAGS = " \
	${@oe.utils.conditional("ENABLE_SPD_OPTEE", "1", " SPD=opteed", "",d)} \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", " TRUSTED_BOARD_BOOT=1 COT=tbbr", "",d)} \
"
EXTRA_FLAGS_append += "${SEC_FLAGS}"
PMIC_EXTRA_FLAGS_append += "${SEC_FLAGS}"

do_compile_append() {

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		python3 ${MANIFEST_GENERATION_KCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -certout ${S}/build/${PLATFORM}/release/bl2-kcert.bin

		python3 ${MANIFEST_GENERATION_CCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -imgin ${S}/build/${PLATFORM}/release/bl2.bin \
			-certout ${S}/build/${PLATFORM}/release/bl2-ccert.bin -imgout ${S}/build/${PLATFORM}/release/bl2_tbb.bin

		python3 ${MANIFEST_GENERATION_KCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl31_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl31_key.pem -certout ${S}/build/${PLATFORM}/release/bl31-kcert.bin
		
		python3 ${MANIFEST_GENERATION_CCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl31_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl31_key.pem -imgin ${S}/build/${PLATFORM}/release/bl31.bin \
			-certout ${S}/build/${PLATFORM}/release/bl31-ccert.bin -imgout ${S}/build/${PLATFORM}/release/bl31_tbb.bin

		if [ "${PMIC_SUPPORT}" = "1" ]; then
			python3 ${MANIFEST_GENERATION_KCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
				-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -certout ${PMIC_BUILD_DIR}/bl2-kcert_pmic.bin

			python3 ${MANIFEST_GENERATION_CCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl2_${IMG_AUTH_MODE}_info.xml \
				-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl2_key.pem -imgin ${PMIC_BUILD_DIR}/bl2.bin \
				-certout ${PMIC_BUILD_DIR}/bl2-ccert_pmic.bin -imgout ${PMIC_BUILD_DIR}/bl2_pmic_tbb.bin

			python3 ${MANIFEST_GENERATION_KCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl31_${IMG_AUTH_MODE}_info.xml \
				-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl31_key.pem -certout ${PMIC_BUILD_DIR}/bl31-kcert_pmic.bin
			
			python3 ${MANIFEST_GENERATION_CCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl31_${IMG_AUTH_MODE}_info.xml \
				-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl31_key.pem -imgin ${PMIC_BUILD_DIR}/bl31.bin \
				-certout ${PMIC_BUILD_DIR}/bl31-ccert_pmic.bin -imgout ${PMIC_BUILD_DIR}/bl31_pmic_tbb.bin
		fi
	fi
}

do_install_append () {

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		# install firmware images
		install -m 0644 ${S}/build/${PLATFORM}/release/bl2-kcert.bin  ${D}/boot/bl2-kcert-${MACHINE}.bin
		install -m 0644 ${S}/build/${PLATFORM}/release/bl2-ccert.bin  ${D}/boot/bl2-ccert-${MACHINE}.bin
		install -m 0644 ${S}/build/${PLATFORM}/release/bl2_tbb.bin    ${D}/boot/bl2-${MACHINE}_tbb.bin
		install -m 0644 ${S}/build/${PLATFORM}/release/bl31-kcert.bin ${D}/boot/bl31-kcert-${MACHINE}.bin
		install -m 0644 ${S}/build/${PLATFORM}/release/bl31-ccert.bin ${D}/boot/bl31-ccert-${MACHINE}.bin
		install -m 0644 ${S}/build/${PLATFORM}/release/bl31_tbb.bin   ${D}/boot/bl31-${MACHINE}_tbb.bin

		if [ "${PMIC_SUPPORT}" = "1" ]; then
			install -m 0644 ${PMIC_BUILD_DIR}/bl2-kcert_pmic.bin  ${D}/boot/bl2-kcert-${MACHINE}_pmic.bin
			install -m 0644 ${PMIC_BUILD_DIR}/bl2-ccert_pmic.bin  ${D}/boot/bl2-ccert-${MACHINE}_pmic.bin
			install -m 0644 ${PMIC_BUILD_DIR}/bl2_pmic_tbb.bin    ${D}/boot/bl2-${MACHINE}_pmic_tbb.bin
			install -m 0644 ${PMIC_BUILD_DIR}/bl31-kcert_pmic.bin ${D}/boot/bl31-kcert-${MACHINE}_pmic.bin
			install -m 0644 ${PMIC_BUILD_DIR}/bl31-ccert_pmic.bin ${D}/boot/bl31-ccert-${MACHINE}_pmic.bin
			install -m 0644 ${PMIC_BUILD_DIR}/bl31_pmic_tbb.bin   ${D}/boot/bl31-${MACHINE}_pmic_tbb.bin
		fi

		install -m 0644 ${S}/build/${PLATFORM}/release/root_of_trust_key_pk.hash ${D}/boot/root_of_trust_key_pk.hash
	fi
}
