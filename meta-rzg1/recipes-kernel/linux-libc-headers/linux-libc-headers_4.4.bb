require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL=" \
	git://git.kernel.org/pub/scm/linux/kernel/git/cip/linux-cip.git"
SRCREV = "5cbc4325387063f3b0baa6a14689554cb2dc8705"
SRC_URI = " \
	${KERNEL_URL};protocol=git;branch=linux-4.4.y-cip \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
