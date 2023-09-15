SUMMARY = "RZ/G2 Firmware Update TA"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit deploy python3native

LICENSE = "BSD-3-Clause & GPLv2"
LIC_FILES_CHKSUM = "file://${S}/LICENSE.md;md5=e39af0548166c775f6685c6b69ec94f8"

#TAG: 2.00
PV = "2.00+git${SRCPV}"
SRCREV = "6e89720dcd6c887b221564be618cc19fd59c3322"

BRANCH = "rzg2"

SRC_URI = " \
	git://github.com/renesas-rz/rzg_optee-ta_fwu.git;branch=${BRANCH};protocol=https \
" 

DEPENDS_append = " optee-os optee-client python3-pyelftools-native python3-cryptography-native python3-pycryptodome-native python3-pycryptodomex-native"

OPTEE_CLIENT_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TA_DEV_KIT_DIR = "${STAGING_INCDIR}/optee/export-user_ta/"

CFLAGS_prepend = "--sysroot=${STAGING_DIR_HOST} "

EXTRA_OEMAKE = " \
	TA_DEV_KIT_DIR=${TA_DEV_KIT_DIR} \
	OPTEE_CLIENT_EXPORT=${OPTEE_CLIENT_EXPORT} \
	CROSS_COMPILE=${TARGET_PREFIX} \
"

S = "${WORKDIR}/git"

do_compile() {
    oe_runmake MACHINE="${@d.getVar("MACHINE", False).replace("-", "_")}"
}

do_install () {
    mkdir -p ${WORKDIR}/deploy/${bindir}

    install -p -m 0755 ${S}/out/ca/* ${WORKDIR}/deploy/${bindir}
}

do_deploy() {
    cd ${WORKDIR}/deploy
    install -d ${DEPLOYDIR}

    tar -zcvf ${DEPLOYDIR}/optee-ta-fwu-${MACHINE}.tar.gz ./*
    tar -jcvf ${DEPLOYDIR}/optee-ta-fwu-${MACHINE}.tar.bz2 ./*
}

addtask deploy before do_build after do_install
