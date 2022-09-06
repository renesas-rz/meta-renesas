require include/rzg2l-security-config.inc

DEPENDS_append = " \
	${@oe.utils.conditional("ENABLE_SPD_OPTEE", "1", " optee-os secprv-native", "",d)} \
	${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", " secprv-native", "",d)} \
"

do_compile_append () {

	if [ "${ENABLE_SPD_OPTEE}" = "1" ]; then
		fiptool update --align 16 --tos-fw ${STAGING_DIR_HOST}/boot/tee-${MACHINE}.bin fip.bin
		objcopy -I binary -O srec --adjust-vma=0x0000 --srec-forceS3 fip.bin fip.srec

		if [ "${PMIC_SUPPORT}" = "1" ]; then
			fiptool update --align 16 --tos-fw ${STAGING_DIR_HOST}/boot/tee-${MACHINE}.bin fip_pmic.bin
			objcopy -I binary -O srec --adjust-vma=0x0000 --srec-forceS3 fip_pmic.bin fip_pmic.srec
		fi
	fi


	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		objcopy -I binary --adjust-vma=0x00012000 --pad-to=0x12400 ${STAGING_DIR_HOST}/boot/bl2-kcert-${MACHINE}.bin bl2-kcert-${MACHINE}.bin
		objcopy -I binary --adjust-vma=0x00012400 --pad-to=0x13000 ${STAGING_DIR_HOST}/boot/bl2-ccert-${MACHINE}.bin bl2-ccert-${MACHINE}.bin

		cat bl2-kcert-${MACHINE}.bin bl2-ccert-${MACHINE}.bin ${STAGING_DIR_HOST}/boot/bl2-${MACHINE}_tbb.bin > bl2_tbb.bin

		bootparameter bl2_tbb.bin ${S}/bl2_bp_tbb.bin

		cat bl2_tbb.bin >> ${S}/bl2_bp_tbb.bin

		fiptool create --align 16 --soc-fw ${STAGING_DIR_HOST}/boot/bl31-${MACHINE}_tbb.bin --soc-fw-key-cert ${STAGING_DIR_HOST}/boot/bl31-kcert-${MACHINE}.bin --soc-fw-cert ${STAGING_DIR_HOST}/boot/bl31-ccert-${MACHINE}.bin ${S}/fip_tbb.bin

		if [ "${ENABLE_SPD_OPTEE}" = "1" ]; then
			fiptool update --align 16 --tos-fw ${STAGING_DIR_HOST}/boot/tee-${MACHINE}_tbb.bin --tos-fw-key-cert ${STAGING_DIR_HOST}/boot/bl32-kcert-${MACHINE}.bin --tos-fw-cert ${STAGING_DIR_HOST}/boot/bl32-ccert-${MACHINE}.bin ${S}/fip_tbb.bin
		fi

		fiptool update --align 16 --nt-fw ${STAGING_DIR_HOST}/boot/u-boot-${MACHINE}_tbb.bin --nt-fw-key-cert ${STAGING_DIR_HOST}/boot/bl33-kcert-${MACHINE}.bin --nt-fw-cert ${STAGING_DIR_HOST}/boot/bl33-ccert-${MACHINE}.bin ${S}/fip_tbb.bin

		objcopy -O srec --adjust-vma=0x00011E00 --srec-forceS3 -I binary ${S}/bl2_bp_tbb.bin ${S}/bl2_bp_tbb.srec
		objcopy -I binary -O srec --adjust-vma=0x0000 --srec-forceS3 ${S}/fip_tbb.bin ${S}/fip_tbb.srec

		if [ "${PMIC_SUPPORT}" = "1" ]; then
			
			objcopy -I binary --adjust-vma=0x00012000 --pad-to=0x12400 ${STAGING_DIR_HOST}/boot/bl2-kcert-${MACHINE}_pmic.bin bl2-kcert-${MACHINE}_pmic.bin
			objcopy -I binary --adjust-vma=0x00012400 --pad-to=0x13000 ${STAGING_DIR_HOST}/boot/bl2-ccert-${MACHINE}_pmic.bin bl2-ccert-${MACHINE}_pmic.bin

			cat bl2-kcert-${MACHINE}_pmic.bin bl2-ccert-${MACHINE}_pmic.bin ${STAGING_DIR_HOST}/boot/bl2-${MACHINE}_pmic_tbb.bin > bl2_pmic_tbb.bin

			bootparameter bl2_pmic_tbb.bin ${S}/bl2_bp_pmic_tbb.bin

			cat bl2_pmic_tbb.bin >> ${S}/bl2_bp_pmic_tbb.bin

			cp ${S}/fip_tbb.bin ${S}/fip_pmic_tbb.bin
			
			fiptool update --align 16 --soc-fw ${STAGING_DIR_HOST}/boot/bl31-${MACHINE}_pmic_tbb.bin --soc-fw-key-cert ${STAGING_DIR_HOST}/boot/bl31-kcert-${MACHINE}_pmic.bin --soc-fw-cert ${STAGING_DIR_HOST}/boot/bl31-ccert-${MACHINE}_pmic.bin ${S}/fip_pmic_tbb.bin

			objcopy -O srec --adjust-vma=0x00011E00 --srec-forceS3 -I binary ${S}/bl2_bp_pmic_tbb.bin ${S}/bl2_bp_pmic_tbb.srec
			objcopy -I binary -O srec --adjust-vma=0x0000 --srec-forceS3 ${S}/fip_pmic_tbb.bin ${S}/fip_pmic_tbb.srec
		fi
	fi
}

