DESCRIPTION = "Trusted Firmware-A for RZ/G2H/M/N/E"

LICENSE = "MIT"
LIC_FILES_CHKSUM = " \
	file://${WORKDIR}/git/docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
	file://${WORKDIR}/mbedtls/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57 \
"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

S = "${WORKDIR}/git"

BRANCH = "v2.7/rz"
BRANCH_mbedtls = "mbedtls-2.28"

SRC_URI = " \
	git://github.com/renesas-rz/rzg_trusted-firmware-a.git;branch=${BRANCH};protocol=https \
	git://github.com/ARMmbed/mbedtls.git;branch=${BRANCH_mbedtls};name=mbedtls;destsuffix=mbedtls \
"

SRCREV = "d7cea95a513382508da470b43bbfba0e9fda9ac4"
SRCREV_mbedtls = "7e163d796c7a8d3dd1a48884fb48ee4398da3137"

PV = "v2.7+git"

COMPATIBLE_MACHINE_rzg2h = "(ek874|hihope-rzg2m|hihope-rzg2n|hihope-rzg2h)"
COMPATIBLE_MACHINE_rzg2l = "(smarc-rzg2l|smarc-rzg2lc|smarc-rzg2ul|smarc-rzv2l|rzv2l-dev)"

PLATFORM ?= "rzg"

# For RZ/G2L Series
PLATFORM_smarc-rzg2l = "g2l"
EXTRA_FLAGS_smarc-rzg2l = "BOARD=smarc_2"
PMIC_EXTRA_FLAGS_smarc-rzg2l = "BOARD=smarc_pmic_2"
FLASH_ADDRESS_BL2_BP_smarc-rzg2l = "00000"
FLASH_ADDRESS_FIP_smarc-rzg2l = "1D200"

PLATFORM_smarc-rzg2lc = "g2l"
EXTRA_FLAGS_smarc-rzg2lc = "BOARD=smarc_1"
FLASH_ADDRESS_BL2_BP_smarc-rzg2lc = "00000"
FLASH_ADDRESS_FIP_smarc-rzg2lc = "1D200"

PLATFORM_smarc-rzg2ul = "g2ul"
EXTRA_FLAGS_smarc-rzg2ul = "BOARD=g2ul_smarc SOC_TYPE=1 SPI_FLASH=AT25QL128A"
FLASH_ADDRESS_BL2_BP_smarc-rzg2ul = "00000"
FLASH_ADDRESS_FIP_smarc-rzg2ul = "1D200"

PLATFORM_smarc-rzv2l = "v2l"
EXTRA_FLAGS_smarc-rzv2l = "BOARD=smarc_4"
PMIC_EXTRA_FLAGS_smarc-rzv2l = "BOARD=smarc_pmic_2"
FLASH_ADDRESS_BL2_BP_smarc-rzv2l = "00000"
FLASH_ADDRESS_FIP_smarc-rzv2l = "1D200"

PLATFORM_rzv2l-dev = "v2l"
EXTRA_FLAGS_rzv2l-dev = "BOARD=dev15_4"
FLASH_ADDRESS_BL2_BP_rzv2l-dev = "00000"
FLASH_ADDRESS_FIP_rzv2l-dev = "1D200"

PMIC_BUILD_DIR = "${S}/build_pmic"

# For RZ/G2H/M/N/E
ATFW_OPT_r8a774c0 = "LSI=G2E RCAR_SA0_SIZE=0 RCAR_DRAM_DDR3L_MEMCONF=1 RCAR_DRAM_DDR3L_MEMDUAL=1 SPD="none""
ATFW_OPT_r8a774a1 = "LSI=G2M RCAR_DRAM_SPLIT=2 SPD="none""
ATFW_OPT_r8a774b1 = "LSI=G2N SPD="none""
ATFW_OPT_r8a774e1 = "LSI=G2H RCAR_DRAM_SPLIT=2 RCAR_DRAM_LPDDR4_MEMCONF=1 RCAR_DRAM_CHANNEL=5 SPD="none""

LOSSY_ENABLE ?= "1"
ATFW_OPT_LOSSY = "${@oe.utils.conditional("LOSSY_ENABLE", "1", "RCAR_LOSSY_ENABLE=1", "", d)}"

