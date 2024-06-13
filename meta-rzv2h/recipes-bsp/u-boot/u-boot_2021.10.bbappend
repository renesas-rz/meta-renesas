DESCRIPTION = "U-boot for the RZ/V2H based board"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rzv2h"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "195f7ea10163c1c393e7bb8e8a625d0817a00319"

PV = "v2021.10+git${SRCPV}"
