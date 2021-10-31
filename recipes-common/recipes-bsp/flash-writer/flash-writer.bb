LIC_FILES_CHKSUM = "file://LICENSE.md;md5=1fb5dca04b27614d6d04abca6f103d8d"
LICENSE="BSD-3-Clause"
PV = "0.89+git${SRCPV}"

PACKAGE_ARCH = "${MACHINE_ARCH}"

FLASH_WRITER_URL = "git://github.com/renesas-rz/rzg2_flash_writer"
BRANCH = "rz_g2l"

SRC_URI = "${FLASH_WRITER_URL};branch=${BRANCH}"
SRCREV = "126ed36e30594869d4ecec45fc28cb15ea91c1c2"

inherit deploy
#require include/provisioning.inc

S = "${WORKDIR}/git"
PMIC_BUILD_DIR = "${S}/build_pmic"

do_compile() {
        if [ "${MACHINE}" = "smarc-rzg2l" ]; then
                BOARD="RZG2L_SMARC";
                PMIC_BOARD="RZG2L_SMARC_PMIC";
        elif [ "${MACHINE}" = "rzg2l-dev" ]; then
                BOARD="RZG2L_15MMSQ_DEV";
        elif [ "${MACHINE}" = "rzg2lc-dev" ]; then
                BOARD="RZG2LC_DEV";
        elif [ "${MACHINE}" = "smarc-rzg2lc" ]; then
                BOARD="RZG2LC_SMARC";
        fi
        cd ${S}

	oe_runmake BOARD=${BOARD}

        if [ "${PMIC_SUPPORT}" = "1" ]; then
		oe_runmake OUTPUT_DIR=${PMIC_BUILD_DIR} clean;
		oe_runmake BOARD=${PMIC_BOARD} OUTPUT_DIR=${PMIC_BUILD_DIR};
	fi
}

do_install[noexec] = "1"

do_deploy() {
        install -d ${DEPLOYDIR}
        install -m 644 ${S}/AArch64_output/*.mot ${DEPLOYDIR}
        if [ "${PMIC_SUPPORT}" = "1" ]; then
        	install -m 644 ${PMIC_BUILD_DIR}/*.mot ${DEPLOYDIR}
	fi
}
PARALLEL_MAKE = "-j 1"
addtask deploy after do_compile
