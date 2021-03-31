require include/core-image-renesas-base.inc

IMAGE_INSTALL_append = " util-linux glib-2.0"

# Environment setup, support building kernel modules with kernel src in SDK
export KERNELSRC="$SDKTARGETSYSROOT/usr/src/kernel"
export KERNELDIR="$SDKTARGETSYSROOT/usr/src/kernel"
export HOST_EXTRACFLAGS="-I${OECORE_NATIVE_SYSROOT}/usr/include/ -L${OECORE_NATIVE_SYSROOT}/usr/lib"

TOOLCHAIN_TARGET_TASK += " libusb1-dev alsa-dev"

