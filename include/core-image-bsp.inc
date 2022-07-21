# Basic packages
IMAGE_INSTALL_append = " \
    bonnie++ \
    util-linux \
    busybox \
    libusb1 \
    pciutils \
    iproute2 \
    i2c-tools \
    can-utils \
    ethtool \
    iperf3 \
    usbutils \
    mtd-utils \
    dosfstools \
    e2fsprogs-badblocks \
    e2fsprogs-dumpe2fs \
    e2fsprogs-e2fsck \
    e2fsprogs-e2scrub \
    e2fsprogs-mke2fs \
    e2fsprogs-resize2fs \
    e2fsprogs-tune2fs \
    minicom \
    memtester \
    alsa-utils \
    libdrm \
    libdrm-tests \
    yavta \
    kernel-module-uvcvideo \
"

# Installation for Wifi/Bluetooth packages
IMAGE_INSTALL_append_rzg2h = " \
    watchdog \
    linux-firmware-ti-connectivity-license \
    linux-firmware-wl18xx \
    init-ifupdown \
    wlconf \
    init-wl18xx \
    iw \
    wpa-supplicant \
    kernel-module-wlcore-sdio \
    bt-fw \
    obexftp \
    bluez-alsa \
    audio-init \
"

# Additional tools for support Tool develop
IMAGE_INSTALL_append = " \
    ckermit \
    connman \
    connman-client \
    connman-tools \
    connman-tests \
    connman-wait-online \
    lttng-modules \
    lttng-tools \
    lttng-ust \
    tcf-agent \
"

# Additional tools for support testing Realtime characteristic in system
IMAGE_INSTALL_append = " \
	${@oe.utils.conditional("IS_RT_BSP", "1", " rt-tests ", " ",d)} \
"

require docker-control.inc
# Additional tools for supporting Docker
DOCKER_PKGS = " docker ca-certificates ntpdate kernel-module-nf-conntrack-netlink "
IMAGE_INSTALL_append = "\
    ${@oe.utils.conditional("USE_DOCKER", "1", " ${DOCKER_PKGS} ", "", d)} \
"
