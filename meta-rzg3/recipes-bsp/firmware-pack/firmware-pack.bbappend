require include/rzg2l-security-config.inc

DEPENDS = "trusted-firmware-a u-boot"
DEPENDS_append = " bptool-native fiptool-native"

DEPENDS_append = " \
        ${@oe.utils.conditional("ENABLE_SPD_OPTEE", "1", " optee-os secprv-native", "",d)} \
        ${@oe.utils.conditional("TRUSTED_BOARD_BOOT", "1", " secprv-native", "",d)} \
"

S = "${WORKDIR}/${BPN}-${PV}"

do_compile () {
	# Create bl2_bp.bin
	bptool ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin ${S}/bp.bin 0xA3000 spi
	cat ${S}/bp.bin ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin > ${S}/bl2_bp_spi.bin
	bptool ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin ${S}/bp.bin 0xA3000 mmc
	cat ${S}/bp.bin ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin > ${S}/bl2_bp_emmc.bin

	# Create fip.bin
	fiptool create --align 16 --soc-fw ${RECIPE_SYSROOT}/boot/bl31-${MACHINE}.bin --nt-fw ${RECIPE_SYSROOT}/boot/u-boot.bin ${S}/fip.bin

	if [ "${ENABLE_SPD_OPTEE}" = "1" ]; then
		fiptool update --align 16 --tos-fw ${RECIPE_SYSROOT}/boot/tee-${MACHINE}.bin ${S}/fip.bin
	fi
        
	# Convert to srec
	objcopy -I binary -O srec --adjust-vma=0xA1E00 --srec-forceS3 ${S}/bl2_bp_spi.bin ${S}/bl2_bp_spi.srec
	objcopy -I binary -O srec --adjust-vma=0xA1E00 --srec-forceS3 ${S}/bl2_bp_emmc.bin ${S}/bl2_bp_emmc.srec
	objcopy -I binary -O srec --adjust-vma=0x00000 --srec-forceS3 ${S}/fip.bin ${S}/fip.srec

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		objcopy -I binary --pad-to=0x00000400 \
			${RECIPE_SYSROOT}/boot/bl2-kcert-${MACHINE}.bin ${S}/bl2-kcert-${MACHINE}.bin
		objcopy -I binary --pad-to=0x00000C00 \
			${RECIPE_SYSROOT}/boot/bl2-ccert-${MACHINE}.bin ${S}/bl2-ccert-${MACHINE}.bin

		cat ${S}/bl2-kcert-${MACHINE}.bin ${S}/bl2-ccert-${MACHINE}.bin \
			${RECIPE_SYSROOT}/boot/bl2-${MACHINE}_tbb.bin > ${S}/bl2_tbb.bin

		bptool ${S}/bl2_tbb.bin ${S}/bp_spi.bin 0xA2000 spi
		cat ${S}/bp_spi.bin ${S}/bl2_tbb.bin > ${S}/bl2_bp_spi_tbb.bin
		bptool ${S}/bl2_tbb.bin ${S}/bp_mmc.bin 0xA2000 mmc
		cat ${S}/bp_mmc.bin ${S}/bl2_tbb.bin > ${S}/bl2_bp_mmc_tbb.bin

		fiptool create --align 16 --soc-fw ${RECIPE_SYSROOT}/boot/bl31-${MACHINE}_tbb.bin \
			--soc-fw-key-cert ${RECIPE_SYSROOT}/boot/bl31-kcert-${MACHINE}.bin \
			--soc-fw-cert ${RECIPE_SYSROOT}/boot/bl31-ccert-${MACHINE}.bin ${S}/fip_tbb.bin

		if [ "${ENABLE_SPD_OPTEE}" = "1" ]; then
			fiptool update --align 16 --tos-fw ${RECIPE_SYSROOT}/boot/tee-${MACHINE}_tbb.bin \
				--tos-fw-key-cert ${RECIPE_SYSROOT}/boot/bl32-kcert-${MACHINE}.bin \
				--tos-fw-cert ${RECIPE_SYSROOT}/boot/bl32-ccert-${MACHINE}.bin ${S}/fip_tbb.bin
		fi

		fiptool update --align 16 --nt-fw ${RECIPE_SYSROOT}/boot/u-boot-${MACHINE}_tbb.bin \
			--nt-fw-key-cert ${RECIPE_SYSROOT}/boot/bl33-kcert-${MACHINE}.bin \
			--nt-fw-cert ${RECIPE_SYSROOT}/boot/bl33-ccert-${MACHINE}.bin ${S}/fip_tbb.bin

		objcopy -I binary -O srec --adjust-vma=0x000A1E00 --srec-forceS3 ${S}/bl2_bp_spi_tbb.bin ${S}/bl2_bp_spi_tbb.srec
		objcopy -I binary -O srec --adjust-vma=0x000A1E00 --srec-forceS3 ${S}/bl2_bp_mmc_tbb.bin ${S}/bl2_bp_mmc_tbb.srec
		objcopy -I binary -O srec --adjust-vma=0x00000000 --srec-forceS3 ${S}/fip_tbb.bin ${S}/fip_tbb.srec
	fi
}

