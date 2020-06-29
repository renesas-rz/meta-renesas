#
# base recipe: meta/recipes-devtools/make/make_4.2.1
# base branch: master
# base commit: a5d1288804e517dee113cb9302149541f825d316
# 

require recipes-devtools/make/make.inc

inherit debian-package
BPN = "make-dfsg"

LICENSE = "GPLv3 & LGPLv2"
LIC_FILES_CHKSUM = " \
file://COPYING;md5=d32239bcb673463ab874e80d47fae504 \
file://tests/COPYING;md5=d32239bcb673463ab874e80d47fae504 \
file://glob/COPYING.LIB;md5=4a770b67e6be0f60da244beb2de0fce4 \
"

require make-dfsg.inc
SRC_URI += " \
           file://0001-glob-fix-error-undefined-reference-to-__alloca.patch \
           "

do_debian_verify_version[noexec] = "1"
do_debian_patch[noexec] = "1"

EXTRA_OECONF += "--without-guile"

BBCLASSEXTEND = "native nativesdk"
