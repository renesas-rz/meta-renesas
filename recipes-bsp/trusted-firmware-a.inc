SECTION = "bootloaders"
SUMMARY = "Trusted Firmware-A for RZ/G2L"
LICENSE = "BSD-3-Clause"

inherit deploy

DEPENDS = "bootparameter-native u-boot fiptool-native"

S = "${WORKDIR}/git"

COMPATIBLE_MACHINE = "(smarc-rzg2l|rzg2l-dev|smarc-rzg2lc|rzg2lc-dev)"

PLATFORM ?= "g2l"
PLATFORM_smarc-rzg2l = "g2l"
EXTRA_FLAGS_smarc-rzg2l = "BOARD=smarc_2"
FLASH_ADDRESS_BL2_BP_smarc-rzg2l = "00000"
FLASH_ADDRESS_FIP_smarc-rzg2l = "1D200"

PLATFORM_rzg2l-dev = "g2l"
EXTRA_FLAGS_rzg2l-dev = "BOARD=dev15_4"
FLASH_ADDRESS_BL2_BP_rzg2l-dev = "00000"
FLASH_ADDRESS_FIP_rzg2l-dev = "1D200"

PLATFORM_rzg2lc-dev = "g2l"
EXTRA_FLAGS_rzg2lc-dev = "BOARD=dev13_1"
FLASH_ADDRESS_BL2_BP_rzg2lc-dev = "00000"
FLASH_ADDRESS_FIP_rzg2lc-dev = "1D200"

# Temporarily use same config with RZ/G2LC Dev board
PLATFORM_smarc-rzg2lc = "g2lc"
EXTRA_FLAGS_smarc-rzg2lc = "BOARD=dev13_1"
FLASH_ADDRESS_BL2_BP_smarc-rzg2lc = "00000"
FLASH_ADDRESS_FIP_smarc-rzg2lc = "1D200"

# Requires CROSS_COMPILE set by hand as there is no configure script
export CROSS_COMPILE="${TARGET_PREFIX}"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

# No configure
do_configure[noexec] = "1"

do_compile () {
	# Build TF-A
	oe_runmake PLAT=${PLATFORM} ${EXTRA_FLAGS} bl2 bl31

	# Create bl2_bp.bin
	bootparameter build/${PLATFORM}/release/bl2.bin bl2_bp.bin
	cat build/${PLATFORM}/release/bl2.bin >> bl2_bp.bin

	# Create fip.bin
	fiptool create --align 16 --soc-fw build/${PLATFORM}/release/bl31.bin --nt-fw ${WORKDIR}/recipe-sysroot/boot/u-boot.bin fip.bin

	# Convert to srec
	objcopy -O srec --adjust-vma=0x00011E00 --srec-forceS3 -I binary bl2_bp.bin bl2_bp.srec
	objcopy -I binary -O srec --adjust-vma=0x0000 --srec-forceS3 fip.bin fip.srec

	PROGRAM_SIZE_BL2_BP=$(printf "%x" `wc -c < bl2_bp.bin`)
	PROGRAM_SIZE_FIP=$(printf "%x" `wc -c < fip.bin`)
}

do_deploy () {
	# Create deploy folder
	install -d ${DEPLOYDIR}

	# Copy IPL
	install -m 0644 ${S}/build/${PLATFORM}/release/bl2/bl2.elf ${DEPLOYDIR}/bl2-${MACHINE}.elf
	install -m 0644 ${S}/build/${PLATFORM}/release/bl2.bin ${DEPLOYDIR}/bl2-${MACHINE}.bin
	install -m 0644 ${S}/build/${PLATFORM}/release/bl31/bl31.elf ${DEPLOYDIR}/bl31-${MACHINE}.elf
	install -m 0644 ${S}/build/${PLATFORM}/release/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}.bin

	# Copy fip images
	install -m 0644 ${S}/bl2_bp.bin ${DEPLOYDIR}/bl2_bp-${MACHINE}.bin
	install -m 0644 ${S}/bl2_bp.srec ${DEPLOYDIR}/bl2_bp-${MACHINE}.srec
	install -m 0644 ${S}/fip.bin ${DEPLOYDIR}/fip-${MACHINE}.bin
	install -m 0644 ${S}/fip.srec ${DEPLOYDIR}/fip-${MACHINE}.srec
}

addtask deploy before do_build after do_compile
