IMAGE_INSTALL:append = " \
		packagegroup-multimedia-libs \
		packagegroup-multimedia-kernel-modules \
                packagegroup-gstreamer1.0-plugins \
"

TOOLCHAIN_TARGET_TASK:append = " packagegroup-multimedia-kernel-modules-dev"
