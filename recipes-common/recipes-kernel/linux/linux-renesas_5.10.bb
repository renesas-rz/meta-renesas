DESCRIPTION = "Linux kernel for the RZG2 based board"

require recipes-kernel/linux/linux-yocto.inc
require include/docker-control.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"
COMPATIBLE_MACHINE_rzg2l = "(smarc-rzg2l|smarc-rzg2lc|smarc-rzg2ul)"
COMPATIBLE_MACHINE_rzg2h = "(ek874|hihope-rzg2n|hihope-rzg2m|hihope-rzg2h)"

KERNEL_URL = " \
    git://github.com/renesas-rz/rz_linux-cip.git"
BRANCH = "${@oe.utils.conditional("IS_RT_BSP", "1", "rz-5.10-cip1-rt1", "rz-5.10-cip1",d)}"
SRCREV = "${@oe.utils.conditional("IS_RT_BSP", "1", "d3a19ad536dcb7b0443744a517bcdb0ee4753b87", "b722cdfbbd89867847300ce08b2185c3deaf1840",d)}"

SRC_URI = "${KERNEL_URL};protocol=https;nocheckout=1;branch=${BRANCH}"
LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"
LINUX_VERSION ?= "${@oe.utils.conditional("IS_RT_BSP", "1", "5.10.83-cip1-rt1", "5.10.83-cip1",d)}"

PV = "${LINUX_VERSION}+git${SRCPV}"
PR = "r1"

SRC_URI_append = "\
  ${@oe.utils.conditional("USE_DOCKER", "1", " file://docker.cfg ", "", d)} \
"

KBUILD_DEFCONFIG = "defconfig"
KCONFIG_MODE = "alldefconfig"

do_kernel_metadata_af_patch() {
	# need to recall do_kernel_metadata after do_patch for some patches applied to defconfig
	rm -f ${WORKDIR}/defconfig
	do_kernel_metadata
}

addtask do_kernel_metadata_af_patch after do_patch before do_kernel_configme

# Fix race condition, which can causes configs in defconfig file be ignored
do_kernel_configme[depends] += "virtual/${TARGET_PREFIX}binutils:do_populate_sysroot"
do_kernel_configme[depends] += "virtual/${TARGET_PREFIX}gcc:do_populate_sysroot"
do_kernel_configme[depends] += "bc-native:do_populate_sysroot bison-native:do_populate_sysroot"

# Fix error: openssl/bio.h: No such file or directory
DEPENDS += "openssl-native"
