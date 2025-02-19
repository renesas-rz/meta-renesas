DESCRIPTION = "VSP Manager Interface library for RZG2L/RZG3E"

require vspmif.inc

DEPENDS = "kernel-module-vspmif mmngr-user-module"
PN = "vspmif-user-module"
PR = "r0"

S = "${WORKDIR}/git"
VSPMIF_LIB_DIR = "vspm_if-module/files/vspm_if"

EXTRA_OEMAKE = "ARCH=${TARGET_ARCH}"

includedir = "${RENESAS_DATADIR}/include"

WS_aarch64 = ""
WS_virtclass-multilib-lib32 = "32"

SRC_URI:append:rzg2l-family = " \
    file://0001-Modify-vspm_public.h-for-ISUM.patch \
    file://0002-Modify-Makefile-for-building-vspm_api_isu.patch \
    file://0003-Add-vspm_api_isu.c-for-ISUM.patch \
    file://0004-Support-libvspm-32bit.patch \
    file://0005-vspm_api_isu-Free-callback-vspmif-data-after-finishi.patch \
    file://0006-Update-copyright-year-for-changed-files.patch \
"

do_compile:prepend:rzg2l-family() {
    if [ X${WS} = "X32" ]; then
        export VSPM32="1"
    fi
}

do_compile() {
    export VSPM_LEGACY_IF="1"

    # Build shared library
    cd ${S}/${VSPMIF_LIB_DIR}/if
    rm -rf ${S}/${VSPMIF_LIB_DIR}/if/libvspm.so*
    oe_runmake
}

do_install() {
    # Create destination folders
    install -d ${D}/${libdir}
    install -d ${D}/${includedir}

    # Copy shared library
    install -m 755 ${S}/${VSPMIF_LIB_DIR}/if/libvspm.so* ${D}/${libdir}/
    cd ${D}/${libdir}/
    ln -sf libvspm.so.1.0.0 libvspm.so.1
    ln -sf libvspm.so.1 libvspm.so

    # Copy shared header files
    install -m 644 ${S}/${VSPMIF_LIB_DIR}/include/vspm_public.h ${D}/${includedir}/
    install -m 644 ${S}/${VSPMIF_LIB_DIR}/include/fdpm_api.h ${D}/${includedir}/
}

PACKAGES = "\
    ${PN} \
    ${PN}-dev \
    ${PN}-dbg \
"

RPROVIDES:${PN} += "vspmif-user-module"
INSANE_SKIP:${PN} += "libdir"
INSANE_SKIP:${PN}-dev += "libdir"
