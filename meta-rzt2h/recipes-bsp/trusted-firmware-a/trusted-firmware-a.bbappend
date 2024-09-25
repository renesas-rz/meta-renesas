COMPATIBLE_MACHINE_rzt2h = "(rzt2h-dev)"

DEPENDS_append = " u-boot"

LIC_FILES_CHKSUM = " \
        file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

PV = "v2.7+git${SRCPV}"

S = "${WORKDIR}/git"

TFA_URI ?= "git://github.com/renesas-rz/rzg_trusted-firmware-a.git;protocol=https"
TFA_REV ?= "103e1aaf6394357e0a65a644feaa44c36e6ac984"

SRC_URI = "${TFA_URI};nobranch=1"
SRCREV = "${TFA_REV}"

PLATFORM_rzt2h = "t2h"
U-BOOT-BIN_rzt2h = "/boot/u-boot.bin"
EXTRA_FLAGS_rzt2h = "BOARD=dev_1 PLATFORM_CORE_COUNT=4"
EXTRA_OEMAKE_rzt2h = "PLAT=${PLATFORM} ${EXTRA_FLAGS} BL33=${RECIPE_SYSROOT}/${U-BOOT-BIN} bl2 fip pkg"
PARALLEL_MAKE = "-j 1"

do_deploy() {
	# Create deploy folder
	install -d ${DEPLOYDIR}

	install -m 0644 ${S}/build/${PLATFORM}/release/bl2_bp_xspi0.bin ${DEPLOYDIR}/bl2_bp_xspi0-${MACHINE}.bin
	install -m 0644 ${S}/build/${PLATFORM}/release/bl2_bp_xspi1.bin ${DEPLOYDIR}/bl2_bp_xspi1-${MACHINE}.bin
	install -m 0644 ${S}/build/${PLATFORM}/release/bl2_bp_emmc.bin ${DEPLOYDIR}/bl2_bp_emmc-${MACHINE}.bin
	install -m 0644 ${S}/build/${PLATFORM}/release/bl2_bp_esd.bin ${DEPLOYDIR}/bl2_bp_esd-${MACHINE}.bin
	install -m 0644 ${S}/build/${PLATFORM}/release/fip.bin ${DEPLOYDIR}/fip-${MACHINE}.bin

	install -m 0644 ${S}/build/${PLATFORM}/release/bl2_bp_xspi0.srec ${DEPLOYDIR}/bl2_bp_xspi0-${MACHINE}.srec
	install -m 0644 ${S}/build/${PLATFORM}/release/bl2_bp_xspi1.srec ${DEPLOYDIR}/bl2_bp_xspi1-${MACHINE}.srec
	install -m 0644 ${S}/build/${PLATFORM}/release/bl2_bp_emmc.srec ${DEPLOYDIR}/bl2_bp_emmc-${MACHINE}.srec
	install -m 0644 ${S}/build/${PLATFORM}/release/fip.srec ${DEPLOYDIR}/fip-${MACHINE}.srec
}
