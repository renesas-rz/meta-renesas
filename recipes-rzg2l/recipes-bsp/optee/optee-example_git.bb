SUMMARY = "OP-TEE example"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit deploy python3native

LICENSE = "BSD & GPLv2"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=cd95ab417e23b94f381dafc453d70c30"

#TAG: 3.14.0
PV = "3.14.0+git${SRCPV}"
BRANCH = "master"
SRCREV = "e9c870525af8f7e7fccf575a0ca5394ce55adcec"

SRC_URI = " \
	git://github.com/linaro-swg/optee_examples.git;branch=${BRANCH} \
	file://git \
"

DEPENDS = "optee-os optee-client"
DEPENDS += "python3-pyelftools-native python3-pycryptodome-native python3-pycryptodomex-native"

TEEC_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TA_DEV_KIT_DIR = "${STAGING_INCDIR}/optee/export-user_ta/"

CFLAGS_prepend = "--sysroot=${STAGING_DIR_HOST}"

EXTRA_OEMAKE = " \
	TA_DEV_KIT_DIR=${TA_DEV_KIT_DIR} \
	TEEC_EXPORT=${TEEC_EXPORT} \
	HOST_CROSS_COMPILE=${TARGET_PREFIX} \
	PLUGIN_LDFLAGS="--sysroot=${STAGING_DIR_HOST} -shared" \
"

S = "${WORKDIR}/git"

do_compile() {
	oe_runmake examples
}

do_install[noexec] = "1"

do_deploy() {
	oe_runmake prepare-for-rootfs OUTPUT_DIR=${S}/out	
	
	install -d ${S}/deploy/bin
	install -d ${S}/deploy/lib/optee_armtz
	
	install -m 0755  ${S}/out/ca/* ${S}/deploy/bin/
	install -m 0755  ${S}/out/ta/* ${S}/deploy/lib/optee_armtz/
	
	cd ${S}/deploy
	install -d ${DEPLOYDIR}
	
	tar -zcvf ${DEPLOYDIR}/optee-example-${MACHINE}.tar.gz ./*
	tar -jcvf ${DEPLOYDIR}/optee-example-${MACHINE}.tar.bz2 ./*
}

addtask deploy before do_build after do_compile
