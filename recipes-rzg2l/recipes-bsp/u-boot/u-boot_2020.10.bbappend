require include/rzg2l-security-config.inc
inherit python3native

DEPENDS_append = " \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", "python3-pycryptodome-native python3-pycryptodomex-native secprv-native", "",d)} \
"

do_compile_append() {

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		python3 ${MANIFEST_GENERATION_KCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl33_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl33_key.pem -certout bl33-kcert.bin
		
		python3 ${MANIFEST_GENERATION_CCERT} -info ${DIRPATH_MANIFEST_GENTOOL}/info/bl33_${IMG_AUTH_MODE}_info.xml \
			-iskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/bl33_key.pem -imgin ${B}/${config}/u-boot.bin \
			-certout bl33-ccert.bin -imgout u-boot_tbb.bin
	fi
}

do_install_append() {

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		# install firmware images
		install -m 0644 ${B}/bl33-kcert.bin ${D}/boot/bl33-kcert-${MACHINE}.bin
		install -m 0644 ${B}/bl33-ccert.bin ${D}/boot/bl33-ccert-${MACHINE}.bin
		install -m 0644 ${B}/u-boot_tbb.bin ${D}/boot/u-boot-${MACHINE}_tbb.bin
	fi
}
