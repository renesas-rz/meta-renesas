DESCRIPTION = "RGX/SGX kernel module"
LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://GPL-COPYING;md5=60422928ba677faaa13d6ab5f5baaa1e \
    file://MIT-COPYING;md5=8c2810fa6bfdc5ae5c15a0c1ade34054 \
"
DEPENDS = "linux-renesas"
PN = "kernel-module-gles"
PR = "r0"

COMPATIBLE_MACHINE = "(r8a7742|r8a7743|r8a7744|r8a7745|r8a77470)"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI_r8a7742 = " \
        file://RGX_KM_H2.tar.bz2 \
        file://0001-kernel-modules-gles-correct-number-of-argument-when-.patch \
"
S_r8a7742 = "${WORKDIR}/rogue_km"
KERNEL_SRC_PATH_r8a7742 = "build/linux/r8a7742_linux"
KERNEL_OLD_SRC_PATH_r8a7742 = "build/linux/r8a7790_linux/"
TARGET_PATH_r8a7742 = "rogue_km/binary_r8a7742_linux_release/target/kbuild/"

SRC_URI_r8a7743 = " \
        file://SGX_KM_M2.tar.bz2 \
        file://0002-kernel-modules-gles-correct-number-of-argument-when-.patch \
"
S_r8a7743 = "${WORKDIR}/eurasia_km"
KERNEL_SRC_PATH_r8a7743 = "eurasiacon/build/linux2/r8a7743_linux/"
KERNEL_OLD_SRC_PATH_r8a7743 = "eurasiacon/build/linux2/r8a7791_linux/"
TARGET_PATH_r8a7743 = "eurasia_km/eurasiacon/binary2_r8a7743_linux_release/target/kbuild"

SRC_URI_r8a7744 = " \
        file://SGX_KM_M2.tar.bz2 \
        file://0002-kernel-modules-gles-correct-number-of-argument-when-.patch \
"
S_r8a7744 = "${WORKDIR}/eurasia_km"
KERNEL_SRC_PATH_r8a7744 = "eurasiacon/build/linux2/r8a7743_linux/"
KERNEL_OLD_SRC_PATH_r8a7744 = "eurasiacon/build/linux2/r8a7791_linux/"
TARGET_PATH_r8a7744 = "eurasia_km/eurasiacon/binary2_r8a7743_linux_release/target/kbuild"


SRC_URI_r8a7745 = " \
        file://SGX_KM_E2.tar.bz2 \
        file://0002-kernel-modules-gles-correct-number-of-argument-when-.patch \
"
S_r8a7745 = "${WORKDIR}/eurasia_km"
KERNEL_SRC_PATH_r8a7745 = "eurasiacon/build/linux2/r8a7745_linux/"
KERNEL_OLD_SRC_PATH_r8a7745 = "eurasiacon/build/linux2/r8a7794_linux/"
TARGET_PATH_r8a7745 = "eurasia_km/eurasiacon/binary2_r8a7745_linux_release/target/kbuild"


SRC_URI_r8a77470 = " \
        file://SGX_KM_C2.tar.bz2 \
        file://0002-kernel-modules-gles-correct-number-of-argument-when-.patch \
"
S_r8a77470 = "${WORKDIR}/eurasia_km"
KERNEL_SRC_PATH_r8a77470 = "eurasiacon/build/linux2/r8a77470_linux/"
KERNEL_OLD_SRC_PATH_r8a77470 = "eurasiacon/build/linux2/r8a7794X_linux/"
TARGET_PATH_r8a77470 = "eurasia_km/eurasiacon/binary2_r8a77470_linux_release/target/kbuild"


GLES = "${@bb.utils.contains('MACHINE_FEATURES', 'rgx', 'rgx', \
    bb.utils.contains('MACHINE_FEATURES', 'sgx', 'sgx', '', d), d)}"

RPROVIDES_${PN} += "${GLES}-kernel-module"

inherit module
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

###do_patch[noexec] = "1"
do_configure[noexec] = "1"
#do_populate_lic[noexec] = "1"


export LANG = "C"
export BUILDDIR = "${STAGING_INCDIR}/.."
export LIBSHARED = "${STAGING_LIBDIR}"
export KERNELSRC = "${STAGING_KERNEL_DIR}"
export CROSS_COMPILE = "${TARGET_PREFIX}"
export KERNELDIR = "${KBUILD_OUTPUT}"
export LDFLAGS=""
export CP = "cp"

# Append function to clean extract source
do_cleansstate_prepend() {
        bb.build.exec_func('do_clean_source', d)
}


do_compile() {
    if [ -e "${S}/${KERNEL_OLD_SRC_PATH}"  ]; then 
    mv ${S}/${KERNEL_OLD_SRC_PATH}  ${S}/${KERNEL_SRC_PATH}
    fi
    cd ${S}/${KERNEL_SRC_PATH}
    unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
    make kbuild ARCH=arm DISCIMAGE=${D}
}

do_install() {
    export DISCIMAGE=${D}
    mkdir -p ${D}/lib/modules/${KERNEL_VERSION}

    cd ${S}/${KERNEL_SRC_PATH}

    unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
    make kbuild_install ARCH=arm DISCIMAGE=${D}
    mkdir -p  ${D}/usr/src/kernel/include
    cp -f ${WORKDIR}/${TARGET_PATH}/Module.symvers \
        ${D}/usr/src/kernel/include/${GLES}.symvers
}

do_clean_source() {
    rm -Rf ${KERNELSRC}/include/${GLES}.symvers
}

FILES_${PN}-dev = " \
    /usr/src/kernel/include/${GLES}.symvers \
"

PACKAGES = "\
    ${PN} \
    ${PN}-dev \
"
