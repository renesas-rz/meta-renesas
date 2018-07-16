include core-image-renesas-base.inc
require ../include/rzg-modules-common.inc

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
  kernel-module-configfs-${KERNEL_VERSION} \
  kernel-module-libcomposite-${KERNEL_VERSION} \
  kernel-module-usb-f-mass-storage-${KERNEL_VERSION} \
  kernel-module-g-mass-storage-${KERNEL_VERSION} \
  kernel-module-rtl-usb-${KERNEL_VERSION} \
  kernel-module-rtl8192cu-${KERNEL_VERSION} \
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
  ohci-init \
"
