#
# base recipe: meta/recipes-core/busybox/busybox_1.22.1.bb
# base branch: daisy
#

PR = "r0"

inherit debian-package
PV = "1.22.0"
include busybox.inc

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=de10de48642ab74318e893a61105afbb"


# busybox-appletlib-dependency.patch: avoid build process races
# 0001-build-system...patch: required for cross compiling
# defconfig: based on ${S}/debian/config/pkg/deb, and some configs are modified
#            so that the default system works correctly (see header comments)
SRC_URI += " \
file://busybox-appletlib-dependency.patch \
file://0001-build-system-Specify-nostldlib-when-linking-to-.o-fi.patch \
file://0001-menuconfig-check-lxdiaglog.sh-Allow-specification-of.patch \
file://defconfig \
file://inittab \
file://rcS \
file://run-ptest \
file://hwclock.sh \
"
