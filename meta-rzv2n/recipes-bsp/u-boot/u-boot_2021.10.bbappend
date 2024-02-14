DESCRIPTION = "U-boot for the RZ/V2N based board"

UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"
BRANCH = "v2021.10/rzv2n"

SRC_URI = "${UBOOT_URL};branch=${BRANCH}"
SRCREV = "e1f6b8f5509055a5df05c2345e5f901c4bacfd5c"

PV = "v2021.10+git${SRCPV}"
