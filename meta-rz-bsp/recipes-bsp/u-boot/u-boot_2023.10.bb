require u-boot-renesas.inc

COMPATIBLE_MACHINE = "(rzg3e-family)"

UBOOT_URI = "git://github.com/renesas-rz/renesas-u-boot-cip.git;protocol=https"
UBOOT_BRANCH = "v2023.10/rzg3e_init"
UBOOT_REV ?= "593d4bf3b5dd9002fe590980528304cb08fc0788"

PV="2023.10+git${SRCPV}"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=2ca5f2c35c8cc335f0a19756634782f1"
