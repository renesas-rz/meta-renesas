#Revision to update qt5.6.3
require qt5.6.3_git.inc
SRCREV = "4dd780a81e886a8a5eb86d1a045716ac4194eba1"

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv21;md5=4bfd28363f541b10d9f024181b8df516 \
    file://LICENSE.LGPLv3;md5=e0459b45c5c4840b353141a8bbed91f0 \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
    file://LGPL_EXCEPTION.txt;md5=9625233da42f9e0ce9d63651a9d97654 \
    file://LICENSE.FDL;md5=6d9f2a9af4c8b8c3c769f6cc1b6aaf7e \
"

SRC_URI_append = " \
	file://0001-Fix-binding-loop-for-declarative-camera.patch \
	file://0003-qtmultimedia-replace-playbin-by-playbin3-to-play-vid.patch \
	file://0004-qtmultimedia-qmlvideo-add-fullscreen-display-support.patch \
	file://0005-qtmultimedia-qmlvideofx-update-GUI-compatible-RZ-G-p.patch \
	file://0006-GStreamer-fix-video-output-stopping-when-the-main-th.patch \
	file://0007-qtmultimedia-Add-function-to-store-get-array-of-fd.patch \
	file://0008-qtmultimedia-Add-render-by-EGLImage-for-video-playba.patch \
	file://0009-qsgvideonode-fix-issue-double-free-in-race-condition.patch \
	file://0010-add_QtGstLaunch_service.patch \
	file://0011-qgstlaunch-Add-returned-value-for-callback-function-.patch \
"

PACKAGECONFIG_append = " gstreamer alsa"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

RDEPENDS_${PN}-plugins += " \
	gstreamer1.0 \
	gstreamer1.0-libav \
	gstreamer1.0-plugins-base \
	gstreamer1.0-plugins-base-app \
	gstreamer1.0-plugins-good \
	gstreamer1.0-plugins-good-video4linux2 \
	gstreamer1.0-plugins-bad \
	libgstbasecamerabinsrc-1.0 \
"
