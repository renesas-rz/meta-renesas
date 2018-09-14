require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "16760d87d7018527f2b13f9730418f8a99912d0d"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.138-cip25-rt \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
