#Revision for qt5.6.3
require qt5.6.3_git.inc

LIC_FILES_CHKSUM = " \
    file://src/core/browser_context_qt.cpp;md5=8b5dcd02451f832169d229afb56f27fd;beginline=1;endline=35 \
    file://src/3rdparty/chromium/LICENSE;md5=0fca02217a5d49a14dfe2d11837bb34d \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
    file://LICENSE.GPL2;md5=b234ee4d69f5fce4486a80fdaf4a4263 \
    file://LICENSE.GPL3;md5=d32239bcb673463ab874e80d47fae504 \
    file://LICENSE.LGPL3;md5=8211fde12cc8a4e2477602f5953f5b71 \
"
DEPENDS += " gperf-native "

QT_MODULE_BRANCH_CHROMIUM = "49-based"

SRCREV_qtwebengine = "fad625e0ba39e855817bbf206ab9a846d07aeeec"
SRCREV_chromium = "cb094c05c5f06489fa64412e7f5d9e194a3f9495"

