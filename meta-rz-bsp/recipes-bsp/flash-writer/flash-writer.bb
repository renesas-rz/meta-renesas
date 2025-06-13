LIC_FILES_CHKSUM:rzg2l-family= "file://LICENSE.md;md5=1fb5dca04b27614d6d04abca6f103d8d"
LICENSE="BSD-3-Clause"

LIC_FILES_CHKSUM:rzg3e-family = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

PV:rzg2l-family= "1.06+git${SRCPV}"
PV:rzg3e-family = "0.90"

PACKAGE_ARCH = "${MACHINE_ARCH}"

FLASH_WRITER_URL ?= "git://github.com/renesas-rz/rzg2_flash_writer"
BRANCH ?= "rz_g2l"

SRC_URI:rzg2l-family = "${FLASH_WRITER_URL};protocol=https;branch=${BRANCH}"
SRCREV:rzg2l-family = "ff167b676547f3997906c82c9be504eb5cff8ef0"

SRC_URI:smarc-rzg3e = "file://Flash_Writer_SCIF_RZG3E_EVK_LPDDR4X.mot"
SRC_URI:rzg3e-dev = "file://Flash_Writer_SCIF_RZG3E_DEV_LPDDR4X_0117.mot"

inherit deploy

S:rzg2l-family= "${WORKDIR}/git"
S:rzg3e-family = "${WORKDIR}"
PMIC_BUILD_DIR = "${S}/build_pmic"

do_compile:rzg2l-family() {
	cd ${S}

	oe_runmake BOARD=${FLASH_WRITER_BOARD}

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		oe_runmake OUTPUT_DIR=${PMIC_BUILD_DIR} clean;
		oe_runmake BOARD=${FLASH_WRITER_PMIC_BOARD} OUTPUT_DIR=${PMIC_BUILD_DIR};
	fi
}

do_install[noexec] = "1"

do_deploy() {
	install -d ${DEPLOYDIR}
}

do_deploy:rzg2l-family:append() {
	install -m 644 ${S}/AArch64_output/*.mot ${DEPLOYDIR}
	if [ "${PMIC_SUPPORT}" = "1" ]; then
		install -m 644 ${PMIC_BUILD_DIR}/*.mot ${DEPLOYDIR}
	fi
}

do_deploy:rzg3e-family:append() {
	install -m 755 ${S}/*mot ${DEPLOYDIR}
}

PARALLEL_MAKE = "-j 1"

addtask deploy after do_compile
