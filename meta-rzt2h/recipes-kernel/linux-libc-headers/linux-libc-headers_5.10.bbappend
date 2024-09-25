KERNEL_URI ?= "git://github.com/renesas-rz/rz_linux-cip.git;protocol=https"
KERNEL_BRANCH ?= "rzt2h-5.10-cip17"
KERNEL_REV ?= "80a74652b6e46c5121de85bf71b99fa4d11fdc7c"
RT-KERNEL_BRANCH ?= "rzt2h-5.10-cip17-rt7"
RT-KERNEL_REV ?= "cdf7f7f2d1b4399584987ad82ae776cb6f1e6507"

BRANCH = "${@oe.utils.conditional("IS_RT_BSP", "1", "${RT-KERNEL_BRANCH}", "${KERNEL_BRANCH}",d)}"
SRCREV = "${@oe.utils.conditional("IS_RT_BSP", "1", "${RT-KERNEL_REV}", "${KERNEL_REV}",d)}"

SRC_URI = "${KERNEL_URI};branch=${BRANCH}"
