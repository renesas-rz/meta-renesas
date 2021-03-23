DESCRIPTION = "Linux kernel for the RZG2 based board"

require recipes-kernel/linux/linux-yocto.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"
COMPATIBLE_MACHINE = "rzg2l-dev"

KERNEL_URL = "git://github.com/renesas-rz/rzg_linux-cip_private.git"
SRCREV = "23bddb51499156a869c137486c992c9fbc1a7d44"
BRANCH = "rvc/rzg2l-cip33"

# When using private git repo, you can append ";user=username:password" to SRC_URI
# to download the remote repo.
SRC_URI = "${KERNEL_URL};protocol=https;branch=${BRANCH}"

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"
LINUX_VERSION ?= "4.19.140"

PV = "${LINUX_VERSION}+git${SRCPV}"
PR = "r1"

KBUILD_DEFCONFIG = "defconfig"
KCONFIG_MODE = "alldefconfig"
LINUX_DEFCONFIG = "defconfig"

# Fix error: openssl/bio.h: No such file or directory
#DEPENDS += "openssl-native"
