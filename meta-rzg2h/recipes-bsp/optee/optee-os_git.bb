DESCRIPTION = "OP-TEE OS"

LICENSE = "BSD-2-Clause & BSD-3-Clause"
LIC_FILES_CHKSUM = " \
    file://LICENSE;md5=c1f21c4f72f372ef38a5a4aee55ec173 \
"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit deploy python3native

PV = "3.15.0+git${SRCPV}"
BRANCH = "master"
#TAG: 3.15.0
SRCREV = "6be0dbcaa11394a2ad5a46ac77e2f76e31a41722"

SRC_URI = " \
    git://github.com/OP-TEE/optee_os.git;branch=${BRANCH} \
    file://0001-mk-gcc-allow-setting-sysroot-lookup.patch \
    file://0002-arch-plat-rzg-add-HW-Unique-Key-support-for-TEE-OTP.patch \
    file://0003-core-arm-plat-rzg-Add-ECC-mode-checking-for-shared-m.patch \
    file://0004-core-arch-plat-rzg-add-Suspend-To-RAM-feature.patch \
    file://0005-core-arm-plat-rzg-Add-Suspend-to-RAM-support-for-con.patch \
    file://0006-plat-rzg-add-some-missing-reference-functions.patch \
"

COMPATIBLE_MACHINE = "(ek874|hihope-rzg2m|hihope-rzg2n|hihope-rzg2h)"
PLATFORM = "rzg"
PLATFORM_FLAVOR = "${@d.getVar("MACHINE", False).replace("-", "_")}"

DEPENDS = "python3-pyelftools-native python3-pycryptodome-native python3-pycryptodomex-native"
export CROSS_COMPILE64="${TARGET_PREFIX}"

# Let the Makefile handle setting up the flags as it is a standalone application
LD[unexport] = "1"
LDFLAGS[unexport] = "1"
export CCcore="${CC}"
export LDcore="${LD}"
libdir[unexport] = "1"

S = "${WORKDIR}/git"

EXTRA_OEMAKE = " \
	PLATFORM=${PLATFORM} PLATFORM_FLAVOR=${PLATFORM_FLAVOR} \
	CFG_ARM64_core=y CFG_REE_FS=y CFG_RPMB_FS=n CFG_CRYPTO_WITH_CE=y \
	RZG_DRAM_ECC=${USE_ECC} RZG_ECC_FULL=${ECC_FULL} \
	LIBGCC_LOCATE_CFLAGS=--sysroot=${STAGING_DIR_HOST} \
	CROSS_COMPILE=${TARGET_PREFIX} \
"

do_compile() {
    oe_runmake
}

do_install() {
    #install TA devkit
    install -d ${D}/usr/include/optee/export-user_ta/

    for f in  ${B}/out/arm-plat-${PLATFORM}/export-ta_arm64/* ; do
        cp -aR  $f  ${D}/usr/include/optee/export-user_ta/
    done
}

do_deploy() {
    # Create deploy folder
    install -d ${DEPLOYDIR}

    # Copy TEE OS to deploy folder
    install -m 0644 ${S}/out/arm-plat-${PLATFORM}/core/tee.elf ${DEPLOYDIR}/tee-${MACHINE}.elf
    install -m 0644 ${S}/out/arm-plat-${PLATFORM}/core/tee-raw.bin ${DEPLOYDIR}/tee-${MACHINE}.bin
    # SREC file is generated from RAW bin and it has start address at 0x0,
    # so we must adjust it to our address for our platform before using it.
    objcopy --adjust-vma=0x44100000 -I srec -O srec \
	${S}/out/arm-plat-${PLATFORM}/core/tee.srec ${DEPLOYDIR}/tee-${MACHINE}.srec
}
addtask deploy before do_build after do_compile

FILES_${PN}-dev = "/usr/include/optee"

INSANE_SKIP_${PN}-dev = "staticdev"
