LIC_FILES_CHKSUM = "file://LICENSE.md;md5=2e4821bed385270bdfa81f3e13d0b68d"
LICENSE="BSD-3-Clause"

PV_rzv2m = "RZV2M+git${SRCPV}"
PV_rzv2ma = "RZV2MA+git${SRCPV}"

PACKAGE_ARCH = "${MACHINE_ARCH}"

FLASH_WRITER_URL = "git://github.com/renesas-rz/rzg2_flash_writer.git"
BRANCH_rzv2m = "rz_v2m"
BRANCH_rzv2ma = "rz_v2ma"

SRC_URI = "${FLASH_WRITER_URL};protocol=https;branch=${BRANCH}"
SRCREV_rzv2m = "8f5bc8593544ccd82cf75e15aa52c42f80195c65"
SRCREV_rzv2ma = "02abd1200b9792465822927d04747b2ecaf58e6b"

inherit deploy

SRC_URI_append = " \
	file://0001-makefile.linaro-update-makefile-to-be-built-with-cro.patch \
"

S = "${WORKDIR}/git"

CFLAGS_append = " -fno-stack-protector"

do_compile () {
	cd ${S}
	oe_runmake -f makefile.linaro
}

PARALLEL_MAKE = "-j 1"

do_deploy() {
        install -d ${DEPLOYDIR}
        install -m 644 ${S}/AArch64_output/*.bin ${DEPLOYDIR}
}

addtask deploy after do_compile
