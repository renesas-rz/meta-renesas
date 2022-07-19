require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL=" \
	git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "rzg1-cip69"
SRCREV = "74075a0636728ae6f786a9fa65b043039043c5ae"
SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

SRC_URI_append = " \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
