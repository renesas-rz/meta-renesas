DESCRIPTION = "Memory Manager User module for Renesas RZG2"
require mmngr_lib.inc
require include/rz-path-common.inc

DEPENDS = "kernel-module-mmngr"
PN = "mmngr-user-module"
PR = "r0"

S = "${WORKDIR}/git/libmmngr/mmngr"

EXTRA_OECONF =  "${@bb.utils.contains("DISTRO_FEATURES", "mm-test", \
    " --enable-mmngr-test", "", d)}"

exec_prefix = "/usr"
bindir = "${RENESAS_DATADIR}/bin"
includedir = "${RENESAS_DATADIR}/include"
CFLAGS += " -I${STAGING_DIR_HOST}${RENESAS_DATADIR}/include"

CFLAGS += " ${@oe.utils.conditional('USE_32BIT_PKGS', '1', ' -I${STAGING_KERNEL_DIR}/include ', '', d)} "

do_install_append() {
    if [ -f ${D}${RENESAS_DATADIR}/bin/mmtp ]; then
        if [ X${WS} = "X32" ]; then
            mv ${D}${RENESAS_DATADIR}/bin/mmtp ${D}${RENESAS_DATADIR}/bin/mmtp${WS}
        fi
    fi
}
