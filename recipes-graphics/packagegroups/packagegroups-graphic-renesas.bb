SUMMARY = "Renesas package group for Weston"
LICENSE = "CLOSED & MIT"

inherit packagegroup

PACKAGES = " \
    packagegroup-wayland-community \
    packagegroup-graphics-renesas-proprietary \
"

RDEPENDS_packagegroup-wayland-community = " \
    wayland \
    weston \
    weston-examples \
    alsa-utils \
    alsa-tools \
    libdrm-tests \
    libdrm-kms \
"

RDEPENDS_packagegroup-graphics-renesas-proprietary = " \
    kernel-module-mali mali-user-module \
"

DEPENDS_packagegroup-graphics-renesas-wayland = "libegl"
