SUMMARY = "RZ/G2 OPTEE TA FWU"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${S}/LICENSE.md;md5=6dfbd335e1a8e28d20df79f57587cabc"

PACKAGE_ARCH = "${MACHINE_ARCH}"
PN = "optee-ta-fwu"

OPTEE_TA_FWU_URL = "git://github.com/renesas-rz/rzg_optee-ta_fwu.git"
BRANCH = "main"

SRC_URI = "${OPTEE_TA_FWU_URL};branch=${BRANCH};protocol=https" 
SRCREV = "f8ba5724eeb74e76228c05983f4d5c0f86bc5e38"

inherit deploy python3native

DEPENDS = "optee-os optee-client"
DEPENDS += "python3-pyelftools-native python3-pycryptodome-native python3-pycryptodomex-native"

OPTEE_CLIENT_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TEEC_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TA_DEV_KIT_DIR = "${STAGING_INCDIR}/optee/export-user_ta/"
INSANE_SKIP_${PN} = "ldflags"
INSANE_SKIP_${PN}-dev = "ldflags"

CFLAGS_prepend = "--sysroot=${STAGING_DIR_HOST}"

EXTRA_OEMAKE = " \
	TA_DEV_KIT_DIR=${TA_DEV_KIT_DIR} \
	TEEC_EXPORT=${TEEC_EXPORT} \
	OPTEE_CLIENT_EXPORT=${OPTEE_CLIENT_EXPORT} \
	HOST_CROSS_COMPILE=${TARGET_PREFIX} \
	TA_CROSS_COMPILE=${TARGET_PREFIX} \
	V=1 \
"

S = "${WORKDIR}/git"

do_compile() {
    oe_runmake
}

do_install () {

    mkdir -p ${D}${nonarch_base_libdir}/optee_armtz
    mkdir -p ${D}${bindir}

    install -p -m 0755 ${S}/host/fwu ${D}${bindir}
    install -p -m 0444 ${S}/ta/*.ta ${D}${nonarch_base_libdir}/optee_armtz
}

addtask install after do_compile 

do_deploy() {
    cd ${D}
    install -d ${DEPLOYDIR}

    tar -zcvf ${DEPLOYDIR}/optee-ta-fwu-${MACHINE}.tar.gz ./*
    tar -jcvf ${DEPLOYDIR}/optee-ta-fwu-${MACHINE}.tar.bz2 ./*
}

PACKAGES = " \
    ${PN} \
    ${PN}-dbg \
"
FILES_${PN} += " \
    ${bindir}/fwu \
    ${nonarch_base_libdir}/optee_armtz/*.ta \
    /usr/src/* \
    /usr/bin/.debug/* \
"

FILES_${PN}-dbg += "${bindir}/.debug"

addtask deploy before do_build after do_install
