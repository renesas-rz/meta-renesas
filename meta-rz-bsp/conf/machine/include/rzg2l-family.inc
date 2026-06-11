require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzg2l-family:mali-family"

# Machine configuration
MACHINE_FEATURES = "opengles opencl"

# Configuration for ARM Trusted Firmware
EXTRA_IMAGEDEPENDS += " trusted-firmware-a"

# flash writer
EXTRA_IMAGEDEPENDS += " flash-writer"

# Firmware-pack
EXTRA_IMAGEDEPENDS += " firmware-pack"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
KERNEL_IMAGETYPE ?= "Image"

# Wic image offset
FIP_WIC_OFFSET = "--offset 256s"

# Update default TUNE_FEATURES support for this SoCs
TUNE_FEATURES = "aarch64 cortexa55"

# ECC support
ECC_FLAGS = "${@oe.utils.conditional("ECC_MODE", "ENABLE", " DDR_ECC_ENABLE=1 ", "",d)}"
ECC_FLAGS += "${@oe.utils.conditional("ECC_MODE", "ERR_DETECT", " DDR_ECC_ENABLE=1 DDR_ECC_DETECT=1 ", "",d)}"
ECC_FLAGS += "${@oe.utils.conditional("ECC_MODE", "ERR_DETECT_CORRECT", " DDR_ECC_ENABLE=1 DDR_ECC_DETECT_CORRECT=1 ", "",d)}"
