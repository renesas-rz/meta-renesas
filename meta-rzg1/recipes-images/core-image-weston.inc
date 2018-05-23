include core-image-renesas-base.inc

IMAGE_INSTALL_append_rzg1 = '${@bb.utils.contains("USE_GLES", "1", \
    " libegl libegl-dev libgbm-dev", "", d)} \
'

# pkg groups for oss codecs
IMAGE_INSTALL_append_lcb = ' ${@bb.utils.contains("USE_MULTIMEDIA", "1", " \
    packagegroup-lcb-oss-codecs \
    ", "", d)}'

IMAGE_INSTALL_append_lcb = " \
    can-utils \
    libsocketcan \
    weston-bin \
"

# GStreamer Packages
GST_PACKAGEGROUP = "packagegroup-gstreamer1.0-plugins"

IMAGE_INSTALL_append = " \
  ${GST_PACKAGEGROUP} \
  iproute2 \
  obexftp \
  bluez5 \
"
