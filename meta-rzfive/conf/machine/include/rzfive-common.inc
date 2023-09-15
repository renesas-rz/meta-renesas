require conf/machine/include/${SOC_FAMILY}.inc
require include/ecc-control.inc

MACHINEOVERRIDES =. "rzfive:"

MACHINE_FEATURES = ""

KERNEL_IMAGETYPE = "Image"
IMAGE_FSTYPES_append = " tar.bz2 ext4"
IMAGE_FSTYPES_append = " ${@oe.utils.conditional("WKS_SUPPORT", "1", "wic.gz wic.bmap", "", d)} "

SERIAL_CONSOLES = "115200;ttySC0"

# Configuration for OPENSBI
EXTRA_IMAGEDEPENDS += " opensbi"

# Add variable to Build Configuration in build log
BUILDCFG_VARS_append = " SOC_FAMILY"

# We must disable ptest when can not use GPLv3 License,
# ptest require many package, which have GPLv3 License,
DISTRO_FEATURES_remove += "${@bb.utils.contains("INCOMPATIBLE_LICENSE", "GPLv3", "ptest", "",d)}"

# Match version between native and target sysroot in meta-gplv2 when not using GPLv3.
PREFERRED_VERSION_gdbm-native ?= "${@bb.utils.contains("INCOMPATIBLE_LICENSE", "GPLv3", "1.8.3", "",d)}"

# u-boot
PREFERRED_VERSION_u-boot = "v2021.10%"
EXTRA_IMAGEDEPENDS += " u-boot"

PACKAGE_INSTALL_remove += " optee-client v4l2-init "

DISTRO_FEATURES_append = " docker"

# All related Docker packages setting
GOVERSION = "${@'1.16' if 'docker' in '${DISTRO_FEATURES}' else '1.14'}"
PREFERRED_VERSION_go = "${GOVERSION}"
PREFERRED_VERSION_containerd-opencontainers = "v1.6.8%"
PREFERRED_VERSION_docker-ce = "20.10.17-ce%"
PREFERRED_VERSION_runc-docker = "1.1.3%"
