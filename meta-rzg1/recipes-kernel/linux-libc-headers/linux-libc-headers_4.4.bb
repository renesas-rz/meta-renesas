require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

PV_append = "+git${SRCREV}"

# NOTE: DON'T set compatible machine as it will prevent the nativesdk package (x86)
#COMPATIBLE_MACHINE = "(skrzg1m|skrzg1e)"

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "4b349464f0d9051954bfc45eb0d4f2df53be27d9"
SRC_URI = " \
    ${RENESAS_URL};protocol=git;branch=rvc/g1e-dev \
"
S = "${WORKDIR}/git"
