require ../../include/multimedia-control.inc
require ../../include/gles-control.inc

# common
IMAGE_INSTALL_append_rzg1 = " \
    alsa-utils alsa-tools \
    libdrm-tests \
    libdrm-kms \
    bash \
"

IMAGE_INSTALL_append_rzg1 = " \
    gstreamer1.0-plugins-base-videorate \
    gstreamer1.0-plugins-base-videotestsrc \
    gstreamer1.0-plugins-base-audiotestsrc \
    gstreamer1.0-plugins-base-alsa \
    gstreamer1.0-plugins-good-autodetect \
    gstreamer1.0-plugins-good-video4linux2 \
    gstreamer1.0-plugins-good-videocrop \
    gstreamer1.0-plugins-bad-fbdevsink \
    gstreamer1.0-plugins-bad-videoparsersbad \
    gstreamer1.0-plugins-good-isomp4 \
"

IMAGE_INSTALL_append_rzg1 = " \
    bluetooth-firmware \
    kernel-module-8723bu \
    rtl-modules-init \
"

IMAGE_INSTALL_append_iwg20m = " \
    dosfstools \
    evtest \
    e2fsprogs-mke2fs \
    i2c-tools \
    iproute2 \
    memtester \
    python-subprocess \
    python-datetime \
    python-json \
    ethtool \
    mtd-utils \
    mtd-utils-ubifs \
    iperf \
    can-utils \
    pciutils \
    libsocketcan \
    minicom \
    lttng-tools \
    lttng-modules \
    lttng-ust \
"
IMAGE_INSTALL_append_iwg21m = " \
    libdrm-tests \
    libdrm-kms \
    bash \
    dosfstools \
    evtest \
    e2fsprogs-mke2fs \
    i2c-tools \
    iproute2 \
    memtester \
    python-subprocess \
    python-datetime \
    python-json \
    ethtool \
    mtd-utils \
    mtd-utils-ubifs \
    iperf \
    can-utils \
    pciutils \
    libsocketcan \
    minicom \
    lttng-tools \
    lttng-modules \
    lttng-ust \
"
IMAGE_INSTALL_append_rzg1 = '${@base_conditional("USE_GLES", "1", \
    "gles-kernel-module gles-user-module", "", d)}'

# pkg groups for multimedia
IMAGE_INSTALL_append_rzg1 = ' ${@base_contains("USE_MULTIMEDIA", "1", " \
    packagegroup-rzg-multimedia \
    ", "", d)}'
# pkg groups for multimedia test program
IMAGE_INSTALL_append_rzg1 = ' ${@base_contains("USE_MULTIMEDIA_TEST", "1", " \
    packagegroup-rzg-multimedia-tp \
    ", "", d)}'
# pkg groups for dtv
IMAGE_INSTALL_append_rzg1 = ' ${@base_contains("USE_DTV", "1", " \
    packagegroup-rzg-dtv \
    ", "", d)}'
# pkg groups for graphic test program
IMAGE_INSTALL_append_rzg1 = ' ${@base_contains("USE_GLES_TEST", "1", " \
    gles-test-module \
    ", "", d)}'
