require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

LINUX_VERSION = "6.1.54-cip6"

SRC_URI = "git://git.kernel.org/pub/scm/linux/kernel/git/cip/linux-cip.git;protocol=https;branch=${KERNEL_BRANCH}"
KERNEL_BRANCH = "linux-6.1.y-cip"
SRCREV = "5f8461a2ec855187b1bab7e4aa419338772fe9bc"

LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

PV = "${LINUX_VERSION}+git${SRCPV}"

S = "${WORKDIR}/git"
