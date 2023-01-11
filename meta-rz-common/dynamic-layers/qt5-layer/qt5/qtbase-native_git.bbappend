#Revision for qt5.6.3
require qt5.6.3_git.inc
SRCREV = "e6f8b072d2bf15f8b82bede48ff29ce8ac8dbd9a"

FILESEXTRAPATHS_append := "${THISDIR}/qtbase:"

# Replace patch to work with Qt5.6.3, old patch only work with Qt.5.6.2
SRC_URI_remove = "file://0010-Add-external-hostbindir-option-for-native-sdk.patch"
SRC_URI += " file://0011-Add-external-hostbindir-option-for-native-sdk.patch"

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv21;md5=fb91571854638f10b2e5f36562661a5a \
    file://LICENSE.LGPLv3;md5=a909b94c1c9674b2aa15ff03a86f518a \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
    file://LICENSE.FDL;md5=6d9f2a9af4c8b8c3c769f6cc1b6aaf7e \
"

# Solve issue build qtbase-native due to no exist "-no-nis" and "-no-gui" setting anymore.
PACKAGECONFIG_CONFARGS_remove = "-no-nis -no-gui"

#Skip QA for patch-fuzz here because main layer meta-qt5 has patch that is not matched with source, also their source too.
WARN_QA_remove = "patch-fuzz"
