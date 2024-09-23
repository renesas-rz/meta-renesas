require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzg2l-family"

# Machine configuration
MACHINE_FEATURES = "opengles opencl"

IMAGE_FSTYPES:append = " tar.bz2 ext4"

# Configuration for ARM Trusted Firmware
EXTRA_IMAGEDEPENDS += " trusted-firmware-a"

# flash writer
EXTRA_IMAGEDEPENDS += " flash-writer"

# Firmware-pack
EXTRA_IMAGEDEPENDS += " firmware-pack"

