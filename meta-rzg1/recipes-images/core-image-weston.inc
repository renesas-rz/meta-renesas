include core-image-renesas-base.inc
require ../include/rzg-modules-common.inc

IMAGE_INSTALL_append_rzg1 = '${@base_conditional("USE_GLES", "1", \
    " libegl libegl-dev libgbm-dev", "", d)} \
'
IMAGE_INSTALL_append_rzg1 = '${@base_conditional("ENABLE_QT_FRAMEWORK", "1", \
    " packagegroup-qt5-examples", "", d)} \
'

IMAGE_INSTALL_append_lcb = " \
    can-utils \
    libsocketcan \
"

# GStreamer Packages
GST_PACKAGEGROUP = "packagegroup-gstreamer1.0-plugins"

IMAGE_INSTALL_append = " \
  ${GST_PACKAGEGROUP} \
  iproute2 \
  obexftp \
  bluez5 \
  configuration \
  usbutils \
  util-linux \
  usb-otg-init \
  usb-init-wl \
  linux-firmware \
  wpa-supplicant \
  init-ifupdown \
  kernel-module-configfs \
  kernel-module-libcomposite \
  kernel-module-usb-f-mass-storage \
  kernel-module-g-mass-storage \
  kernel-module-rtl-usb \
  kernel-module-rtl8192cu \
  dosfstools \
  evtest \
  e2fsprogs \
  i2c-tools \
  memtester \
  python-subprocess \
  python-datetime \
  python-json \
  ethtool \
  mtd-utils \
  mtd-utils-ubifs \
  pciutils \
  libsocketcan \
  minicom \
  lttng-tools \
  lttng-modules \
  lttng-ust \
  util-linux-losetup \
  util-linux-umount \
  util-linux-swaponoff \
  util-linux-libsmartcols \
  can-utils \
  audio-init \
  pulseaudio-init \
  kernel-module-ohci-hcd \
  kernel-module-ohci-pci \
  ohci-init \
  rt-tests \
  ltp \
"

IMAGE_INSTALL_append_iwg21m = " \
  kernel-module-sh-eth \
"

IMAGE_INSTALL_append_iwg23s = " \
  kernel-module-ohci-platform \
"
