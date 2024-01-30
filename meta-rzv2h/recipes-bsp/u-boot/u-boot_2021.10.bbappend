DESCRIPTION = "U-boot for the RZ/V2H based board"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rzv2h"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "8ca952fa51717293e96858ae8089886d72398d5f"

PV = "v2021.10+git${SRCPV}"
