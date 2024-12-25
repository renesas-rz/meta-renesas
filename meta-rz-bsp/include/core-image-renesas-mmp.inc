IMAGE_INSTALL:append = " \
		packagegroup-multimedia-libs \
		packagegroup-multimedia-kernel-modules \
"

TOOLCHAIN_TARGET_TASK:append = " packagegroup-multimedia-kernel-modules-dev"
