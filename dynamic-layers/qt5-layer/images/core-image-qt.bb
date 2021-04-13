require recipes-graphics/images/core-image-weston.bb
require include/core-image-renesas-base.inc

SUMMARY = "Renesas core image with Qt5 platform support base on core-image-weston"

IMAGE_INSTALL_append = " packagegroup-qt5 packagegroup-qt5-examples "
