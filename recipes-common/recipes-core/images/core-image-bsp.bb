require recipes-core/images/core-image-minimal.bb
require include/core-image-renesas-base.inc
require include/core-image-bsp.inc

TOOLCHAIN_TARGET_TASK += " libusb1-dev alsa-dev"
