require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL = " \
	git://git.kernel.org/pub/scm/linux/kernel/git/cip/linux-cip.git"
BRANCH = "linux-4.4.y-cip-rt"
SRCREV = "78fba2cb0d1a53e593417cbd63e20924f01be5e5"
SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

SRC_URI_append = " \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
