require conf/machine/include/${SOC_FAMILY}.inc

# 32BIT package install (default is disable)
# This variables can be used only in multilib.
USE_32BIT_PKGS ?= "0"
USE_32BIT_WAYLAND ?= "0"
USE_32BIT_MMP ?= "0"

MACHINE_FEATURES = ""

KERNEL_IMAGETYPE = "Image"
IMAGE_FSTYPES_append = " tar.bz2 ext4"

SERIAL_CONSOLES = "115200;ttySC0"

# Device tree: support multiple dtb files for all variant RZ/G2L and RZ/G2LC
KERNEL_DEVICETREE = " \
   renesas/r9a07g044l2-dev.dtb \
   renesas/r9a07g044l2-smarc.dtb \
   renesas/r9a07g044c2-dev.dtb \
   renesas/r9a07g044c2-smarc.dtb \
"

# Configuration for ARM Trusted Firmware
EXTRA_IMAGEDEPENDS += " trusted-firmware-a"

# u-boot
PREFERRED_VERSION_u-boot = "v2020.10%"
EXTRA_IMAGEDEPENDS += " u-boot"

# Add variable to Build Configuration in build log
BUILDCFG_VARS_append = " SOC_FAMILY"

PREFERRED_PROVIDER_virtual/libgles1 = "mali-user-module"
PREFERRED_PROVIDER_virtual/libgles2 = "mali-user-module"
PREFERRED_PROVIDER_virtual/egl = "mali-user-module"
PREFERRED_PROVIDER_virtual/libgl = ""
PREFERRED_PROVIDER_egl = "mali-user-module"
PREFERRED_PROVIDER_libgles2 = "mali-user-module"

# We must disable ptest when can not use GPLv3 License,
# ptest require many package, which have GPLv3 License,
DISTRO_FEATURES_remove += "${@bb.utils.contains("INCOMPATIBLE_LICENSE", "GPLv3", "ptest", "",d)}"

# Match version between native and target sysroot in meta-gplv2 when not using GPLv3.
PREFERRED_VERSION_gdbm-native ?= "${@bb.utils.contains("INCOMPATIBLE_LICENSE", "GPLv3", "1.8.3", "",d)}"
