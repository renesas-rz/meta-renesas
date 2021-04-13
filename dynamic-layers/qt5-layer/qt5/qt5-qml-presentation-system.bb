SUMMARY = "Qt5 qml presentation system"
DESCRIPTION = "Quick tour of Qt 5.0, primarily focusing on its graphical capabilities."
HOMEPAGE = "https://code.qt.io/cgit/qt-labs/"
LICENSE = "LGPLv2.1"

# This package actually has no License file. Below is dummy info to build
LIC_FILES_CHKSUM = "file://presentation.pro;md5=fcb836475bffdd2776009a329c13b560"

DEPENDS = "qtdeclarative"
#RDEPENDS_${PN}-dev = ""

SRCREV = "860804a58bf47eaecdcc1acf81620bb998bf8cbf"
SRC_URI = "git://code.qt.io/qt-labs/qml-presentation-system.git"

S = "${WORKDIR}/git"

do_install() {
     install -d ${D}${libdir}/qt5/qml/Qt/labs/presentation
     install -m 644 ${S}/src/* ${D}${libdir}/qt5/qml/Qt/labs/presentation/
}

#FILES_${PN}-dbg += "${datadir}/${P}/.debug"
FILES_${PN} += "${datadir} \
	        ${libdir}/*"
