require conf/machine/include/${SOC_FAMILY}.inc
require rzg2-common.inc

# Firmware-pack 
EXTRA_IMAGEDEPENDS += " firmware-pack"

MACHINEOVERRIDES =. "rzg2l:"

BBMASK_append = " recipes-rzg2h"

# u-boot
PREFERRED_VERSION_u-boot = "v2020.10%"
EXTRA_IMAGEDEPENDS += " u-boot"
