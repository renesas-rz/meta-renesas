SUMMARY = "GStreamer 1.0 package groups"
LICENSE = "MIT"

#require include/omx-control.inc

DEPENDS = "gstreamer1.0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good"
DEPENDS += "gstreamer1.0-plugins-bad"
#DEPENDS += "gstreamer1.0-plugins-ugly"
#DEPENDS += "${@base_conditional("USE_OMX_COMMON", "1", "gstreamer1.0-omx", "", d)}"

LIC_FILES_CHKSUM = " \
    file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302 \
"

PR = "r0"

inherit packagegroup

PACKAGES = " \
    packagegroup-gstreamer1.0-plugins \
    packagegroup-gstreamer1.0-plugins-base \
    packagegroup-gstreamer1.0-plugins-good \
    packagegroup-gstreamer1.0-plugins-bad \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins = " \
    packagegroup-gstreamer1.0-plugins-base \
    packagegroup-gstreamer1.0-plugins-good \
    packagegroup-gstreamer1.0-plugins-bad \
"

# temp immerse omx
RDEPENDS_packagegroup-gstreamer1.0-plugins-base = " \
    gstreamer1.0-plugins-base-videorate \
    gstreamer1.0-plugins-base-videoconvert \
    gstreamer1.0-plugins-base-videotestsrc \
    gstreamer1.0-plugins-base-audiotestsrc \
    gstreamer1.0-plugins-base-alsa \
    gstreamer1.0-plugins-base-vspmfilter \
    gstreamer1.0-plugin-vspfilter \
    gstreamer1.0-omx \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins-good = " \
    gstreamer1.0-plugins-good-autodetect \
    gstreamer1.0-plugins-good-isomp4 \
    gstreamer1.0-plugins-good-video4linux2 \
    gstreamer1.0-plugins-good-videocrop \
"

RDEPENDS_packagegroup-gstreamer1.0-plugins-bad = " \
    gstreamer1.0-plugins-bad-asfmux \
    gstreamer1.0-plugins-bad-fbdevsink \
    gstreamer1.0-plugins-bad-videoparsersbad \
    gstreamer1.0-plugins-bad-faac \
    gstreamer1.0-plugins-bad-faad \
    gstreamer1.0-plugins-bad-waylandsink \
"
