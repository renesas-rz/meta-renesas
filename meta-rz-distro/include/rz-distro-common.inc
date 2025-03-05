export BUILDDIR = "${STAGING_INCDIR}/.."
export INCSHARED = "${STAGING_INCDIR}"
export LIBSHARED = "${STAGING_LIBDIR}"
export LDFLAGS = ""
export CP = "cp"

IMAGE_INSTALL:append = " \
		packagegroup-multimedia-libs \
		packagegroup-gstreamer1.0-plugins \
"

# RZ common path
RENESAS_DATADIR ?= "/usr/local"

