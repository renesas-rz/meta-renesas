# Install packages
IMAGE_INSTALL_append = " \
    gstreamer1.0-meta-base \
    gstreamer1.0-meta-audio \
    gstreamer1.0-meta-video \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wayland', \
        'gstreamer1.0-plugins-bad-waylandsink', '', d)} \
    gstreamer1.0-plugins-ugly-asf \
    gstreamer1.0-libav \
    gstreamer1.0-rtsp-server \
    gstreamer1.0-meta-debug \
    gstreamer1.0-plugins-bad-faac \
    gstreamer1.0-plugins-bad-faad \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugin-vspmfilter \
    kernel-module-mmngr \
    kernel-module-mmngrbuf \
    kernel-module-vspm \
    kernel-module-vspmif \
    vspmif-user-module \
    mmngr-user-module \
    mmngrbuf-user-module \
    alsa-utils \
"
