require conf/machine/include/${SOC_FAMILY}.inc

MACHINEOVERRIDES =. "rzfive:"

BBMASK_append = " recipes-rzg2h|recipes-rzv2l|recipes-rzg2l"

MACHINE_FEATURES = ""

KERNEL_IMAGETYPE = "Image"
IMAGE_FSTYPES_append = " tar.bz2 ext4"

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
PREFERRED_VERSION_u-boot = "v2020.10%"
EXTRA_IMAGEDEPENDS += " u-boot"

PACKAGE_INSTALL_remove += " optee-client v4l2-init "
