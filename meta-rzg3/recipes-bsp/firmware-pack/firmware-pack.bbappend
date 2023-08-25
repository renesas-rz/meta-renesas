DEPENDS = " \
	trusted-firmware-a u-boot \
	${@oe.utils.conditional("ENABLE_SPD_OPTEE", "1", " optee-os", "",d)} \
"
DEPENDS_append = " bptool-native fiptool-native"

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
}
