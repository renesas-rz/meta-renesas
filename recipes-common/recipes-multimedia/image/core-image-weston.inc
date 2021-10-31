# Gstreamer Packages
GSTREAMER_PKGS = "packagegroup-gstreamer1.0-plugins"
MMPLIB_PKGS = "packagegroup-multimedia-libs"
MMPKERNEL_PKGS = "packagegroup-multimedia-kernel-modules"

# Install packages for Wayland Env
# default: Basic packages, Gstreamer packages
IMAGE_INSTALL_append = " \
    ${GSTREAMER_PKGS} \
    ${MMPLIB_PKGS} \
    ${MMPKERNEL_PKGS} \
"

