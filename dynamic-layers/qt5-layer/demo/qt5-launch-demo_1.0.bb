SUMMARY = "Qt5 launch demo"
DESCRIPTION = "Quick tour of Qt 5.0, primarily focusing on its graphical capabilities."
HOMEPAGE = "http://code.qt.io/cgit/{non-gerrit}/qt-labs/"
LICENSE = "BSD"

# This package actually has no License file. Below is dummy info to build
LIC_FILES_CHKSUM = "file://main.qml;beginline=1;endline=39;md5=46fcfe21b4d58845077530223ab020af"

SRCREV = "c43ddf9d354761c51266ecbdc6cb90a3aac1903d"
SRC_URI = "git://code.qt.io/{non-gerrit}/qt-labs/qt5-launch-demo.git \
	http://resource.renesas.com/resource/lib/img/products/media/auto-j/microcontrollers-microprocessors/rz/rzg/qt-videos/renesas-bigideasforeveryspace.mp4;name=video \
	file://0001-VideoSlide-Change-the-video-source-and-workaround-ca.patch \
	file://0002-Update-GUI-to-compatible-with-RZ-G-platform.patch \
	file://0003-WebKit-change-address-webpage-to-offline-file.patch \
"

SRC_URI[video.md5sum] = "44748e486a971d1e039fbfc3bc15b6f1"
SRC_URI[video.sha256sum] = "148ec58a28be27700a944b66e404d38ac9d0bbb376485ce60069bdc890a0e0c6"

DEPENDS += " qtdemo-extrafiles"

S = "${WORKDIR}/git"

do_install() {
    install -d ${D}${datadir}/${PN}
    cp -a ${S}/* ${D}${datadir}/${PN}
    install -m 755 ${WORKDIR}/renesas-bigideasforeveryspace.mp4 ${D}${datadir}/${PN}

    # Change the permission to match with filesystem
    chown -R $(stat -c "%U" ${D}${datadir}/${PN}) ${D}${datadir}/${PN} 
    chgrp -R $(stat -c "%G" ${D}${datadir}/${PN}) ${D}${datadir}/${PN} 
}

FILES_${PN} += "${datadir}/${PN}"

