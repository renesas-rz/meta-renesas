LIC_FILES_CHKSUM = "file://LICENSE.md;md5=7f62d8fc087d1e90350a140c9f8c8e99"
LICENSE="BSD-3-Clause"
PV = "1.05+git${SRCPV}"

PACKAGE_ARCH = "${MACHINE_ARCH}"
FLASH_WRITER_URL = "git://github.com/renesas-rz/rzg2_flash_writer"
BRANCH = "master"

SRC_URI = "${FLASH_WRITER_URL};branch=${BRANCH}"
SRCREV = "6606c4f4351f56fb3bd84d7836c01c8932a4f884"

inherit deploy

S = "${WORKDIR}/git"

do_compile() {
        if [ "${MACHINE}" = "hihope-rzg2n" -o "${MACHINE}" = "hihope-rzg2m" -o "${MACHINE}" = "hihope-rzg2h" ]; then
                BOARD="HIHOPE";
        elif [ "${MACHINE}" = "ek874" ]; then
                BOARD="EK874";
        fi
        cd ${S}

       oe_runmake BOARD=${BOARD}
}

do_install[noexec] = "1"

do_deploy() {
        install -d ${DEPLOYDIR}
        install -m 644 ${S}/AArch64_output/*.mot ${DEPLOYDIR}
}

PARALLEL_MAKE = "-j 1"
addtask deploy after do_compile
