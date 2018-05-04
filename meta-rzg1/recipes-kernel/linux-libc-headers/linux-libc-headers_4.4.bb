require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

PV_append = "+git${SRCREV}"

# NOTE: DON'T set compatible machine as it will prevent the nativesdk package (x86)
#COMPATIBLE_MACHINE = "(skrzg1m|skrzg1e)"

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "420a803841324811c2bd47a87c29aa34381acb1b"
SRC_URI = " \
    ${RENESAS_URL};protocol=git;branch=v4.4.55-cip3 \
"
S = "${WORKDIR}/git"
