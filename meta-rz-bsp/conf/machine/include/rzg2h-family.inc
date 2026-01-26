require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzg2h-family"

# Machine configuration
MACHINE_FEATURES = "opengles opencl"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
PREFERRED_VERSION_linux-renesas ?= "6.12%"
KERNEL_IMAGETYPE ?= "Image"
