require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg2l-family)"

LIC_FILES_CHKSUM = " \
	file://${WORKDIR}/git/docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

S = "${WORKDIR}/git"

TFA_URI ?= "git://github.com/renesas-rz/rzg_trusted-firmware-a.git;protocol=https"
TFA_REV ?= "cc18695622e5637ec70ee3ae8eb5e83b09d13804"
TFA_BRANCH ?= "v2.9/rz"

SRC_URI = "${TFA_URI};branch=${TFA_BRANCH}"
SRCREV = "${TFA_REV}"

PV = "2.9+git"

BUILD_DIR = "${B}/${TFA_PLATFORM}"
BUILD_DIR .= "/${@'debug' if d.getVar("TFA_DEBUG") == '1' else 'release'}"

ECC_FLAGS = " DDR_ECC_ENABLE=1 "
ECC_FLAGS += "${@oe.utils.conditional("ECC_MODE", "ERR_DETECT", "DDR_ECC_DETECT=1", "",d)}"
ECC_FLAGS += "${@oe.utils.conditional("ECC_MODE", "ERR_DETECT_CORRECT", "DDR_ECC_DETECT_CORRECT=1", "",d)}"
EXTRA_OEMAKE += "${@oe.utils.conditional("USE_ECC", "1", " ${ECC_FLAGS} ", "",d)}"
TFA_PMIC_EXTRA_OEMAKE:append = "${@oe.utils.conditional("USE_ECC", "1", " ${ECC_FLAGS} ", "",d)}"
EXTRA_OEMAKE += "FIP_ALIGN=16"

do_compile:prepend() {
	# This is still needed to have the native tools executing properly by
	# setting the RPATH
	sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/fiptool/Makefile
}

PMIC_BUILD_DIR = "${S}/build_pmic"

do_compile:append() {
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		for T in ${TFA_BUILD_TARGET}; do
			oe_runmake PLAT=${TFA_PLATFORM} ${TFA_PMIC_EXTRA_OEMAKE} BUILD_PLAT=${PMIC_BUILD_DIR} -C ${S} $T
		done
	fi
}

do_install:append() {
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 0644 ${PMIC_BUILD_DIR}/bl2.bin ${D}/firmware/bl2-${TFA_PLATFORM}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/bl31.bin ${D}/firmware/bl31-${TFA_PLATFORM}_pmic.bin
		install -m 0644 ${PMIC_BUILD_DIR}/fip.bin ${D}/firmware/fip-${TFA_PLATFORM}_pmic.bin
	fi
}

do_deploy:append() {
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		cp -rf ${D}/firmware/*pmic.bin ${DEPLOYDIR}/
	fi
}
addtask deploy before do_build after do_compile
