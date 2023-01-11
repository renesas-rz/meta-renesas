#Revision for qt5.6.3
# Note that this package is not officially released with Qt 5.6
# This revision is just a buildable version with Qt 5.6.3

PV = "git${SRCPV}"
SRCREV = "95a78c9f04d9a3f954477855f84180ced556a480"

PACKAGECONFIG = "gstreamer qtmultimedia qtsensors qtwebchannel"

DEPENDS += " gperf-native bison-native python3-native"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "\
    file://0001-QtWebKit-doesn-t-build-with-ICU-59.patch \
    file://0002-Fix-build-with-icu-6x.-or-newer.patch \
"
PROVIDES = " qtwebkit-qmlplugins"
