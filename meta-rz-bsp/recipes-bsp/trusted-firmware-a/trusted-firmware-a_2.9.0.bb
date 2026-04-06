require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg2l-family|rzg2h-family)"

LIC_FILES_CHKSUM = " \
	file://${WORKDIR}/git/docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

S = "${WORKDIR}/git"

TFA_URI ?= "git://github.com/renesas-rz/rzg_trusted-firmware-a.git;protocol=https"
TFA_REV ?= "69ad8fc4d38f31cddbfd9dfc8cccfb6b8609dcb9"
TFA_BRANCH ?= "v2.9/rz"

SRC_URI = "${TFA_URI};branch=${TFA_BRANCH}"
SRCREV = "${TFA_REV}"

PV = "2.9+git"

BUILD_DIR = "${B}/${TFA_PLATFORM}"
BUILD_DIR .= "/${@'debug' if d.getVar("TFA_DEBUG") == '1' else 'release'}"

# For G2L series
ECC_FLAGS = " DDR_ECC_ENABLE=1 "
ECC_FLAGS += "${@oe.utils.conditional("ECC_MODE", "ERR_DETECT", "DDR_ECC_DETECT=1", "",d)}"
ECC_FLAGS += "${@oe.utils.conditional("ECC_MODE", "ERR_DETECT_CORRECT", "DDR_ECC_DETECT_CORRECT=1", "",d)}"
EXTRA_OEMAKE:append:rzg2l-family = "${@oe.utils.conditional("USE_ECC", "1", " ${ECC_FLAGS} ", "",d)}"
TFA_PMIC_EXTRA_OEMAKE:append = "${@oe.utils.conditional("USE_ECC", "1", " ${ECC_FLAGS} ", "",d)}"
EXTRA_OEMAKE:append:rzg2l-family = "FIP_ALIGN=16"

# For RZ/G2H/N
EXTRA_OEMAKE:append:hihope-rzg2h = " LSI=G2H RCAR_DRAM_SPLIT=2 RCAR_DRAM_LPDDR4_MEMCONF=1 RCAR_DRAM_CHANNEL=5 SPD=none"
EXTRA_OEMAKE:append:hihope-rzg2n = " LSI=G2N SPD=none"
LOSSY_ENABLE ?= "1"
ATFW_OPT_LOSSY = "${@oe.utils.conditional('LOSSY_ENABLE', '1', ' RCAR_LOSSY_ENABLE=1', '', d)}"
EXTRA_OEMAKE:append:hihope-rzg2n = " ${@oe.utils.conditional('USE_ECC', '1', ' LIFEC_DBSC_PROTECT_ENABLE=0 RZG_DRAM_ECC=1', ' ${ATFW_OPT_LOSSY}', d)}"
EXTRA_OEMAKE:append:hihope-rzg2h = " ${@oe.utils.conditional('USE_ECC', '1', ' LIFEC_DBSC_PROTECT_ENABLE=0 RCAR_DRAM_SPLIT=0 RZG_DRAM_ECC=1', ' ${ATFW_OPT_LOSSY}', d)}"
EXTRA_OEMAKE:append:rzg2h-family = " RZG_DRAM_ECC_FULL=${ECC_FULL}"
EXTRA_OEMAKE:append:rzg2h-family = " RCAR_RPC_HYPERFLASH_LOCKED=0"

do_compile:prepend:rzg2l-family() {
	# This is still needed to have the native tools executing properly by
	# setting the RPATH
	sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/fiptool/Makefile
}

PMIC_BUILD_DIR = "${S}/build_pmic"

do_compile:append:rzg2l-family() {
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		for T in ${TFA_BUILD_TARGET}; do
			oe_runmake PLAT=${TFA_PLATFORM} ${TFA_PMIC_EXTRA_OEMAKE} BUILD_PLAT=${PMIC_BUILD_DIR} -C ${S} $T
		done
	fi
}

do_compile:append:rzg2h-family() {
	for T in ${TFA_BUILD_TARGET}; do
		oe_runmake ${TFA_PLATFORM} PLAT=${TFA_PLATFORM} -C ${S} $T
	done
}

do_install:append:rzg2l-family() {
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${D}/firmware/bl2-${TFA_PLATFORM}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${D}/firmware/bl31-${TFA_PLATFORM}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/fip.bin ${D}/firmware/fip-${TFA_PLATFORM}_pmic.bin
	fi
}

do_deploy:append:rzg2l-family() {
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		cp -rf ${D}/firmware/*pmic.bin ${DEPLOYDIR}/
	fi
}

do_deploy:append:rzg2h-family() {
	install -m 0644 ${B}/${TFA_PLATFORM}/release/bl2.bin ${DEPLOYDIR}/bl2-${MACHINE}.bin
	install -m 0644 ${B}/${TFA_PLATFORM}/release/bl2.srec ${DEPLOYDIR}/bl2-${MACHINE}.srec
	install -m 0644 ${B}/${TFA_PLATFORM}/release/bl31.srec ${DEPLOYDIR}/bl31-${MACHINE}.srec
	install -m 0644 ${B}/${TFA_PLATFORM}/release/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}.bin
	install -m 0644 ${S}/tools/renesas/rzg_layout_create/bootparam_sa0.srec ${DEPLOYDIR}/bootparam_sa0.srec
	install -m 0644 ${S}/tools/renesas/rzg_layout_create/bootparam_sa0.bin ${DEPLOYDIR}/bootparam_sa0.bin
	install -m 0644 ${S}/tools/renesas/rzg_layout_create/cert_header_sa6.srec ${DEPLOYDIR}/cert_header_sa6.srec
	install -m 0644 ${S}/tools/renesas/rzg_layout_create/cert_header_sa6.bin ${DEPLOYDIR}/cert_header_sa6.bin
}

addtask deploy before do_build after do_compile
