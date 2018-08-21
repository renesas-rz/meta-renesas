require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "a6b7743ea54e2a3dc4a3750ba09917801f6ffaaf"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.138-cip25-rt \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
