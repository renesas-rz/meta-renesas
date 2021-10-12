SECTION = "bootloaders"
SUMMARY = "Trusted Firmware-A for RZ/G2L"
LICENSE = "BSD-3-Clause"

inherit deploy

#DEPENDS = "bootparameter-native u-boot fiptool-native"
#DEPENDS = " u-boot"

S = "${WORKDIR}/git"

COMPATIBLE_MACHINE = "(smarc-rzg2l|rzg2l-dev|smarc-rzg2lc|rzg2lc-dev)"

PLATFORM ?= "g2l"
PLATFORM_smarc-rzg2l = "g2l"
EXTRA_FLAGS_smarc-rzg2l = "BOARD=smarc_2"
PMIC_EXTRA_FLAGS_smarc-rzg2l = "BOARD=smarc_pmic_2"
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

PMIC_BUILD_DIR = "${S}/build_pmic"

# Requires CROSS_COMPILE set by hand as there is no configure script
export CROSS_COMPILE="${TARGET_PREFIX}"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

# No configure
do_configure[noexec] = "1"

FILES_${PN} = "/boot "
SYSROOT_DIRS += "/boot"

do_compile () {
	# Build TF-A
	oe_runmake PLAT=${PLATFORM} ${EXTRA_FLAGS} bl2 bl31

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		oe_runmake PLAT=${PLATFORM} ${PMIC_EXTRA_FLAGS} BUILD_PLAT=${PMIC_BUILD_DIR} bl2 bl31
	fi
}

do_install () { 
	install -d ${D}/boot 
	install -m 644 ${S}/build/${PLATFORM}/release/bl2.bin ${D}/boot/bl2-${MACHINE}.bin
	install -m 644 ${S}/build/${PLATFORM}/release/bl31.bin ${D}/boot/bl31-${MACHINE}.bin

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${D}/boot/bl2-${MACHINE}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${D}/boot/bl31-${MACHINE}_pmic.bin
	fi
}

do_deploy () {
	# Create deploy folder
	install -d ${DEPLOYDIR}

	# Copy IPL
	install -m 0644 ${S}/build/${PLATFORM}/release/bl2/bl2.elf ${DEPLOYDIR}/bl2-${MACHINE}.elf
	install -m 0644 ${S}/build/${PLATFORM}/release/bl2.bin ${DEPLOYDIR}/bl2-${MACHINE}.bin
	install -m 0644 ${S}/build/${PLATFORM}/release/bl31/bl31.elf ${DEPLOYDIR}/bl31-${MACHINE}.elf
	install -m 0644 ${S}/build/${PLATFORM}/release/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}.bin

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${DEPLOYDIR}/bl2-${MACHINE}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}_pmic.bin
	fi
}

addtask deploy before do_build after do_compile
