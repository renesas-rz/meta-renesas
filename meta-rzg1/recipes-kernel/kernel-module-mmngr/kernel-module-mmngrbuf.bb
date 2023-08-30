inherit module
require include/rz-modules-common.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://drv/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://drv/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
    file://include/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://include/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"

DEPENDS = "linux-renesas"
PN = "kernel-module-mmngrbuf"
PR = "r0"

SRC_URI = "file://mmngrbuf.tar.bz2"

S = "${WORKDIR}/mmngrbuf"
includedir = "${RENESAS_DATADIR}/include"

do_compile() {
    cd ${S}/drv
    make all ARCH=arm
}

do_install () {
    # Create destination folders
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Copy shared library for reference from other modules
    install -m 644 ${S}/drv/Module.symvers ${KERNELSRC}/include/mmngrbuf.symvers
    install -m 644 ${S}/drv/Module.symvers ${D}/${includedir}/mmngrbuf.symvers

    # Copy kernel module
    install -m 644 ${S}/drv/mmngrbuf.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/
}

# Append function to clean extract source
do_cleansstate_prepend() {
        bb.build.exec_func('do_clean_source', d)
}

do_clean_source() {
    rm -f ${KERNELSRC}/include/mmngr_buf_private.h
    rm -f ${KERNELSRC}/include/mmngrbuf.symvers
}

PACKAGES = "\
    ${PN}-dev \
"

FILES_${PN}-dev = " \
    ${includedir}/mmngrbuf.symvers \
"

RPROVIDES_${PN} += "kernel-module-mmngrbuf"

python do_package_ipk_prepend () {
    d.setVar('ALLOW_EMPTY', '1')
}

KERNEL_MODULE_AUTOLOAD = "mmngrbuf"
