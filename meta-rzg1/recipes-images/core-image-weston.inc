include core-image-renesas-base.inc

IMAGE_INSTALL_append_rzg1 = '${@bb.utils.contains("USE_GLES", "1", \
    " libegl libegl-dev libgbm-dev", "", d)} \
'

IMAGE_INSTALL_append_lcb = " \
    can-utils \
    libsocketcan \
"
#weston-bin 

# GStreamer Packages
GST_PACKAGEGROUP = "packagegroup-gstreamer1.0-plugins"

IMAGE_INSTALL_append = " \
  ${GST_PACKAGEGROUP} \
  iproute2 \
  obexftp \
  bluez5 \
  packagegroup-qt5-examples \
  configuration \
  usbutils \
  util-linux \
  usb-otg-init \
  usb-init-wl \
  linux-firmware \
  wpa-supplicant \
  init-ifupdown \
"
