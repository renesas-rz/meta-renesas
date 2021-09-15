SUMMARY = "GStreamer 1.0 package groups"
LICENSE = "MIT"

require include/omx-control.inc

# LICENSE_FLAGS = "license_${PN}"

DEPENDS = "gstreamer1.0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good"
DEPENDS += "gstreamer1.0-plugins-bad"
DEPENDS += "gstreamer1.0-plugins-ugly"
DEPENDS += "${@bb.utils.contains("USE_OMX_COMMON", "1", "gstreamer1.0-omx", "", d)}"

LIC_FILES_CHKSUM = " \
    file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302 \
"

PR = "r0"

inherit packagegroup

PACKAGES = " \
    packagegroup-gstreamer1.0-plugins \
    packagegroup-gstreamer1.0-plugins-base \
    packagegroup-gstreamer1.0-plugins-audio \
    packagegroup-gstreamer1.0-plugins-video \
    ${@bb.utils.contains("USE_OMX_COMMON", "1", "packagegroup-gstreamer1.0-omx", "", d)} \
    packagegroup-gstreamer1.0-plugins-debug \
    packagegroup-gstreamer1.0-plugins-bad \
    packagegroup-vspfilter-init \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins = " \
    packagegroup-gstreamer1.0-plugins-base \
    packagegroup-gstreamer1.0-plugins-bad \
    packagegroup-gstreamer1.0-plugins-audio \
    packagegroup-gstreamer1.0-plugins-video \
    ${@bb.utils.contains("USE_OMX_COMMON", "1", "packagegroup-gstreamer1.0-omx", "", d)} \
    packagegroup-gstreamer1.0-plugins-debug \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    ${@bb.utils.contains("USE_OMX_COMMON", "1", "gstreamer1.0-plugin-vspmfilter", "", d)} \
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

RDEPENDS_packagegroup-gstreamer1.0-omx = " \
    ${@bb.utils.contains("USE_OMX_COMMON", "1", "gstreamer1.0-omx", "", d)} \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins-debug = " \
    gstreamer1.0-meta-debug \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins-bad = " \
    gstreamer1.0-plugins-bad-faac \
    gstreamer1.0-plugins-bad-faad \
"
