#Revision to update qt5.6.2
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
require qt5.6.2_git.inc
SRCREV = "20686cb51fb2dfa5973d636875e9fc20c2bde4f5"

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv21;md5=4bfd28363f541b10d9f024181b8df516 \
    file://LICENSE.LGPLv3;md5=e0459b45c5c4840b353141a8bbed91f0 \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
"
