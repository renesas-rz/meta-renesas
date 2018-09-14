#Revision to update qt5.6.3
require qt5.6.3_git.inc
SRCREV = "bb01612a8809efd268903e41b9e3a17cff48f1c0"

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv21;md5=4bfd28363f541b10d9f024181b8df516 \
    file://LICENSE.LGPLv3;md5=e0459b45c5c4840b353141a8bbed91f0 \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
    file://LGPL_EXCEPTION.txt;md5=9625233da42f9e0ce9d63651a9d97654 \
    file://LICENSE.FDL;md5=6d9f2a9af4c8b8c3c769f6cc1b6aaf7e \
"
FILESEXTRAPATHS_prepend := "${THISDIR}/qtdeclarative:"
SRC_URI_append = " \
    file://0001-Build-developer-mode.patch \
    file://0001-qtdeclarative-flexible-size-for-qmlscene.patch \
"

SRC_URI_append_iwg21m = " \
    file://0001-quick-scenegraph-fix-texture-width-alignment-issue-f.patch \
"
