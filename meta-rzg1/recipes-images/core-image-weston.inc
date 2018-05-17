include core-image-renesas-base.inc

IMAGE_INSTALL_append_lcb = " \
    can-utils \
    libsocketcan \
    weston-bin \
"

IMAGE_INSTALL_append = " \
  iproute2 \
  obexftp \
  bluez5 \
"
