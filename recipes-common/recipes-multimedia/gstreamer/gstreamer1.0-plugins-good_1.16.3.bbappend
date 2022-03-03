FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_remove = "https://gstreamer.freedesktop.org/src/gst-plugins-good/gst-plugins-good-${PV}.tar.xz"
SRC_URI_append = " \
    gitsm://github.com/renesas-rcar/gst-plugins-good.git;branch=RCAR-GEN3e/1.16.3;name=base \
"

SRCREV_base = "34a8bf145506eca37291c8e72ab09fa0b5eb6149"

DEPENDS += "mmngrbuf-user-module"

S = "${WORKDIR}/git"

EXTRA_OEMESON_append = " \
    -Dignore-fps-of-video-standard=true \
"

EXTRA_OEMESON_append_rzg2h = " \
     -Dcont-frame-capture=true \
"
