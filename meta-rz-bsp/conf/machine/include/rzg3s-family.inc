require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzg3s-family"

# Machine configuration
MACHINE_FEATURES = "can alsa ext2"

IMAGE_FSTYPES:append = " tar.bz2 ext4"

# Configuration for ARM Trusted Firmware
EXTRA_IMAGEDEPENDS += " trusted-firmware-a"

# flash writer
EXTRA_IMAGEDEPENDS += " flash-writer"

# Firmware-pack
EXTRA_IMAGEDEPENDS += " firmware-pack"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
PREFERRED_VERSION_linux-renesas ?= "6.1%"
KERNEL_IMAGETYPE ?= "Image"

# Wic image offset
FIP_WIC_OFFSET = "--offset 768s"
