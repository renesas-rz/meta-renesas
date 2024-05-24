require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL=" \
	git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "${@bb.utils.contains("IS_RT_BSP", "1", "rzg1-cip87-rt49", "rzg1-cip87",d)}"
SRCREV = "${@bb.utils.contains("IS_RT_BSP", "1", "cb3c1256ae5ddc367327f1dc267b946cc7106b93", "bc8690b978b52db35a4489e4a7cced069f850eff",d)}"
SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

SRC_URI_append = " \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
