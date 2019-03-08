require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "3e70d30fbc190d25f68f3a1f605ad78e9e651b21"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.166-cip29 \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
