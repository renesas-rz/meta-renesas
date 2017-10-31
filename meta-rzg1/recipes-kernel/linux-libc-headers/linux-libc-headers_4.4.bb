require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

PV_append = "+git${SRCREV}"

# NOTE: DON'T set compatible machine as it will prevent the nativesdk package (x86)
#COMPATIBLE_MACHINE = "(skrzg1m|skrzg1e)"

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "21bafd4f4a5523a685287b81a492f2618a92b4e2"
SRC_URI = " \
    ${RENESAS_URL};protocol=git;branch=v4.4.55-cip3 \
"
S = "${WORKDIR}/git"
