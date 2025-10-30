SECTION = "bootloaders"
SUMMARY = "Firmware Packaging"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

inherit deploy

PACKAGE_ARCH = "${MACHINE_ARCH}"

DEPENDS = "trusted-firmware-a u-boot"
DEPENDS:append = " bptool-native"
DEPENDS:append:rzt2h-family = " parameter-block-generator-native"

SYSROOT_TFA="${RECIPE_SYSROOT}/firmware"

do_configure[noexec] = "1"
do_compile () {
	# Create bl2_bp.bin
	for bl2boot in ${BL2_BOOT_TARGET}; do
		# Create bl2_bp.bin
		bptool ${SYSROOT_TFA}/bl2.bin ${S}/bp.bin ${BL2_BASE_ADDR} $bl2boot
		cat ${S}/bp.bin ${SYSROOT_TFA}/bl2.bin > ${S}/bl2_bp_$bl2boot.bin

		# Conver BL2 to S-Record
		objcopy -I binary -O srec --adjust-vma=${BL2_ADJUST_VMA} --srec-forceS3 ${S}/bl2_bp_$bl2boot.bin ${S}/bl2_bp_$bl2boot.srec
	done

	# Convert FIP to S-Record
	cp ${SYSROOT_TFA}/fip.bin ${S}/fip-${MACHINE}.bin
	objcopy -I binary -O srec --adjust-vma=${FIP_ADJUST_VMA} --srec-forceS3 ${SYSROOT_TFA}/fip.bin ${S}/fip-${MACHINE}.srec

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		# Create bl2_bp.bin
		for bl2boot in ${BL2_BOOT_TARGET}; do
			# Create bl2_bp.bin
			bptool ${SYSROOT_TFA}/bl2-${TFA_PLATFORM}_pmic.bin ${S}/bp-${TFA_PLATFORM}_pmic.bin ${BL2_BASE_ADDR} $bl2boot
			cat ${S}/bp-${TFA_PLATFORM}_pmic.bin ${SYSROOT_TFA}/bl2-${TFA_PLATFORM}_pmic.bin > ${S}/bl2_bp_${bl2boot}_pmic.bin

			# Conver BL2 to S-Record
			objcopy -I binary -O srec --adjust-vma=${BL2_ADJUST_VMA} --srec-forceS3 ${S}/bl2_bp_${bl2boot}_pmic.bin ${S}/bl2_bp_${bl2boot}_pmic.srec
		done

		# Convert FIP to S-Record
		cp ${SYSROOT_TFA}/fip-${TFA_PLATFORM}_pmic.bin ${S}/fip-${MACHINE}_pmic.bin
		objcopy -I binary -O srec --adjust-vma=${FIP_ADJUST_VMA} --srec-forceS3 ${SYSROOT_TFA}/fip-${TFA_PLATFORM}_pmic.bin ${S}/fip-${MACHINE}_pmic.srec
	fi
}

do_compile:rzt2h-family() {
	BL2_FILE="${SYSROOT_TFA}/bl2.bin"
	# Get BL2 filesize and align to 0x200 (512) bytes
	BL2_SIZE=$(wc -c < "${BL2_FILE}")
	BL2_SIZE=$(expr "${BL2_SIZE}" + 511)
	BL2_SIZE=$(expr "${BL2_SIZE}" / 512)
	BL2_SIZE=$(expr "${BL2_SIZE}" \* 512)
	BL2_SIZE_HEX=$(printf "0x%08x" "${BL2_SIZE}")

	for bl2boot in ${BL2_BOOT_TARGET}; do
		case "$bl2boot" in
			xspi0) loader_addr="${LOADER_ADDR_xspi0}" ;;
			xspi1) loader_addr="${LOADER_ADDR_xspi1}" ;;
			emmc)  loader_addr="${LOADER_ADDR_emmc}"  ;;
			esd)   loader_addr="${LOADER_ADDR_esd}"   ;;
			*) bbwarn "Unknown target $bl2boot"; continue ;;
		esac

		set -- \
			--output="${S}/bp_${bl2boot}.bin" \
			--cache_flag=1 \
			--loader_addr="${loader_addr}" \
			--loader_size="${BL2_SIZE_HEX}" \
			--dest_addr="${DEST_ADDR}" \
			--pll0_ssc_ctr_v="${PLL0_SSC_CTR_V}" \
			--bootcpu_flg="${BOOTCPU_FLG}"

		# Add XSPI-specific argument for xspi0/xspi1
		if [ "$bl2boot" = "xspi0" ] || [ "$bl2boot" = "xspi1" ]; then
			set -- "$@" --xspi_cssctl_v="${XSPI_CSSCTL_V}"
		fi

		# Execute parameter-block-gen with all built arguments
		parameter-block-gen "$@"

		cat ${S}/bp_$bl2boot.bin ${BL2_FILE} > ${S}/bl2_bp_$bl2boot.bin

		if [ "$bl2boot" = "esd" ]; then
			#BL2 with seven copies of eSD Boot parameters
			cat ${S}/bp_$bl2boot.bin ${S}/bp_$bl2boot.bin ${S}/bp_$bl2boot.bin ${S}/bp_$bl2boot.bin ${S}/bp_$bl2boot.bin ${S}/bp_$bl2boot.bin ${S}/bp_$bl2boot.bin ${BL2_FILE} > ${S}/bl2_bp_$bl2boot.bin
		fi

		objcopy -I binary -O srec --adjust-vma=${BL2_ADJUST_VMA} --srec-forceS3 ${S}/bl2_bp_$bl2boot.bin ${S}/bl2_bp_$bl2boot.srec
	done

	# Convert FIP to S-Record
	cp ${SYSROOT_TFA}/fip.bin ${S}/fip-${MACHINE}.bin
	objcopy -I binary -O srec --adjust-vma=${FIP_ADJUST_VMA} --srec-forceS3 ${SYSROOT_TFA}/fip.bin ${S}/fip-${MACHINE}.srec
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

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		# Copy BL2 and FIP images
		for bl2boot in ${BL2_BOOT_TARGET}; do
			install -m 0644 ${S}/bl2_bp_${bl2boot}_pmic.bin ${DEPLOYDIR}/bl2_bp_${bl2boot}-${MACHINE}_pmic.bin
			install -m 0644 ${S}/bl2_bp_${bl2boot}_pmic.srec ${DEPLOYDIR}/bl2_bp_${bl2boot}-${MACHINE}_pmic.srec
		done

		install -m 0644 ${S}/fip-${MACHINE}_pmic.bin ${DEPLOYDIR}
		install -m 0644 ${S}/fip-${MACHINE}_pmic.srec ${DEPLOYDIR}
	fi
}

addtask deploy before do_build after do_compile
