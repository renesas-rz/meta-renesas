SUMMARY = "OP-TEE sanity testsuite"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit deploy python3native

LICENSE = "BSD & GPLv2"
LIC_FILES_CHKSUM = "file://${S}/LICENSE.md;md5=daa2bcccc666345ab8940aab1315a4fa"

#TAG: 3.15.0
PV_rzg2h = "3.15.0+git${SRCPV}"
SRCREV_rzg2h = "f88f69eb27beda52998de09cd89a7ee422da00d9"
#TAG: 3.17.0
PV_rzg2l = "3.17.0+git${SRCPV}"
SRCREV_rzg2l = "44a31d02379bd8e50762caa5e1592ad81e3339af"

BRANCH = "master"

SRC_URI = " \
	git://github.com/OP-TEE/optee_test.git;branch=${BRANCH} \
"

DEPENDS = "optee-os optee-client"
DEPENDS += "python3-pyelftools-native python3-pycryptodome-native python3-pycryptodomex-native"

OPTEE_CLIENT_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TA_DEV_KIT_DIR = "${STAGING_INCDIR}/optee/export-user_ta/"

CFLAGS_prepend = "--sysroot=${STAGING_DIR_HOST}"

EXTRA_OEMAKE = " \
	TA_DEV_KIT_DIR=${TA_DEV_KIT_DIR} \
	OPTEE_CLIENT_EXPORT=${OPTEE_CLIENT_EXPORT} \
	CROSS_COMPILE=${TARGET_PREFIX} \
	V=1 \
"

S = "${WORKDIR}/git"

do_compile() {
    oe_runmake xtest
    oe_runmake ta
    oe_runmake test_plugin
}

do_install[noexec] = "1"

do_deploy() {
    oe_runmake install DESTDIR=${S}/deploy

    cd ${S}/deploy
    install -d ${DEPLOYDIR}

    tar -zcvf ${DEPLOYDIR}/optee-test-${MACHINE}.tar.gz ./*
    tar -jcvf ${DEPLOYDIR}/optee-test-${MACHINE}.tar.bz2 ./*
}

addtask deploy before do_build after do_compile
