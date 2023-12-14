DESCRIPTION = "Trusted Firmware-A for Renesas RZ"

LICENSE = "BSD-3-Clause & MIT & Apache-2.0"
LIC_FILES_CHKSUM = " \
	file://${WORKDIR}/git/docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

S = "${WORKDIR}/git"

BRANCH = "v2.9/rz"

SRC_URI = " \
	git://github.com/renesas-rz/rzg_trusted-firmware-a.git;branch=${BRANCH};protocol=https \
"

SRCREV = "cc18695622e5637ec70ee3ae8eb5e83b09d13804"

PV = "v2.9+git"

COMPATIBLE_MACHINE_rzg2h = "(ek874|hihope-rzg2m|hihope-rzg2n|hihope-rzg2h)"
COMPATIBLE_MACHINE_rzg2l = "(smarc-rzg2l|rzg2l-dev|smarc-rzg2lc|rzg2lc-dev|smarc-rzg2ul|rzg2ul-dev|smarc-rzv2l|rzv2l-dev)"

PLATFORM ?= "rzg"

# requires CROSS_COMPILE set by hand as there is no configure script
export CROSS_COMPILE="${TARGET_PREFIX}"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

do_deploy() {
    # Create deploy folder
    install -d ${DEPLOYDIR}

    # Copy IPL to deploy folder
    install -m 0644 ${S}/build/${PLATFORM}/release/bl2/bl2.elf ${DEPLOYDIR}/bl2-${MACHINE}.elf
    install -m 0644 ${S}/build/${PLATFORM}/release/bl2.bin ${DEPLOYDIR}/bl2-${MACHINE}.bin
    install -m 0644 ${S}/build/${PLATFORM}/release/bl31/bl31.elf ${DEPLOYDIR}/bl31-${MACHINE}.elf
    install -m 0644 ${S}/build/${PLATFORM}/release/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}.bin
}

addtask deploy before do_build after do_compile
