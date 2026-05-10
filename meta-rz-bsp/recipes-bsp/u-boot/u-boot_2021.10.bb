require u-boot-renesas.inc

COMPATIBLE_MACHINE = "(rzg2l-family|rzg2h-family)"

UBOOT_URI = "git://github.com/renesas-rz/renesas-u-boot-cip.git;protocol=https"
UBOOT_BRANCH:rzg2l-family = "v2021.10/rz"
UBOOT_REV:rzg2l-family = "5141064c1552accaf69c6f509bf21b2063b9cff5"

UBOOT_BRANCH:rzv2h-evk = "v2021.10/rzv2h"
UBOOT_REV:rzv2h-evk = "31d53b8f6fdc1d9055a8c226643f4ed61570e017"

UBOOT_BRANCH:rzg2h-family = "v2021.10/rz"
UBOOT_REV:rzg2h-family = "9bf02ad38dd332f9dd349d9b0fe8fa47ba7b8d5c"

PV = "2021.10+git${SRCPV}"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=5a7450c57ffe5ae63fd732446b988025"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
SRC_URI:append:rzg2h-family = " \
	${@oe.utils.ifelse("${ECC_FULL}" == "1"," \
	file://0001-board-hihope-rzg2-reduce-memory-to-reserve-for-USB-m.patch \
	", "")} \
"

do_deploy:append() {
    if [ -n "${UBOOT_CONFIG}" ]
    then
        for config in ${UBOOT_MACHINE}; do
            i=$(expr $i + 1);
            for type in ${UBOOT_CONFIG}; do
                j=$(expr $j + 1);
                if [ $j -eq $i ]
                then
                    install -m 644 ${B}/${config}/${UBOOT_SREC} ${DEPLOYDIR}/u-boot-elf-${type}-${PV}-${PR}.${UBOOT_SREC_SUFFIX}
                    cd ${DEPLOYDIR}
                    ln -sf u-boot-elf-${type}-${PV}-${PR}.${UBOOT_SREC_SUFFIX} u-boot-elf-${type}.${UBOOT_SREC_SUFFIX}
                fi
            done
            unset j
        done
        unset i
    else
        install -m 644 ${B}/${UBOOT_SREC} ${DEPLOYDIR}/${UBOOT_SREC_IMAGE}
        cd ${DEPLOYDIR}
        rm -f ${UBOOT_SREC} ${UBOOT_SREC_SYMLINK}
        ln -sf ${UBOOT_SREC_IMAGE} ${UBOOT_SREC_SYMLINK}
        ln -sf ${UBOOT_SREC_IMAGE} ${UBOOT_SREC}
    fi
}
