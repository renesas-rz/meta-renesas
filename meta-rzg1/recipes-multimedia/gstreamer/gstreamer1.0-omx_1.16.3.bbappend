FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_remove = "https://gstreamer.freedesktop.org/src/gst-omx/gst-omx-${PV}.tar.xz"

SRC_URI_append = " \
    git://github.com/renesas-rcar/gst-omx.git;branch=RCAR-GEN3e/1.16.3;name=base \
    git://anongit.freedesktop.org/gstreamer/common;destsuffix=git/common;name=common \
"

SRC_URI_append_rzg1 = " \
    file://gstomx-rzg1.conf \
    file://0001-omx-Fix-conflict-between-omx-user-module-and-mmngr-o.patch \
    file://0002-Fix-error-Resolution-do-not-match-in-running-case-fi.patch \
    file://0003-gst-pipeline-cannot-corectly-decode-with-vspmfilter-.patch \
"

SRCREV_base = "6db86e9434815d27de853b4c8235d098da5500a2"
SRCREV_common = "52adcdb89a9eb527df38c569539d95c1c7aeda6e"

DEPENDS += "omx-user-module  mmngrbuf-user-module"

LIC_FILES_CHKSUM = " \
    file://COPYING;md5=4fbd65380cdd255951079008b364516c \
    file://omx/gstomx.h;beginline=1;endline=22;md5=4b2e62aace379166f9181a8571a14882 \
"

S = "${WORKDIR}/git"

GSTREAMER_1_0_OMX_TARGET = "rcar"
GSTREAMER_1_0_OMX_CORE_NAME = "/usr/local/lib/libomxr_core.so"
EXTRA_OECONF_append = " --enable-experimental"

do_configure_prepend() {
    cd ${S}
    install -m 0644 ${WORKDIR}/gstomx-rzg1.conf ${S}/config/rcar/gstomx.conf
    sed -i 's,@RENESAS_DATADIR@,${RENESAS_DATADIR},g' ${S}/config/rcar/gstomx.conf
    ./autogen.sh --noconfigure
    cd ${B}
}
