require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

PV_append = "+git${SRCREV}"

# NOTE: DON'T set compatible machine as it will prevent the nativesdk package (x86)
#COMPATIBLE_MACHINE = "(skrzg1m|skrzg1e)"

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "c7db59efd08b54f31dc4524f505ff741acb958ab"
SRC_URI = " \
    ${RENESAS_URL};protocol=git;branch=rvc/g1e-dev \
"
S = "${WORKDIR}/git"
