require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzg3e-family:mali-family"

MACHINE_FEATURES = "opengles opencl mali-g52"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
KERNEL_IMAGETYPE ?= "Image"

# flash writer
EXTRA_IMAGEDEPENDS += " flash-writer"

# Wic image offset
FIP_WIC_OFFSET = "--offset 768s"

# Update default TUNE_FEATURES support for this SoCs
TUNE_FEATURES = "aarch64 cortexa55"
