#Revision to update qt5.6.3
require qt5.6.3_git.inc
SRCREV = "b66f6b05c5f8024ddd9f8c46f33ccb618323999e"

FILESEXTRAPATHS_prepend := "${THISDIR}/qtquickcontrols:"

# Replace patch to work with Qt5.6.2, old patch only work with Qt.5.6.1
SRC_URI_remove = "file://0001-texteditor-fix-invalid-use-of-incomplete-type-class-.patch"
SRC_URI += " file://0001-Update-texteditor-fix-invalid-use-of-incomplete-type-class-.patch "

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv3;md5=e0459b45c5c4840b353141a8bbed91f0 \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
    file://LICENSE.GPLv2;md5=c96076271561b0e3785dad260634eaa8 \
    file://LICENSE.FDL;md5=6d9f2a9af4c8b8c3c769f6cc1b6aaf7e \
"