ATFW_OPT_append_r8a774c0 = "${@oe.utils.conditional("USE_ECC", "1", " LIFEC_DBSC_PROTECT_ENABLE=0 RZG_DRAM_ECC=1 ", "",d)}"
ATFW_OPT_append_r8a774a1 = "${@oe.utils.conditional("USE_ECC", "1", " LIFEC_DBSC_PROTECT_ENABLE=0 RCAR_DRAM_SPLIT=0 RZG_DRAM_ECC=1 ", " ${ATFW_OPT_LOSSY} ",d)}"
ATFW_OPT_append_r8a774b1 = "${@oe.utils.conditional("USE_ECC", "1", " LIFEC_DBSC_PROTECT_ENABLE=0 RZG_DRAM_ECC=1 ", " ${ATFW_OPT_LOSSY} ",d)}"
ATFW_OPT_append_r8a774e1 = "${@oe.utils.conditional("USE_ECC", "1", " LIFEC_DBSC_PROTECT_ENABLE=0 RCAR_DRAM_SPLIT=0 RZG_DRAM_ECC=1 ", " ${ATFW_OPT_LOSSY} ",d)}"

ATFW_OPT_append += " RZG_DRAM_ECC_FULL=${ECC_FULL} "

ATFW_OPT_append += " RCAR_RPC_HYPERFLASH_LOCKED=0 MBEDTLS_DIR=../mbedtls "

# requires CROSS_COMPILE set by hand as there is no configure script
export CROSS_COMPILE="${TARGET_PREFIX}"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

FILES_${PN}_rzg2l = "/boot "
SYSROOT_DIRS_rzg2l += "/boot"

do_compile_rzg2h() {
    oe_runmake distclean
    oe_runmake bl2 bl31 rzg PLAT=${PLATFORM} ${ATFW_OPT}
}

do_compile_rzg2l() {
# Build TF-A
    oe_runmake PLAT=${PLATFORM} ${EXTRA_FLAGS} bl2 bl31

    if [ "${PMIC_SUPPORT}" = "1" ]; then
       oe_runmake PLAT=${PLATFORM} ${PMIC_EXTRA_FLAGS} BUILD_PLAT=${PMIC_BUILD_DIR} bl2 bl31
    fi
}

do_install_rzg2l () { 
    install -d ${D}/boot 
    install -m 644 ${S}/build/${PLATFORM}/release/bl2.bin ${D}/boot/bl2-${MACHINE}.bin
    install -m 644 ${S}/build/${PLATFORM}/release/bl31.bin ${D}/boot/bl31-${MACHINE}.bin

    if [ "${PMIC_SUPPORT}" = "1" ]; then
       install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${D}/boot/bl2-${MACHINE}_pmic.bin
       install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${D}/boot/bl31-${MACHINE}_pmic.bin
    fi
}

do_deploy() {
    # Create deploy folder
    install -d ${DEPLOYDIR}

    # Copy IPL to deploy folder
    install -m 0644 ${S}/build/${PLATFORM}/release/bl2/bl2.elf ${DEPLOYDIR}/bl2-${MACHINE}.elf
    install -m 0644 ${S}/build/${PLATFORM}/release/bl2.bin ${DEPLOYDIR}/bl2-${MACHINE}.bin
    install -m 0644 ${S}/build/${PLATFORM}/release/bl31/bl31.elf ${DEPLOYDIR}/bl31-${MACHINE}.elf
    install -m 0644 ${S}/build/${PLATFORM}/release/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}.bin
}

do_deploy_append_rzg2l() {
    if [ "${PMIC_SUPPORT}" = "1" ]; then
       install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${DEPLOYDIR}/bl2-${MACHINE}_pmic.bin
       install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}_pmic.bin
    fi
}

do_deploy_append_rzg2h() {
    install -m 0644 ${S}/build/${PLATFORM}/release/bl2.srec ${DEPLOYDIR}/bl2-${MACHINE}.srec
    install -m 0644 ${S}/build/${PLATFORM}/release/bl31.srec ${DEPLOYDIR}/bl31-${MACHINE}.srec
    install -m 0644 ${S}/tools/renesas/rzg_layout_create/bootparam_sa0.srec ${DEPLOYDIR}/bootparam_sa0.srec
    install -m 0644 ${S}/tools/renesas/rzg_layout_create/cert_header_sa6.srec ${DEPLOYDIR}/cert_header_sa6.srec
}
addtask deploy before do_build after do_compile
