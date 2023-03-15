require include/rzg2l-security-config.inc
inherit python3native

# For RZ/G2L Series
PLATFORM_smarc-rzg2l = "g2l"
EXTRA_FLAGS_smarc-rzg2l = "BOARD=smarc_2"
PMIC_EXTRA_FLAGS_smarc-rzg2l = "BOARD=smarc_pmic_2"
FLASH_ADDRESS_BL2_BP_smarc-rzg2l = "00000"
FLASH_ADDRESS_FIP_smarc-rzg2l = "1D200"

PLATFORM_rzg2l-dev = "g2l"
EXTRA_FLAGS_rzg2l-dev = "BOARD=dev15_4"
FLASH_ADDRESS_BL2_BP_rzg2l-dev = "00000"
FLASH_ADDRESS_FIP_rzg2l-dev = "1D200"

PLATFORM_smarc-rzg2lc = "g2l"
EXTRA_FLAGS_smarc-rzg2lc = "BOARD=smarc_1"
FLASH_ADDRESS_BL2_BP_smarc-rzg2lc = "00000"
FLASH_ADDRESS_FIP_smarc-rzg2lc = "1D200"

PLATFORM_rzg2lc-dev = "g2l"
EXTRA_FLAGS_rzg2lc-dev = "BOARD=dev13_1"
FLASH_ADDRESS_BL2_BP_rzg2lc-dev = "00000"
FLASH_ADDRESS_FIP_rzg2lc-dev = "1D200"

PLATFORM_smarc-rzg2ul = "g2ul"
EXTRA_FLAGS_smarc-rzg2ul = "BOARD=g2ul_smarc SOC_TYPE=1 SPI_FLASH=AT25QL128A"
FLASH_ADDRESS_BL2_BP_smarc-rzg2ul = "00000"
FLASH_ADDRESS_FIP_smarc-rzg2ul = "1D200"

PLATFORM_rzg2ul-dev = "g2ul"
EXTRA_FLAGS_rzg2ul-dev = "BOARD=g2ul_type1_ddr4_dev SOC_TYPE=1"
FLASH_ADDRESS_BL2_BP_rzg2ul-dev = "00000"
FLASH_ADDRESS_FIP_rzg2ul-dev = "1D200"

PLATFORM_smarc-rzv2l = "v2l"
EXTRA_FLAGS_smarc-rzv2l = "BOARD=smarc_4"
PMIC_EXTRA_FLAGS_smarc-rzv2l = "BOARD=smarc_pmic_2"
FLASH_ADDRESS_BL2_BP_smarc-rzv2l = "00000"
FLASH_ADDRESS_FIP_smarc-rzv2l = "1D200"

PLATFORM_rzv2l-dev = "v2l"
EXTRA_FLAGS_rzv2l-dev = "BOARD=dev15_4"
FLASH_ADDRESS_BL2_BP_rzv2l-dev = "00000"
FLASH_ADDRESS_FIP_rzv2l-dev = "1D200"

PMIC_BUILD_DIR = "${S}/build_pmic"

FILES_${PN} = "/boot "
SYSROOT_DIRS += "/boot"

DEPENDS_append = " \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", "python3-pycryptodome-native python3-pycryptodomex-native secprv-native", "",d)} \
"

SEC_FLAGS = " \
	${@oe.utils.conditional("ENABLE_SPD_OPTEE", "1", " SPD=opteed", "",d)} \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", " TRUSTED_BOARD_BOOT=1 COT=tbbr", "",d)} \
"
EXTRA_FLAGS_append += "${SEC_FLAGS}"
PMIC_EXTRA_FLAGS_append += "${SEC_FLAGS}"

FILESEXTRAPATHS_append := "${THISDIR}/files"
SRC_URI += " \
	file://0001-plat-renesas-rz-Disable-unused-CRYPTO_SUPPORT.patch \
"

do_compile() {
	oe_runmake PLAT=${PLATFORM} ${EXTRA_FLAGS} bl2 bl31

	if [ "${PMIC_SUPPORT}" = "1" ]; then
	oe_runmake PLAT=${PLATFORM} ${PMIC_EXTRA_FLAGS} BUILD_PLAT=${PMIC_BUILD_DIR} bl2 bl31
	fi

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

do_install() {
	install -d ${D}/boot
	install -m 644 ${S}/build/${PLATFORM}/release/bl2.bin ${D}/boot/bl2-${MACHINE}.bin
	install -m 644 ${S}/build/${PLATFORM}/release/bl31.bin ${D}/boot/bl31-${MACHINE}.bin

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${D}/boot/bl2-${MACHINE}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${D}/boot/bl31-${MACHINE}_pmic.bin
	fi

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

do_deploy_append() {
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${DEPLOYDIR}/bl2-${MACHINE}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}_pmic.bin
	fi
}
