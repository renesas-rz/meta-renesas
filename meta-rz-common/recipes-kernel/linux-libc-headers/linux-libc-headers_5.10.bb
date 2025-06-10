require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL = " \
    git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "${@oe.utils.conditional("IS_RT_BSP", "1", "rz-5.10-cip54-rt23", "rz-5.10-cip54",d)}"
SRCREV = "${@oe.utils.conditional("IS_RT_BSP", "1", "bae6b8c28b0ad4490f23aa133a1ead15375ae8f7", "e0e940c3b804dcb159027cb5a1bc0b28102e7b43",d)}"
LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

FILESEXTRAPATHS_prepend := "${THISDIR}/../linux/linux-renesas:"

S = "${WORKDIR}/git"

# below overrides the multilib list - can be dropped for the next LTS
do_install_armmultilib () {
	oe_multilib_header asm/auxvec.h asm/bitsperlong.h asm/byteorder.h asm/fcntl.h asm/hwcap.h asm/ioctls.h asm/kvm_para.h asm/mman.h asm/param.h asm/perf_regs.h asm/bpf_perf_event.h
	oe_multilib_header asm/posix_types.h asm/ptrace.h  asm/setup.h  asm/sigcontext.h asm/siginfo.h asm/signal.h asm/stat.h  asm/statfs.h asm/swab.h  asm/types.h asm/unistd.h
}
