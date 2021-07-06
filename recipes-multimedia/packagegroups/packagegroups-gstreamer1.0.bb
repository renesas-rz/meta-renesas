SUMMARY = "GStreamer 1.0 package groups"
LICENSE = "MIT"

inherit packagegroup

PACKAGES = " \
    packagegroup-gstreamer1.0-plugins \
    packagegroup-gstreamer1.0-plugins-base \
    packagegroup-gstreamer1.0-plugins-audio \
    packagegroup-gstreamer1.0-plugins-video \
    packagegroup-gstreamer1.0-plugins-debug \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins = " \
    packagegroup-gstreamer1.0-plugins-base \
    packagegroup-gstreamer1.0-plugins-audio \
    packagegroup-gstreamer1.0-plugins-video \
    packagegroup-gstreamer1.0-plugins-debug \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins-base = " \
    gstreamer1.0-meta-base \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins-audio = " \
    gstreamer1.0-meta-audio \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins-video = " \
    gstreamer1.0-meta-video \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wayland', \
        'gstreamer1.0-plugins-bad-waylandsink', '', d)} \
    gstreamer1.0-plugins-ugly-asf \
    gstreamer1.0-libav \
    gstreamer1.0-rtsp-server \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins-debug = " \
    gstreamer1.0-meta-debug \
"
