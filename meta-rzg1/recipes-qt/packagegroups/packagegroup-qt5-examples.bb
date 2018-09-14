# TODO add license
DESCRIPTION = "All Demos Packages for Qt5"

LICENSE = "MIT"

inherit packagegroup

PACKAGES = "\
    packagegroup-qt5-examples \
    "

ALLOW_EMPTY_${PN} = "1"


# Requires Wayland to work
QT5_WAYLAND_PACKAGES = " \
    qtwayland \
    qtwayland-plugins \
    qtwayland-tools \
"

QT5_EXAMPLES = " \
	qtbase-examples \
	qtdeclarative-examples \
	qtmultimedia-examples \	
"

RDEPENDS_${PN} += " \
	qtbase \
	qtbase-plugins \
	qtbase-tools \
	qtbase-fonts \
	${@base_contains('DISTRO_FEATURES', 'wayland', '${QT5_WAYLAND_PACKAGES}', '', d)} \
	qtdeclarative \
	qtdeclarative-plugins \
	qtdeclarative-tools \
	qtdeclarative-qmlplugins \
	qtimageformats-plugins \
	qtgraphicaleffects-qmlplugins \
	qtconnectivity \
	qtconnectivity-qmlplugins \
	qtlocation-plugins \
	qtlocation-qmlplugins \
	qtmultimedia \
	qtmultimedia-plugins \
	qtmultimedia-qmlplugins \
	qtsvg \
	qtsvg-plugins \
	qtsensors \
	qtsensors-plugins \
	qtsensors-qmlplugins \
	qtscript \
	qtserialport \
	qtwebchannel \
	qtwebchannel-qmlplugins \
	qtwebsockets \
	qtwebsockets-qmlplugins \
	qt5-qml-presentation-system \
	${QT5_EXAMPLES} \
"

