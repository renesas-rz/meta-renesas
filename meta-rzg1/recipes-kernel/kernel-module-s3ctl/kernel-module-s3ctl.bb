inherit module
require include/rz-modules-common.inc

LICENSE = "GPLv2 & MIT"
LIC_FILES_CHKSUM = " \
    file://drv/GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://drv/MIT-COPYING;md5=fea016ce2bdf2ec10080f69e9381d378 \
"
DEPENDS = "linux-renesas"
PN = "kernel-module-s3ctl"
PR = "r0"
SRC_URI = "file://s3ctl-kernel.tar.bz2"

S = "${WORKDIR}/s3ctl"
includedir = "${RENESAS_DATADIR}/include"

do_compile() {
    # Build kernel module
    cd ${S}/drv
    make all ARCH=arm
}

do_install() {
    # Create shared folder
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}/${includedir}

    # Copy kernel module
    install -m 644 ${S}/drv/s3ctl.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/

    # Copy shared header files
    install -m 644 ${S}/drv/Module.symvers ${D}/${includedir}/s3ctl.symvers
}

# Append function to clean extract source
do_cleansstate_prepend() {
        bb.build.exec_func('do_clean_source', d)
}

do_clean_source() {
    rm -rf ${KERNELSRC}/include/s3ctl_private.h
    rm -rf ${KERNELSRC}/include/s3ctl.symvers
}

PACKAGES = "\
    ${PN}-dev \
"

FILES_${PN}-dev = " \
    ${includedir}/ \
    ${includedir}/*.h \
    ${includedir}/s3ctl.symvers \
"

RPROVIDES_${PN} += "kernel-module-s3ctl"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

do_configure[noexec] = "1"

python do_package_ipk_prepend () {
    d.setVar('ALLOW_EMPTY', '1')
}

KERNEL_MODULE_AUTOLOAD = "s3ctl"
