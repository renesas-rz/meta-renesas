DESCRIPTION = "VSP manager interface user module for the Renesas MPUs"

require vspmif.inc

DEPENDS = "kernel-module-vspm kernel-module-vspmif mmngr-user-module"
PN = "vspmif-user-module"
PR = "r0"
RDEPENDS:${PN} = "kernel-module-vspmif mmngr-user-module"

S = "${WORKDIR}/git"
VSPMIF_LIB_DIR = "vspm_if-module/files/vspm_if"

EXTRA_OEMAKE = "ARCH=${TARGET_ARCH}"

includedir = "${RENESAS_DATADIR}/include"

WS_aarch64 = ""
WS_virtclass-multilib-lib32 = "32"

vspm32_compile_export() {
    if [ X${WS} = "X32" ]; then
        export VSPM32="1"
    fi
    export VSPM_ISU="1"
}

do_compile:prepend:rzg2l-family() {
    vspm32_compile_export
}

do_compile:prepend:rzv2h-family() {
    vspm32_compile_export
}

do_compile:prepend:rzv2n-family() {
    vspm32_compile_export
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
