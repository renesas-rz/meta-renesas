require include/rz-modules-common.inc

LICENSE = "CLOSED"
DEPENDS = "kernel-module-vspm"
PN = "vspm-user-module"
PR = "r0"
SRC_URI = "file://vspm-user.tar.bz2 \
"

S = "${WORKDIR}/vspm"

includedir = "${RENESAS_DATADIR}/include"
libdir = "${RENESAS_DATADIR}/lib"

do_compile() {
    # Build shared library
    cd ${S}/if
    rm -rf ${S}/if/libvspm.so*
    make all ARCH=arm
}

do_install() {
    # Create destination folder
    install -d ${D}/${includedir}
    install -d ${D}/${libdir}
    
    # Copy shared library
    install -m 755 ${S}/if/libvspm.so* ${D}/${libdir}/
    cd ${D}/${libdir}/
    ln -sf libvspm.so.1.5.0 libvspm.so.1
    ln -sf libvspm.so.1 libvspm.so

    # Copy shared header files
    install -m 644 ${S}/include/vspm_public.h ${D}/${includedir}/
    install -m 644 ${S}/include/tddmac_drv.h ${D}/${includedir}/
    install -m 644 ${S}/include/vsp_drv.h ${D}/${includedir}/
}

do_clean_source() {
    rm -f ${LIBSHARED}/libvspm.so*
    rm -f ${D}/${includedir}/vspm_public.h
    rm -f ${D}/${includedir}/tddmac_drv.h
    rm -f ${D}/${includedir}/vsp_drv.h
}

PACKAGES = "\
    ${PN} \
    ${PN}-dev \
"

FILES_${PN} = " \
    /usr/local/lib/libvspm.so.* \
"

FILES_${PN}-dev = " \
    /usr/local/lib \
    /usr/local/lib/libvspm.so \
    /usr/local/lib/* \
    /usr/local/include \
    /usr/local/include/*.h \
"

RPROVIDES_${PN} += "vspm-user-module"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INSANE_SKIP_${PN} += "libdir"
INSANE_SKIP_${PN}-dev += "libdir"
