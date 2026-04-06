require conf/machine/include/soc-family.inc
require conf/machine/include/ecc-control.inc

SOC_FAMILY = "rzg2h-family"

# Machine configuration
MACHINE_FEATURES = "opengles opencl usb3"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
PREFERRED_VERSION_linux-renesas ?= "6.12%"
KERNEL_IMAGETYPE ?= "Image"

# U-boot configuration
EXTRA_IMAGEDEPENDS += " u-boot"

# Configuration for ARM Trusted Firmware
EXTRA_IMAGEDEPENDS += " trusted-firmware-a"

# flash writer
EXTRA_IMAGEDEPENDS += " flash-writer"
