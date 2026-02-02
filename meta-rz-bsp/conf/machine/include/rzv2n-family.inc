require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzv2n-family:mali-family"

MACHINE_FEATURES = "opengles opencl mali-g31"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
PREFERRED_VERSION_linux-renesas ?= "6.1%"
PREFERRED_VERSION_linux-renesas-rt ?= "6.1%"
KERNEL_IMAGETYPE ?= "Image"

# Wic image offset
FIP_WIC_OFFSET = "--offset 768s"
