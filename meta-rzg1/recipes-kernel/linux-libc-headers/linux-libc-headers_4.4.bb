require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "79f8a920af486ed07283dbe7159e68ee3c19d19c"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.55-cip3 \
"

S = "${WORKDIR}/git"
