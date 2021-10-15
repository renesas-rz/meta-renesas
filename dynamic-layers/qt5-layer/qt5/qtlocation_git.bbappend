#Revision to update qt5.6.3
require qt5.6.3_git.inc
SRCREV = "35348e80145305778a89923d3bfe50d7baba7690"

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv21;md5=4bfd28363f541b10d9f024181b8df516 \
    file://LICENSE.LGPLv3;md5=e0459b45c5c4840b353141a8bbed91f0 \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
    file://LICENSE.GPLv2;md5=c96076271561b0e3785dad260634eaa8 \
    file://LGPL_EXCEPTION.txt;md5=9625233da42f9e0ce9d63651a9d97654 \
    file://LICENSE.FDL;md5=6d9f2a9af4c8b8c3c769f6cc1b6aaf7e \
"

PACKAGES_append = " \
	qtlocation-qmlplugins-location \
	qtlocation-qmlplugins-positioning \
	qtlocation-plugins-position \
	qtlocation-plugins-geoservices \
	qtlocation-location \
	qtlocation-positioning \
"

FILES_${PN}-qmlplugins = ""
FILES_${PN}-plugins = ""
FILES_${PN} = ""

FILES_${PN}-qmlplugins-location = " \
        ${OE_QMAKE_PATH_QML}/QtLocation/* \
"

FILES_${PN}-qmlplugins-positioning = " \
        ${OE_QMAKE_PATH_QML}/QtPositioning/* \
"

FILES_${PN}-plugins-geoservices = " \
        ${OE_QMAKE_PATH_PLUGINS}/geoservices/* \
"

FILES_${PN}-plugins-position = " \
        ${OE_QMAKE_PATH_PLUGINS}/position/* \
"

FILES_${PN}-location = " \
        ${OE_QMAKE_PATH_LIBS}/libQt5Location* \
"

FILES_${PN}-positioning = " \
        ${OE_QMAKE_PATH_LIBS}/libQt5Positioning* \
"

RDEPENDS_${PN}-qmlplugins += " qtlocation-qmlplugins-location qtlocation-qmlplugins-positioning "
RDEPENDS_${PN}-plugins += " qtlocation-plugins-position qtlocation-plugins-geoservices "
RDEPENDS_${PN} += " qtlocation-location qtlocation-positioning "
