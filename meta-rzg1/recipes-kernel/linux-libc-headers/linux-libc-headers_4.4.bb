require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "3e632bfaaef838eb7aefb0e050b9fde6243bbd79"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.130-cip23 \
"

S = "${WORKDIR}/git"
