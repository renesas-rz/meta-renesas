require u-boot-renesas.inc

COMPATIBLE_MACHINE = "(rzg3e-family)"

UBOOT_URI = "git://github.com/renesas-rz/renesas-u-boot-cip.git;protocol=https;nobranch=1"
UBOOT_REV ?= "deef73d62a080ba09180fefe3c8b8d08b050c076"

PV="2024.07+git${SRCPV}"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=2ca5f2c35c8cc335f0a19756634782f1"
