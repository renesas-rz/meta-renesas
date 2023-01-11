#Do not use X11 if we are building for Wayland
USE_X11 = " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wayland', '${USE_WAYLAND}', 'qtx11extras-dev', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wayland', '${USE_WAYLAND}', 'qtx11extras-mkspecs', d)} \
"

RDEPENDS_${PN} += " \
    qtbase-tools \
    qtdeclarative-tools \
    qtxmlpatterns-tools \
    qtwayland-tools \
"

# meta-qt5 still use qtwebkit and qtquick1, although they are removed from Qt 5.6
# Overwrite USE_RUBY to prevent using them
USE_RUBY = " "

# Remove qtsystems since it is actually not released with Qt5.0
# # Remove qtenginio as it it not guarantee compatible with Qt5.6
# # Also do not build qt3d and qtlocation by default due to their license (not
# have LGPLv2.1)
RDEPENDS_${PN}_remove = "qtsystems-dev"
RDEPENDS_${PN}_remove = "qtsystems-mkspecs"
RDEPENDS_${PN}_remove = "qtsystems-qmlplugins"
RDEPENDS_${PN}_remove = "qtenginio-dev"
RDEPENDS_${PN}_remove = "qtenginio-mkspecs"
RDEPENDS_${PN}_remove = "qtenginio-qmlplugins"
RDEPENDS_${PN}_remove = "qt3d-dev"
RDEPENDS_${PN}_remove = "qt3d-mkspecs"
RDEPENDS_${PN}_remove = "qt3d-qmlplugins"
RDEPENDS_${PN}_remove = "qtlocation-dev"
RDEPENDS_${PN}_remove = "qtlocation-mkspecs"
RDEPENDS_${PN}_remove = "qtlocation-plugins"
RDEPENDS_${PN}_remove = "qtlocation-qmlplugins"
