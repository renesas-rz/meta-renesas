KERNEL_URI ?= "git://github.com/renesas-rz/rz_linux-cip.git;protocol=https"
KERNEL_BRANCH ?= "rzt2h-5.10-cip17"
KERNEL_REV ?= "d84719598b26d50b5204cd5912b9e279dfdcf6ec"
RT-KERNEL_BRANCH ?= "rzt2h-5.10-cip17-rt7"
RT-KERNEL_REV ?= "ac7c7207c121146a314fd7324aa48fb476830af7"

BRANCH = "${@oe.utils.conditional("IS_RT_BSP", "1", "${RT-KERNEL_BRANCH}", "${KERNEL_BRANCH}",d)}"
SRCREV = "${@oe.utils.conditional("IS_RT_BSP", "1", "${RT-KERNEL_REV}", "${KERNEL_REV}",d)}"

SRC_URI = "${KERNEL_URI};branch=${BRANCH}"
