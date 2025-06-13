require conf/machine/include/soc-family.inc
SOC_FAMILY = "rzg3e-family:mali-family"

MACHINE_FEATURES = "opengles opencl mali-g52"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-renesas"
PREFERRED_VERSION_linux-renesas ?= "6.1%"
KERNEL_IMAGETYPE ?= "Image"

# Supported devicetree
KERNEL_DEVICETREE ?= " \
	renesas/r9a09g047e57-smarc.dtb \
	renesas/r9a09g047e57-dev.dtb \
"

# flash writer
EXTRA_IMAGEDEPENDS += " flash-writer"
