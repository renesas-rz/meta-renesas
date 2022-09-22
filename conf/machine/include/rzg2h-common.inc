require rzg2-common.inc
require include/ecc-control.inc

# Configuration for ARM Trusted Firmware
#EXTRA_IMAGEDEPENDS += " optee-os"

MACHINEOVERRIDES =. "rzg2h:"

BBMASK_append = " recipes-rzg2l"
