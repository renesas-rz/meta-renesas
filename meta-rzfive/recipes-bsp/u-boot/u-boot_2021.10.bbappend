FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
DEPENDS:append = " bc dtc-native opensbi"

SRC_URI_append = " \
	file://BootLoaderHeader.bin \
"

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
