require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL=" \
	git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "rzg1-cip69-rt39"
SRCREV = "696dbb597252c55e975ae73d7c214459633a8334"
SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

SRC_URI_append = " \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
