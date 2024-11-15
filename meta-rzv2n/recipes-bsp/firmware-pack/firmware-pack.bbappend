DEPENDS = "trusted-firmware-a u-boot"
DEPENDS_append = " bptool-native fiptool-native"

do_compile () {
	# Create bl2_bp.bin
	bptool ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin ${S}/bp.bin 0x08103000 spi
	cat ${S}/bp.bin ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin > ${S}/bl2_bp_spi.bin

	bptool ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin ${S}/bp.bin 0x08103000 esd
	cat ${S}/bp.bin ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin > ${S}/bl2_bp_esd.bin

	bptool ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin ${S}/bp.bin 0x08103000 mmc
	cat ${S}/bp.bin ${RECIPE_SYSROOT}/boot/bl2-${MACHINE}.bin > ${S}/bl2_bp_mmc.bin

	# Create fip.bin
	fiptool create --align 16 --soc-fw ${RECIPE_SYSROOT}/boot/bl31-${MACHINE}.bin \
		--nt-fw ${RECIPE_SYSROOT}/boot/u-boot.bin ${S}/fip.bin

	# Convert to srec
	objcopy -I binary -O srec --adjust-vma=0x08101E00 --srec-forceS3 ${S}/bl2_bp_spi.bin ${S}/bl2_bp_spi.srec
	objcopy -I binary -O srec --adjust-vma=0x08101E00 --srec-forceS3 ${S}/bl2_bp_esd.bin ${S}/bl2_bp_esd.srec
	objcopy -I binary -O srec --adjust-vma=0x08101E00 --srec-forceS3 ${S}/bl2_bp_mmc.bin ${S}/bl2_bp_mmc.srec

	objcopy -I binary -O srec --adjust-vma=0x0000 --srec-forceS3 ${S}/fip.bin ${S}/fip.srec
}

do_deploy () {
	# Create deploy folder
	install -d ${DEPLOYDIR}

	# Copy BL2 and fip images
	install -m 0644  ${S}/bl2_bp_spi.bin ${DEPLOYDIR}/bl2_bp_spi-${MACHINE}.bin
	install -m 0644  ${S}/bl2_bp_spi.srec ${DEPLOYDIR}/bl2_bp_spi-${MACHINE}.srec

	install -m 0644  ${S}/bl2_bp_esd.bin ${DEPLOYDIR}/bl2_bp_esd-${MACHINE}.bin
	install -m 0644  ${S}/bl2_bp_esd.srec ${DEPLOYDIR}/bl2_bp_esd-${MACHINE}.srec

	install -m 0644  ${S}/bl2_bp_mmc.bin ${DEPLOYDIR}/bl2_bp_mmc-${MACHINE}.bin
	install -m 0644  ${S}/bl2_bp_mmc.srec ${DEPLOYDIR}/bl2_bp_mmc-${MACHINE}.srec

	install -m 0644  ${S}/fip.bin ${DEPLOYDIR}/fip-${MACHINE}.bin
	install -m 0644  ${S}/fip.srec ${DEPLOYDIR}/fip-${MACHINE}.srec
}
