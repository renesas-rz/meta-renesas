require include/rzg2l-optee-config.inc

# For RZ/G2L Series
PLATFORM_smarc-rzg2l = "g2l"
EXTRA_FLAGS_smarc-rzg2l = "BOARD=smarc_2"
PMIC_EXTRA_FLAGS_smarc-rzg2l = "BOARD=smarc_pmic_2"

PLATFORM_rzg2l-dev = "g2l"
EXTRA_FLAGS_rzg2l-dev = "BOARD=dev15_4"

PLATFORM_smarc-rzg2lc = "g2l"
EXTRA_FLAGS_smarc-rzg2lc = "BOARD=smarc_1"

PLATFORM_rzg2lc-dev = "g2l"
EXTRA_FLAGS_rzg2lc-dev = "BOARD=dev13_1"

PLATFORM_smarc-rzg2ul = "g2ul"
EXTRA_FLAGS_smarc-rzg2ul = "BOARD=g2ul_smarc SOC_TYPE=1 SPI_FLASH=AT25QL128A"

PLATFORM_rzg2ul-dev = "g2ul"
EXTRA_FLAGS_rzg2ul-dev = "BOARD=g2ul_type1_ddr4_dev SOC_TYPE=1"

PLATFORM_smarc-rzv2l = "v2l"
EXTRA_FLAGS_smarc-rzv2l = "BOARD=smarc_4"
PMIC_EXTRA_FLAGS_smarc-rzv2l = "BOARD=smarc_pmic_2"

PLATFORM_rzv2l-dev = "v2l"
EXTRA_FLAGS_rzv2l-dev = "BOARD=dev15_4"

PMIC_BUILD_DIR = "${S}/build_pmic"

FILES_${PN} = "/boot "
SYSROOT_DIRS += "/boot"

SEC_FLAGS = " \
	${@oe.utils.conditional("ENABLE_SPD_OPTEE", "1", " SPD=opteed", "",d)} \
"

EXTRA_FLAGS_append += "${SEC_FLAGS}"
PMIC_EXTRA_FLAGS_append += "${SEC_FLAGS}"

FILESEXTRAPATHS_append := "${THISDIR}/files"
SRC_URI += " \
	file://0001-plat-renesas-rz-Disable-unused-CRYPTO_SUPPORT.patch \
"

ECC_FLAGS = " DDR_ECC_ENABLE=1 "
ECC_FLAGS += "${@oe.utils.conditional("ECC_MODE", "ERR_DETECT", "DDR_ECC_DETECT=1", "",d)}"
ECC_FLAGS += "${@oe.utils.conditional("ECC_MODE", "ERR_DETECT_CORRECT", "DDR_ECC_DETECT_CORRECT=1", "",d)}"
EXTRA_FLAGS_append = "${@oe.utils.conditional("USE_ECC", "1", " ${ECC_FLAGS} ", "",d)}"
PMIC_EXTRA_FLAGS_append = "${@oe.utils.conditional("USE_ECC", "1", " ${ECC_FLAGS} ", "",d)}"

do_compile() {
	oe_runmake PLAT=${PLATFORM} ${EXTRA_FLAGS} bl2 bl31

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		oe_runmake PLAT=${PLATFORM} ${PMIC_EXTRA_FLAGS} BUILD_PLAT=${PMIC_BUILD_DIR} bl2 bl31
	fi
}

do_install() {
	install -d ${D}/boot
	install -m 644 ${S}/build/${PLATFORM}/release/bl2.bin ${D}/boot/bl2-${MACHINE}.bin
	install -m 644 ${S}/build/${PLATFORM}/release/bl31.bin ${D}/boot/bl31-${MACHINE}.bin

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${D}/boot/bl2-${MACHINE}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${D}/boot/bl31-${MACHINE}_pmic.bin
	fi
}

do_deploy_append() {
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${DEPLOYDIR}/bl2-${MACHINE}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}_pmic.bin
	fi
}
