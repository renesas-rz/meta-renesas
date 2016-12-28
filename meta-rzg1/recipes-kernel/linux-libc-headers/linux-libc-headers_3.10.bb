require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KORG_ARCHIVE_COMPRESSION = "xz"
COMPATIBLE_MACHINE = "(skrzg1m|skrzg1e|iwg20m)"
PV_append = "+git${SRCREV}"

RENESAS_BACKPORTS_URL="git://git.kernel.org/pub/scm/linux/kernel/git/horms/renesas-backport.git"
SRCREV = "34547b2a5032ce6dca24b745d608d2f3baac187f"
SRC_URI = " \
    ${RENESAS_BACKPORTS_URL};protocol=git;branch=bsp/v3.10.31-ltsi/rcar-gen2-1.9.8 \
    file://scripts-Makefile.headersinst-install-headers-from-sc.patch \
"
S = "${WORKDIR}/git"
