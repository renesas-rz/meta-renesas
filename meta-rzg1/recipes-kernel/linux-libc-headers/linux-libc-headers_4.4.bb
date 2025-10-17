require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL=" \
	git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "${@bb.utils.contains("IS_RT_BSP", "1", "rzg1-cip102-rt57", "rzg1-cip102",d)}"
SRCREV = "${@bb.utils.contains("IS_RT_BSP", "1", "2072aaab7861228946346229b41aeec34fc3f4f1", "a6e2e06c37645977643b18874a64db3046123d67",d)}"
SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

SRC_URI_append = " \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
