require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

PV_append = "+git${SRCREV}"

# NOTE: DON'T set compatible machine as it will prevent the nativesdk package (x86)
#COMPATIBLE_MACHINE = "(skrzg1m|skrzg1e)"

RENESAS_URL="git://git.kernel.org/pub/scm/linux/kernel/git/bwh/linux-cip.git"
SRCREV = "a09e49b41e1bb15e0ec04a8a3b92728de7310c96"
SRC_URI = " \
    ${RENESAS_URL};protocol=git;branch=linux-4.4.y-cip \
"
S = "${WORKDIR}/git"
