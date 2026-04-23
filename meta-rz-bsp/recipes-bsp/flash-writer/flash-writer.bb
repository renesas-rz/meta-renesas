LIC_FILES_CHKSUM:rzg2l-family = "file://LICENSE.md;md5=1fb5dca04b27614d6d04abca6f103d8d"
LICENSE="BSD-3-Clause"

LIC_FILES_CHKSUM ?= "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

PV:rzg2l-family = "1.08+git${SRCPV}"
PV:rzg3s-family = "0127"
PV:rzg3l-family = "1.0"
PV ?= "0.90"

PACKAGE_ARCH = "${MACHINE_ARCH}"

FLASH_WRITER_URL ?= "git://github.com/renesas-rz/rzg2_flash_writer"

BRANCH:rzg2l-family ?= "rz_g2l"
SRC_URI:rzg2l-family = "${FLASH_WRITER_URL};protocol=https;branch=${BRANCH}"
SRCREV:rzg2l-family = "43509f2b268b0ce86288cf3c37e668d64c5d5d12"

SRC_URI:smarc-rzg3e = "file://Flash_Writer_SCIF_RZG3E_EVK_LPDDR4X.mot"
SRC_URI:rzg3e-dev = "file://Flash_Writer_SCIF_RZG3E_DEV_LPDDR4X_0117.mot"

SRC_URI:rzv2h-family = "file://Flash_Writer_SCIF_RZV2H_DEV_INTERNAL_MEMORY.mot"

SRC_URI:rzv2n-family = "file://Flash_Writer_SCIF_RZV2N_DEV_LPDDR4X.mot"

SRC_URI:rzg3s-family = " \
	file://FlashWriter.bin;subdir=${BPN} \
	file://FlashWriter.mot;subdir=${BPN} \
"

SRC_URI:rzt2h-family = " \
	file://Flash_Programmer_SCIF_CR52_RZT2H_EVK.mot \
	file://HDR_NM \
"

BRANCH:rzg2h-family ?= "master"
SRC_URI:rzg2h-family = "${FLASH_WRITER_URL};protocol=https;branch=${BRANCH}"
SRCREV:rzg2h-family = "ceebddab90e5ae9b100536114553af818261c660"

SRC_URI:smarc-rzg3l = "file://Flash_Writer_SCIF_RZG3L_SMARC_LPDDR4.mot"

inherit deploy

S:rzg2l-family = "${WORKDIR}/git"
S:rzg2h-family = "${WORKDIR}/git"
S:rzg3e-family = "${WORKDIR}"
S:rzv2h-family = "${WORKDIR}"
S:rzv2n-family = "${WORKDIR}"
S:rzg3s-family = "${WORKDIR}/${BPN}"
S:rzt2h-family = "${WORKDIR}"
S:rzg3l-family = "${WORKDIR}"
PMIC_BUILD_DIR = "${S}/build_pmic"

do_compile:rzg2l-family() {
	cd ${S}

	oe_runmake BOARD=${FLASH_WRITER_BOARD}

	if [ "${PMIC_SUPPORT}" = "1" ]; then
		oe_runmake OUTPUT_DIR=${PMIC_BUILD_DIR} clean;
		oe_runmake BOARD=${FLASH_WRITER_PMIC_BOARD} OUTPUT_DIR=${PMIC_BUILD_DIR};
	fi
}

do_compile:rzg3s-family() {
	# Convert to srec
	objcopy -I binary -O srec --adjust-vma=0xA1E00 --srec-forceS3 ${S}/FlashWriter.bin ${S}/FlashWriter.srec
}

do_compile:rzg2h-family() {
        if [ "${MACHINE}" = "hihope-rzg2n" -o "${MACHINE}" = "hihope-rzg2h" ]; then
                BOARD="HIHOPE";
        fi
        cd ${S}

       oe_runmake BOARD=${BOARD}
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

do_deploy:rzv2h-family:append() {
	install -m 755 ${S}/*mot ${DEPLOYDIR}
}

do_deploy:rzv2n-family:append() {
	install -m 755 ${S}/*mot ${DEPLOYDIR}
}

do_deploy:append:rzg3s-family() {
	# Copy Flash-writer binaries to deploy folder
	install -m 0644  ${S}/FlashWriter.srec ${DEPLOYDIR}/FlashWriter-${MACHINE}.srec
	install -m 0644  ${S}/FlashWriter.mot ${DEPLOYDIR}/FlashWriter-${MACHINE}.mot
}

do_deploy:append:rzt2h-family() {
	# Copy Flash-writer binaries to deploy folder
	install -m 0644  ${S}/Flash_Programmer_SCIF_CR52_RZT2H_EVK.mot ${DEPLOYDIR}
	install -m 0644  ${S}/HDR_NM ${DEPLOYDIR}
}

do_deploy:append:rzg2h-family() {
        install -d ${DEPLOYDIR}
        install -m 644 ${S}/AArch64_output/*.mot ${DEPLOYDIR}
}

do_deploy:append:rzg3l-family() {
	install -d ${DEPLOYDIR}
	install -m 755 ${S}/Flash_Writer_SCIF_RZG3L_SMARC_LPDDR4.mot ${DEPLOYDIR}
}

PARALLEL_MAKE = "-j 1"

addtask deploy after do_compile
