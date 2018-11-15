require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "3baa972487eb15c13dff27054615c4bba3999576"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.138-cip25-rt \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
