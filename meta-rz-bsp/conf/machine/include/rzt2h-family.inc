require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzt2h-family"

# Configuration for ARM Trusted Firmware

# Trusted Firmware-A configuration
EXTRA_IMAGEDEPENDS += " trusted-firmware-a"

# flash writer
EXTRA_IMAGEDEPENDS += " flash-writer"

# Firmware-pack
EXTRA_IMAGEDEPENDS += " firmware-pack"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
KERNEL_IMAGETYPE ?= "Image"

# Wic image offset
FIP_WIC_OFFSET = "--offset 768s"

# Update default TUNE_FEATURES support for this SoCs
TUNE_FEATURES = "aarch64 cortexa55"
