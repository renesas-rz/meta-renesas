FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

LIC_FILES_CHKSUM = "file://main.cpp;md5=9ee38907470e8eaf4219d06a739e6a78"
SRCREV = "35d72a2eba7456a2efc5eb8b77afbc00f69ba0ac"
DEPENDS_append += "qtmultimedia qtsvg"

RDEPENDS_${PN}_append = " qtdemo-extrafiles qtquickcontrols"

SRC_URI_append += " \
	file://0001-Run-application-fullscreen-and-add-exit-button.patch \
	file://0002-Configure-font-for-application-and-rendertype-for-to.patch \
	file://0003-Force-complete-loading-incubator-if-it-not-ready.patch \
	file://0004-Not-hide-source-of-share-effects-at-initialization.patch \
	file://0005-Add-video-and-audio-offline-for-Qteverywhere.patch \
	file://0006-Fix-missed-parameter-in-mapToItem-function-of-Calqla.patch \
	file://btn_exit.png \
	file://qt5_video_fhd30fps.png \
	file://qt5_video_hd30fps.png \
"

do_compile_prepend() {
    cp ${WORKDIR}/btn_exit.png ${WORKDIR}/git/QtDemo/qml/QtDemo/images
    cp ${WORKDIR}/qt5_video_fhd30fps.png ${WORKDIR}/git/QtDemo/qml/QtDemo/demos/video
    cp ${WORKDIR}/qt5_video_hd30fps.png ${WORKDIR}/git/QtDemo/qml/QtDemo/demos/video
}

FILES_${PN}-dbg += "home/root/.debug"
FILES_${PN} += "home/root"
