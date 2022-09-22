require rzg2-common.inc
require include/ecc-control.inc

# Configuration for ARM Trusted Firmware
#EXTRA_IMAGEDEPENDS += " optee-os"

MACHINEOVERRIDES =. "rzv2ma:"

BBMASK_append = " recipes-rzv2l"
BBMASK_append += "/meta-renesas/recipes-rzv2m/"
