LICENSE = "GPL-2.0-only & MIT"
LIC_FILES_CHKSUM = " \
    file://GPL-COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://MIT-COPYING;md5=192063521ce782a445a3c9f99a8ad560 \
"
inherit module
require include/rz-modules-common.inc

MMNGR_DRV_URI = "git://github.com/renesas-rz/mmngr_drv"

SRC_URI = "${MMNGR_DRV_URI};branch=main;protocol=https"
SRCREV = "0b52d57b16edb147618704d4d9d32ae4e957c133"
