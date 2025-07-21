require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzg3l-family:mali-family"

MACHINE_FEATURES = "opengles opencl mali-g31 hwh264dec hwh264enc"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
PREFERRED_VERSION_linux-renesas ?= "6.12%"
KERNEL_IMAGETYPE ?= "Image"

# Wic image offset
FIP_WIC_OFFSET = "--offset 768s"
