DESCRIPTION = "VSP Manager Interface test app for RZG2"

require vspmif.inc

DEPENDS = "vspmif-user-module mmngr-user-module"
PN = "vspmif-tp-user-module"
PR = "r0"

S = "${WORKDIR}/git"
VSPMIF_TP_DIR = "vspm_if-tp-user/files/vspm_if"

# Get Wordsize of test app and change their names later to avoid override
WS_aarch64 = ""
WS_virtclass-multilib-lib32 = "32"

SRC_URI_append_rzg2l = " \
        file://0001-Add-ISU-One-pass-test.patch \
	file://0002-add-ISU-IT.patch \
"

do_compile_prepend_rzg2l() {
    if [ X${WS} = "X32" ]; then
       cp ${STAGING_KERNEL_DIR}/include/vsp_drv.h ${RECIPE_SYSROOT}/usr/local/include
       cp ${STAGING_KERNEL_DIR}/include/isu_drv.h ${RECIPE_SYSROOT}/usr/local/include
       cp ${STAGING_KERNEL_DIR}/include/fdp_drv.h ${RECIPE_SYSROOT}/usr/local/include
       cp ${STAGING_KERNEL_DIR}/include/vspm_cmn.h ${RECIPE_SYSROOT}/usr/local/include
       cp ${STAGING_KERNEL_DIR}/include/mmngr_public_cmn.h ${RECIPE_SYSROOT}/usr/local/include
    fi
}

do_compile() {
    cd ${S}/${VSPMIF_TP_DIR}
    make all
}

do_install() {
    # Create destination folder
    install -d ${D}${RENESAS_DATADIR}/bin/

    # Copy user test program
    if [ X${WS} = "X32" ]; then
        install -m 755 ${S}/${VSPMIF_TP_DIR}/vspm_tp ${D}${RENESAS_DATADIR}/bin/vspm_tp32
        install -m 755 ${S}/${VSPMIF_TP_DIR}/fdpm_tp ${D}${RENESAS_DATADIR}/bin/fdpm_tp32
    else
        install -m 755 ${S}/${VSPMIF_TP_DIR}/vspm_tp ${D}${RENESAS_DATADIR}/bin/
        install -m 755 ${S}/${VSPMIF_TP_DIR}/fdpm_tp ${D}${RENESAS_DATADIR}/bin/
    fi
}

do_install_append_rzg2l() {
    if [ X${WS} = "X32" ]; then
        install -m 755 ${S}/${VSPMIF_TP_DIR}/vspm_isu_rs ${D}${RENESAS_DATADIR}/bin/isum_tp32
    else
        install -m 755 ${S}/${VSPMIF_TP_DIR}/vspm_isu_rs ${D}${RENESAS_DATADIR}/bin/isum_tp
    fi
}

PACKAGES = "\
    ${PN} \
    ${PN}-dbg \
"
FILES_${PN} = " \
    ${@oe.utils.conditional('WS', '32', '${RENESAS_DATADIR}/bin/vspm_tp32 ${RENESAS_DATADIR}/bin/fdpm_tp32', \
    '${RENESAS_DATADIR}/bin/vspm_tp ${RENESAS_DATADIR}/bin/fdpm_tp', d)}"

FILES_rzg2l_${PN} = " \
    ${@oe.utils.conditional('WS', '32', '${RENESAS_DATADIR}/bin/isum_tp32', '${RENESAS_DATADIR}/bin/isum_tp', d)}"

FILES_${PN}-dbg = " \
    ${RENESAS_DATADIR}/bin/.debug/*"

RPROVIDES_${PN} += "vspmif-tp-user-module"
