COMPATIBLE_MACHINE_rzt2h = "(rzt2h-dev|rzn2h-dev)"

LINUX_VERSION = "${@oe.utils.conditional("IS_RT_BSP", "1", "5.10.145-cip17-rt7", "5.10.145-cip17",d)}"

KERNEL_URI ?= "git://github.com/renesas-rz/rz_linux-cip.git;protocol=https"
KERNEL_BRANCH ?= "rzt2h-5.10-cip17"
KERNEL_REV ?= "1c5832cafd2fe0ab967212552ffe013ab187705e"
RT-KERNEL_BRANCH ?= "rzt2h-5.10-cip17-rt7"
RT-KERNEL_REV ?= "d1076824de3cbffdd8db4428c1e6b65172123a4d"

BRANCH = "${@oe.utils.conditional("IS_RT_BSP", "1", "${RT-KERNEL_BRANCH}", "${KERNEL_BRANCH}",d)}"
SRCREV = "${@oe.utils.conditional("IS_RT_BSP", "1", "${RT-KERNEL_REV}", "${KERNEL_REV}",d)}"

SRC_URI = "${KERNEL_URI};branch=${BRANCH}"