do_deploy () {
	# Create deploy folder
	install -d ${DEPLOYDIR}

	# Copy fip images
	install -m 0644  ${S}/bl2_bp_spi.bin ${DEPLOYDIR}/bl2_bp_spi-${MACHINE}.bin
	install -m 0644  ${S}/bl2_bp_spi.srec ${DEPLOYDIR}/bl2_bp_spi-${MACHINE}.srec
	install -m 0644  ${S}/bl2_bp_emmc.bin ${DEPLOYDIR}/bl2_bp_emmc-${MACHINE}.bin
	install -m 0644  ${S}/bl2_bp_emmc.srec ${DEPLOYDIR}/bl2_bp_emmc-${MACHINE}.srec

	install -m 0644  ${S}/fip.bin ${DEPLOYDIR}/fip-${MACHINE}.bin
	install -m 0644  ${S}/fip.srec ${DEPLOYDIR}/fip-${MACHINE}.srec

	if [ "${ENABLE_SPD_OPTEE}" = "1" ]; then
		split -b 900k fip.bin ${DEPLOYDIR}/fip-split1.bin
		mv ${DEPLOYDIR}/fip-split1.binaa ${DEPLOYDIR}/fip-split1.bin
		mv ${DEPLOYDIR}/fip-split1.binab ${DEPLOYDIR}/fip-split2.bin
		objcopy -I binary -O srec --adjust-vma=0x00000 --srec-forceS3 ${DEPLOYDIR}/fip-split1.bin ${DEPLOYDIR}/fip-split1.srec
		objcopy -I binary -O srec --adjust-vma=0x00000 --srec-forceS3 ${DEPLOYDIR}/fip-split2.bin ${DEPLOYDIR}/fip-split2.srec
	fi

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		# Copy fip trusted boot board images
		install -m 0644 ${S}/bl2_bp_spi_tbb.bin  ${DEPLOYDIR}/bl2_bp-${MACHINE}_spi_tbb.bin
		install -m 0644 ${S}/bl2_bp_spi_tbb.srec ${DEPLOYDIR}/bl2_bp-${MACHINE}_spi_tbb.srec
		install -m 0644 ${S}/bl2_bp_mmc_tbb.bin  ${DEPLOYDIR}/bl2_bp-${MACHINE}_mmc_tbb.bin
		install -m 0644 ${S}/bl2_bp_mmc_tbb.srec ${DEPLOYDIR}/bl2_bp-${MACHINE}_mmc_tbb.srec
		install -m 0644 ${S}/fip_tbb.bin     ${DEPLOYDIR}/fip-${MACHINE}_tbb.bin
		install -m 0644 ${S}/fip_tbb.srec    ${DEPLOYDIR}/fip-${MACHINE}_tbb.srec

		split -b 900k ${DEPLOYDIR}/fip-${MACHINE}_tbb.bin ${DEPLOYDIR}/fip-split1_tbb.bin
		mv ${DEPLOYDIR}/fip-split1_tbb.binaa ${DEPLOYDIR}/fip-split1_tbb.bin
		mv ${DEPLOYDIR}/fip-split1_tbb.binab ${DEPLOYDIR}/fip-split2_tbb.bin
		objcopy -I binary -O srec --adjust-vma=0x00000 --srec-forceS3 \
			${DEPLOYDIR}/fip-split1_tbb.bin ${DEPLOYDIR}/fip-split1_tbb.srec
		objcopy -I binary -O srec --adjust-vma=0x00000 --srec-forceS3 \
			${DEPLOYDIR}/fip-split2_tbb.bin ${DEPLOYDIR}/fip-split2_tbb.srec
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
