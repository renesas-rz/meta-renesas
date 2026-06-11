require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzg3s-family"

# Configuration for ARM Trusted Firmware
EXTRA_IMAGEDEPENDS += " trusted-firmware-a"

# flash writer
EXTRA_IMAGEDEPENDS += " flash-writer"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
KERNEL_IMAGETYPE ?= "Image"

# Wic image offset
FIP_WIC_OFFSET = "--offset 768s"

# Update default TUNE_FEATURES support for this SoCs
TUNE_FEATURES = "aarch64 cortexa55"
