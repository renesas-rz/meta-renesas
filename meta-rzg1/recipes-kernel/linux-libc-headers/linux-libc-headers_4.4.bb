require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "54596ca208c1bdafb83050baf8c721c21018851c"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.166-cip29-rt \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
