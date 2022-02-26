require rzg2-common.inc
require include/ecc-control.inc

# Configuration for ARM Trusted Firmware
EXTRA_IMAGEDEPENDS += " optee-os"

MACHINEOVERRIDES =. "rzg2h:"

BBMASK_append = " recipes-rzg2l"

# u-boot
PREFERRED_VERSION_u-boot = "v2021.10%"
EXTRA_IMAGEDEPENDS += " u-boot"
