require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL=" \
	git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "${@bb.utils.contains("IS_RT_BSP", "1", "rzg1-cip91-rt51", "rzg1-cip91",d)}"
SRCREV = "${@bb.utils.contains("IS_RT_BSP", "1", "f2066231519dffe3eb1028f60d43f5803a5d5ee5", "b03384e148d17040bad23850205203ba083c9587",d)}"
SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

SRC_URI_append = " \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
