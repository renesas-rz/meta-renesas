require recipes-bsp/u-boot/u-boot-common.inc
require recipes-bsp/u-boot/u-boot.inc

LIC_FILES_CHKSUM = "file://Licenses/README;md5=5a7450c57ffe5ae63fd732446b988025"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
DEPENDS:append = " bc dtc-native opensbi"

SRCREV="ea6d1659b79402a6137e7cda9620bfe956801780"
BRANCH="v2021.12/rzf-smarc"

SRC_URI = " \
	git://github.com/renesas-rz/renesas-u-boot-cip.git;protocol=https;branch=${BRANCH} \
	file://BootLoaderHeader.bin \
    "

PV = "v2020.10+git${SRCPV}"

do_compile:prepend() {
    export OPENSBI=${DEPLOY_DIR_IMAGE}/fw_dynamic.bin
}

do_compile:append() {

	cat ${WORKDIR}/BootLoaderHeader.bin  ${B}/${config}/spl/u-boot-spl.bin > ${B}/u-boot-spl_bp.bin
	objcopy -I binary -O srec --adjust-vma=0x00011E00 --srec-forceS3 ${B}/u-boot-spl_bp.bin ${B}/spl-${MACHINE}.srec
	objcopy -I binary -O srec --adjust-vma=0 --srec-forceS3 ${B}/${config}/u-boot.itb ${B}/fit-${MACHINE}.srec
}

do_deploy:append() {
    if [ -f "${WORKDIR}/boot.scr" ]; then
        install -d ${DEPLOY_DIR_IMAGE}
        install -m 755 ${WORKDIR}/boot.scr ${DEPLOY_DIR_IMAGE}
    fi

	install -m 755 ${B}/spl-${MACHINE}.srec ${DEPLOY_DIR_IMAGE}
	install -m 755 ${B}/fit-${MACHINE}.srec ${DEPLOY_DIR_IMAGE}
}

do_compile[depends] += "opensbi:do_deploy"
