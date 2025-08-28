require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg3e-family|rzg2l-family|rzg3s-family)"

LIC_FILES_CHKSUM = "file://${WORKDIR}/git/docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"
PV = "2.10+git${SRCPV}"

S = "${WORKDIR}/git"

TFA_URI ?= "git://github.com/renesas-rz/rzg_trusted-firmware-a.git;protocol=https"
TFA_REV:rzg2l-family = "f59ed5a31ef6b28200e9ba35fc78a607fdeda6dd"
TFA_REV:rzg3s-family = "f59ed5a31ef6b28200e9ba35fc78a607fdeda6dd"

SRC_URI = "${TFA_URI};nobranch=1"
SRCREV = "${TFA_REV}"

BUILD_DIR = "${B}/${TFA_PLATFORM}"
BUILD_DIR .= "/${@'debug' if d.getVar("TFA_DEBUG") == '1' else 'release'}"

EXTRA_OEMAKE:append:rzg2l-family = " FIP_ALIGN=16"

PMIC_BUILD_DIR = "${S}/build_pmic"

do_compile:append:rzg2l-family() {
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		for T in ${TFA_BUILD_TARGET}; do
			oe_runmake PLAT=${TFA_PLATFORM} ${TFA_PMIC_EXTRA_OEMAKE} BUILD_PLAT=${PMIC_BUILD_DIR} -C ${S} $T
		done
	fi
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

addtask deploy before do_build after do_compile
