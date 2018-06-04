require ../../include/gles-control.inc
require ../../include/multimedia-control.inc

DESCRIPTION = "Package Group for multimedia of R-Car Gen2"
LICENSE = "CLOSED"

inherit packagegroup

PACKAGES = "\
    packagegroup-rzg-multimedia-tp \
    packagegroup-rzg-dtv \
    packagegroup-rzg-multimedia \
"

PACKAGES_append_lcb = " packagegroup-lcb-oss-codecs"

MULTIMEDIA_PACKAGES ="\
    kernel-module-mmngr mmngr-user-module \
    kernel-module-mmngrbuf mmngrbuf-user-module \
    mmngrbuf-user-module-dev \
    kernel-module-fdpm fdpm-user-module \
    kernel-module-vspm vspm-user-module \
    kernel-module-s3ctl s3ctl-user-module \
    kernel-module-uvcs-cmn omx-user-module \
    libmemcpy \
"

MULTIMEDIA_PACKAGES_append = " \
    ${@ "kernel-module-vsp2 libmediactl-v4l2" if "${USE_GLES_MULTIMEDIA}" == "1" else "" } \
"

RDEPENDS_packagegroup-rzg-multimedia = "\
    ${@ "${MULTIMEDIA_PACKAGES}" if "${USE_MULTIMEDIA}" == "1" else "" } \
    media-ctl \
"

MULTIMEDIA_TEST_PACKAGES = "\
    ${MULTIMEDIA_PACKAGES} \
    mmngr-tp-user-module \
    mmngrbuf-tp-user-module \
    fdpm-tp-user-module \
    vspm-tp-user-module \
    s3ctl-tp-user-module \
"

DTV_PACKAGES = "\
    ${MULTIMEDIA_PACKAGES} \
    scu-kernel-module ssp-kernel-module \
    dtv \
"

RDEPENDS_packagegroup-rzg-dtv = "\
    ${@ '${DTV_PACKAGES}' if '${USE_DTV}' == '1' else '' } \
"

RDEPENDS_packagegroup-rzg-multimedia = "\
    ${@ '${MULTIMEDIA_PACKAGES}' if '${USE_MULTIMEDIA}' == '1' else '' } \
"

RDEPENDS_packagegroup-lcb-oss-codecs = "\
    libvorbis \
    libogg \
"
