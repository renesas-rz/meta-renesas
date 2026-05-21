export BUILDDIR = "${STAGING_INCDIR}/.."
export INCSHARED = "${STAGING_INCDIR}"
export LIBSHARED = "${STAGING_LIBDIR}"
export KERNELSRC = "${STAGING_KERNEL_DIR}"
export CROSS_COMPILE = "${TARGET_PREFIX}"
export KERNELDIR = "${STAGING_KERNEL_DIR}"
export LDFLAGS = ""
export CP = "cp"

RENESAS_DATADIR ?= "/usr/local"
TOOLCHAIN_TARGET_TASK:append = " packagegroup-multimedia-kernel-modules-dev"

IMAGE_INSTALL:append = " \
		packagegroup-multimedia-kernel-modules \
"

# Qos user packages only supports 64bit.
QOS_USER_PKGS = ""
QOS_USER_PKGS:aarch64 = " \
	qosif-user-module \
	qosif-tp-user-module \
"

# Installation for QoS packages
IMAGE_INSTALL:append:rzg2h-family = " \
	kernel-module-qos \
	${QOS_USER_PKGS} \
"
