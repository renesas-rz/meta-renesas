require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "724ae629f42a0abc36e1e45e8cfb0abb951236a1"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.166-cip29 \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
