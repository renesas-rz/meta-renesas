KERNEL_URL = " \
    git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "${@oe.utils.conditional("IS_RT_BSP", "1", "rzg3s-cip17-rt7", "rzg3s-cip17",d)}"
SRCREV = "${@oe.utils.conditional("IS_RT_BSP", "1", "14ec0928ebe91d323c103eeb68a5118d04eaea8e", "bbd33951a02e7d6b70532ad919be6003ac137ac6",d)}"
