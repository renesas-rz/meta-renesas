SECTION = "bootloaders"
SUMMARY = "Firmware Packaging"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

inherit deploy

PACKAGE_ARCH = "${MACHINE_ARCH}"

DEPENDS = "trusted-firmware-a u-boot"
DEPENDS:append = " bptool-native"

SYSROOT_TFA="${RECIPE_SYSROOT}/firmware"

do_configure[noexec] = "1"
do_compile () {
	# Create bl2_bp.bin
	for bl2boot in ${BL2_BOOT_TARGET}; do
		# Create bl2_bp.bin
		bptool ${SYSROOT_TFA}/bl2.bin ${S}/bp.bin 0x08004000 $bl2boot
		cat ${S}/bp.bin ${SYSROOT_TFA}/bl2.bin > ${S}/bl2_bp_$bl2boot.bin

		# Conver BL2 to S-Record
		objcopy -I binary -O srec --adjust-vma=0x08003600 --srec-forceS3 ${S}/bl2_bp_$bl2boot.bin ${S}/bl2_bp_$bl2boot.srec
	done

	# Convert FIP to S-Record
	cp ${SYSROOT_TFA}/fip.bin ${S}/fip-${MACHINE}.bin
	objcopy -I binary -O srec --adjust-vma=0x08003600 --srec-forceS3 ${SYSROOT_TFA}/fip.bin ${S}/fip-${MACHINE}.srec
}

do_deploy () {
	# Create deploy folder
	install -d ${DEPLOYDIR}

	# Copy BL2 and FIP images
	for bl2boot in ${BL2_BOOT_TARGET}; do
		install -m 0644 ${S}/bl2_bp_$bl2boot.bin ${DEPLOYDIR}/bl2_bp_$bl2boot-${MACHINE}.bin
		install -m 0644 ${S}/bl2_bp_$bl2boot.srec ${DEPLOYDIR}/bl2_bp_$bl2boot-${MACHINE}.srec
	done
	install -m 0644 ${S}/fip-${MACHINE}.bin ${DEPLOYDIR}
	install -m 0644 ${S}/fip-${MACHINE}.srec ${DEPLOYDIR}
}

addtask deploy before do_build after do_compile
