SECTION = "bootloaders"
SUMMARY = "Firmware Packaging"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

inherit deploy

DEPENDS = "trusted-firmware-a u-boot"
DEPENDS += " bootparameter-native fiptool-native"

S = "${WORKDIR}"

do_configure[noexec] = "1"

do_compile () {

	# Create bl2_bp.bin
	bootparameter ${WORKDIR}/recipe-sysroot/boot/bl2-${MACHINE}.bin bl2_bp.bin
	# Add for eSD boot image
	cp bl2_bp.bin bl2_bp_esd.bin

	cat ${WORKDIR}/recipe-sysroot/boot/bl2-${MACHINE}.bin >> bl2_bp.bin

	# Create fip.bin
	fiptool create --align 16 --soc-fw ${WORKDIR}/recipe-sysroot/boot/bl31-${MACHINE}.bin --nt-fw ${WORKDIR}/recipe-sysroot/boot/u-boot.bin fip.bin

	# Convert to srec
	objcopy -O srec --adjust-vma=0x00011E00 --srec-forceS3 -I binary bl2_bp.bin bl2_bp.srec
	objcopy -I binary -O srec --adjust-vma=0x0000 --srec-forceS3 fip.bin fip.srec

        if [ "${PMIC_SUPPORT}" = "1" ]; then
		bootparameter ${WORKDIR}/recipe-sysroot/boot/bl2-${MACHINE}_pmic.bin bl2_bp_pmic.bin
		# Add for eSD boot image
		cp bl2_bp_pmic.bin bl2_bp_esd_pmic.bin

		cat ${WORKDIR}/recipe-sysroot/boot/bl2-${MACHINE}_pmic.bin >> bl2_bp_pmic.bin
		fiptool create --align 16 --soc-fw ${WORKDIR}/recipe-sysroot/boot/bl31-${MACHINE}_pmic.bin --nt-fw ${WORKDIR}/recipe-sysroot/boot/u-boot.bin fip_pmic.bin
		objcopy -O srec --adjust-vma=0x00011E00 --srec-forceS3 -I binary bl2_bp_pmic.bin bl2_bp_pmic.srec
		objcopy -I binary -O srec --adjust-vma=0x0000 --srec-forceS3 fip_pmic.bin fip_pmic.srec
	fi

}

do_deploy () {
	# Create deploy folder
	install -d ${DEPLOYDIR}

	# Copy fip images
	install -m 0644 ${S}/bl2_bp.bin ${DEPLOYDIR}/bl2_bp-${MACHINE}.bin
	install -m 0644 ${S}/bl2_bp.srec ${DEPLOYDIR}/bl2_bp-${MACHINE}.srec
	install -m 0644 ${S}/fip.bin ${DEPLOYDIR}/fip-${MACHINE}.bin
	install -m 0644 ${S}/fip.srec ${DEPLOYDIR}/fip-${MACHINE}.srec

	# Copy fip image for eSD boot
	install -m 0644 ${S}/bl2_bp_esd.bin ${DEPLOYDIR}/bl2_bp_esd-${MACHINE}.bin

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 0644 ${S}/bl2_bp_pmic.bin ${DEPLOYDIR}/bl2_bp-${MACHINE}_pmic.bin
		install -m 0644 ${S}/bl2_bp_pmic.srec ${DEPLOYDIR}/bl2_bp-${MACHINE}_pmic.srec
		install -m 0644 ${S}/fip_pmic.bin ${DEPLOYDIR}/fip-${MACHINE}_pmic.bin
		install -m 0644 ${S}/fip_pmic.srec ${DEPLOYDIR}/fip-${MACHINE}_pmic.srec

		# Copy fip image for eSD boot
		install -m 0644 ${S}/bl2_bp_esd_pmic.bin ${DEPLOYDIR}/bl2_bp_esd-${MACHINE}_pmic.bin
	fi
}

addtask deploy before do_build after do_compile
