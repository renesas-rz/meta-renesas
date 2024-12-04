DESCRIPTION = "U-boot for the RZ/V2H based board"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rzv2h"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "31d53b8f6fdc1d9055a8c226643f4ed61570e017"

PV = "v2021.10+git${SRCPV}"