do_deploy_append () {

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		# Copy fip trusted boot board images
		install -m 0644 ${S}/bl2_bp_tbb.bin  ${DEPLOYDIR}/bl2_bp-${MACHINE}_tbb.bin
		install -m 0644 ${S}/bl2_bp_tbb.srec ${DEPLOYDIR}/bl2_bp-${MACHINE}_tbb.srec
		install -m 0644 ${S}/fip_tbb.bin     ${DEPLOYDIR}/fip-${MACHINE}_tbb.bin
		install -m 0644 ${S}/fip_tbb.srec    ${DEPLOYDIR}/fip-${MACHINE}_tbb.srec

		if [ "${PMIC_SUPPORT}" = "1" ]; then
			install -m 0644 ${S}/bl2_bp_pmic_tbb.bin  ${DEPLOYDIR}/bl2_bp-${MACHINE}_pmic_tbb.bin
			install -m 0644 ${S}/bl2_bp_pmic_tbb.srec ${DEPLOYDIR}/bl2_bp-${MACHINE}_pmic_tbb.srec
			install -m 0644 ${S}/fip_pmic_tbb.bin     ${DEPLOYDIR}/fip-${MACHINE}_pmic_tbb.bin
			install -m 0644 ${S}/fip_pmic_tbb.srec    ${DEPLOYDIR}/fip-${MACHINE}_pmic_tbb.srec
		fi
	fi

	if [ -d "${SYMLINK_NATIVE_BOOT_KEY_DIR}" ]; then
		# Copy install keys
		install -d ${S}/user_factory_prog
		install -m 0644 ${SYMLINK_NATIVE_BOOT_KEY_DIR}/encrypted-*.bin     ${S}/user_factory_prog
		install -m 0644 ${SYMLINK_NATIVE_BOOT_KEY_DIR}/kuk_init_vec.txt    ${S}/user_factory_prog
		install -m 0644 ${SYMLINK_NATIVE_PROV_KEY_DIR}/ufpk_init_vec.bin   ${S}/user_factory_prog

		if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		install -m 0644 ${STAGING_DIR_HOST}/boot/root_of_trust_key_pk.hash ${S}/user_factory_prog
		fi

		cd ${S}/user_factory_prog
		tar zcvf ${S}/user_factory_prog-${MACHINE}.tar.gz *
		install -m 0644 ${S}/user_factory_prog-${MACHINE}.tar.gz ${DEPLOYDIR}/
	fi

	if [ -d "${SYMLINK_NATIVE_BOOT_KEY_DIR}/user_keys" ]; then
		install -d ${S}/sce_enc_oem_key
		install -m 0644 ${SYMLINK_NATIVE_BOOT_KEY_DIR}/user_keys/encrypted-*.bin ${S}/sce_enc_oem_key
		
		if [ -n "$(ls ${S}/sce_enc_oem_key)" ]; then
			cd ${S}
			tar zcvf sce_enc_oem_key_${MACHINE}.tar.gz sce_enc_oem_key
			install -m 0644 ${S}/sce_enc_oem_key_${MACHINE}.tar.gz ${DEPLOYDIR}/
		fi
	fi
}
