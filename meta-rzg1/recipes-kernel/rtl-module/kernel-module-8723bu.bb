inherit module

export BUILDDIR = "${STAGING_INCDIR}/.."
export LIBSHARED = "${STAGING_LIBDIR}"
export KERNELSRC = "${STAGING_KERNEL_DIR}"
export CROSS_COMPILE = "${TARGET_PREFIX}"
export KERNELDIR = "${STAGING_KERNEL_DIR}"
export LDFLAGS = ""
export CP = "cp"

SUMMARY = "Realtek 8723bu wifi driver"
HOMEPAGE = "https://github.com/lwfinger/rtl8723bu/"
LICENSE = "OPEN"

# This package actually has no License file. Below is dummy info to build
LIC_FILES_CHKSUM = "file://git/README.md;md5=7967f55fbefa3330942afef996a272db "

SRC_URI = "git://github.com/lwfinger/rtl8723bu.git;protocol=git \
        file://0001-makefile-fix-bug-when-compile.patch \
"
SRCREV = "e2d0baa0b71227ad3814acba779fb29bc344c0be"

S = "${WORKDIR}"

DEPENDS = "linux-renesas"

do_patch() {
    cd ${S}/git
    git apply ../*.patch
}

do_compile() {
    cd ${S}/git
    make
}

do_install() {
    cd ${S}/git
    mkdir -p ${D}/lib/modules/${KERNEL_VERSION}/extra/ 
    cp -f 8723bu.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/
}


FILES_${PN} = " \
  /lib \
  /lib/modules \
  /lib/modules/${KERNEL_VERSION}/extra \
  /lib/modules/${KERNEL_VERSION}/extra/8723bu.ko \
"
FILES_${PN}-dbg += " \
  /lib/modules/${KERNEL_VERSION}/extra/.debug \
  /lib/modules/${KERNEL_VERSION}/extra/.debug/8723bu.ko \
 "