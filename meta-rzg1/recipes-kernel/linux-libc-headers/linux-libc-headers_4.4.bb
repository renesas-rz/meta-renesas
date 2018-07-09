require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "e768144c09a6fc08c3cde9451adf317e4ab0442d"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.130-cip23 \
"

S = "${WORKDIR}/git"
