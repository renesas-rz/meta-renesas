#Revision to update qt5.6.3
require qt5.6.3_git.inc
SRCREV = "50582280b10fb1962b3bdfdd06a72ae1e0325049"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
    file://0001-XSLTTokenizer-queueSorting-remove-redundant.patch \
"

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv21;md5=4bfd28363f541b10d9f024181b8df516 \
    file://LICENSE.LGPLv3;md5=e0459b45c5c4840b353141a8bbed91f0 \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
    file://LGPL_EXCEPTION.txt;md5=9625233da42f9e0ce9d63651a9d97654 \
    file://LICENSE.FDL;md5=6d9f2a9af4c8b8c3c769f6cc1b6aaf7e \
"
