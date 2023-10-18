require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL=" \
	git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "rzg1-cip78-rt45"
SRCREV = "33ced8c7f3754ef14afda6d30d111d33bdd2e774"
SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

SRC_URI_append = " \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
