require conf/machine/include/rzg2-common.inc
require include/ecc-control.inc

# Configuration for ARM Trusted Firmware
EXTRA_IMAGEDEPENDS += " optee-os"

MACHINEOVERRIDES =. "rzg2h:"
