
require conf/machine/include/${SOC_FAMILY}.inc
# Configuration for kernel
PREFERRED_PROVIDER_virtual/kernel = "linux-renesas"

MACHINE_FEATURES = ""

KERNEL_IMAGETYPE = "uImage"
KERNEL_EXTRA_ARGS += "LOADADDR=0x40008000"

IMAGE_FSTYPES_append = " tar.bz2 ext4"

# libdrm
PREFERRED_VERSION_libdrm = "2.4.83"

# Add variable to Build Configuration in build log
BUILDCFG_VARS_append = " SOC_FAMILY"

#add u-boot
PREFERRED_VERSION_u-boot = "v2013.01%"
