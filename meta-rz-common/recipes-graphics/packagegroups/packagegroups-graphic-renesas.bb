SUMMARY = "Renesas package group for Weston"
LICENSE = "CLOSED & MIT"

inherit packagegroup

PACKAGES = " \
    packagegroup-wayland-community \
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
