require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "109cf1ff72cc08584318a79eb0250db9b43bd91c"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.138-cip25-rt \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
