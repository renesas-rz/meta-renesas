require include/rzg2h-security-config.inc
inherit deploy

SUMMARY = "RZ/G2H Security Module"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${S}/LICENSE.txt;md5=64d0b525014dc2f5318d56db69fd314e"

BRANCH = "master"
SRCREV = "e8e742054444feb0ef24a688c473568446b847b7"

SRC_URI = "git://github.com/renesas-rz/rzg_security-module.git;branch=${BRANCH};protocol=https"

PACKAGE_ARCH = "${MACHINE_ARCH}"

S = "${WORKDIR}/git"

LSI_OPT_r8a774c0 = "LSI=G2E"
LSI_OPT_r8a774a1 = "LSI=G2M"
LSI_OPT_r8a774b1 = "LSI=G2N"
LSI_OPT_r8a774e1 = "LSI=G2H"
LSI_OPT_append += " SEC_LIB_DIR=${SYMLINK_NATIVE_SEC_LIB_DIR}"

DEPENDS += "secprv-native"

do_compile() {
    oe_runmake ${LSI_OPT}
}

do_deploy() {
    install -d ${DEPLOYDIR}
    install -m 0644 ${B}/out/sec_module.elf  ${DEPLOYDIR}/sec_module-${MACHINE}.elf
    install -m 0644 ${B}/out/sec_module.srec ${DEPLOYDIR}/sec_module-${MACHINE}.srec
    install -m 0644 ${B}/out/sec_module.bin  ${DEPLOYDIR}/sec_module-${MACHINE}.bin
}
addtask deploy before do_build after do_compile
