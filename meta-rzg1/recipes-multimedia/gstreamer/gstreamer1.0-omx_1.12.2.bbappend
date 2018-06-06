FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_remove = "http://gstreamer.freedesktop.org/src/gst-omx/gst-omx-${PV}.tar.xz"
SRC_URI_append = " \
    git://github.com/renesas-rcar/gst-omx.git;branch=RCAR-GEN3/1.12.2 \
    file://0001-omxvideodec-Support-videodec-for-RCarGen3.patch \
    file://0002-omxvideodec-Support-no-copy-option-for-omx-video-dec.patch \
    file://0003-omxvideodec-Add-use-dmabuf-option-for-omx-video-deco.patch \
    file://0004-omxbufferpool-Add-dmabuf-handling-for-video-decoders.patch \
    file://0005-omxvideodec-Support-no-reorder-option-for-omx-video-.patch \
    file://0005-workaroud-add-include-omx-openmax.patch \
    file://0006-omxvideodec-Support-lossy-compress-option.patch \
    file://0007-omxvideodec-Calculate-timestamp-manually-if-not-prov.patch \
    file://0008-omxvideodec-Add-hacks-to-choose-default-mode.patch \
    file://0009-omxvideodec-Support-default-pixel-aspect-ratio.patch \
    file://0010-omx-Only-handle-BufferDone-message-for-valid-buffer.patch \
    file://0001-omxvideodec-Support-copy-mode-for-omxh264dec.patch \
    file://0002-gstomx-Once-reinitialize-an-instance-and-then-retry.patch \
    file://gstomx.conf \
"

DEPENDS += "omx-user-module mmngrbuf-user-module"

#HEAD
#SRCREV = "6813dedbc9a61ea8a80e54fc373fa07d37114d4a"
SRCREV = "d00664578bbef19091cfcaebc2caef17e30221af"

LIC_FILES_CHKSUM = "file://COPYING;md5=4fbd65380cdd255951079008b364516c \
    file://omx/gstomx.h;beginline=1;endline=22;md5=e2c6664eda77dc22095adbed9cb6c6e4 \
"
    
#file://omx/gstomx.h;beginline=1;endline=22;md5=41f577b291a84518889deaaaf2bcbc95 
#file://omx/gstomx.h;beginline=1;endline=22;md5=d411057db0aa43d31f1ec9d6a980a216
#file://omx/gstomx.h;beginline=1;endline=22;md5=e2c6664eda77dc22095adbed9cb6c6e4
S = "${WORKDIR}/git"

GSTREAMER_1_0_OMX_TARGET = "rcar"
GSTREAMER_1_0_OMX_CORE_NAME = "/usr/local/lib/libomxr_core.so"
EXTRA_OECONF_append = " --enable-experimental"

do_configure_prepend() {
    export http_proxy=${http_proxy}
    export https_proxy=${https_proxy}
    export HTTP_PROXY=${HTTP_PROXY}
    export HTTPS_PROXY=${HTTPS_PROXY}
    cd ${S}
    install -m 0644 ${WORKDIR}/gstomx.conf ${S}/config/rcar/
    ./autogen.sh --noconfigure
    cd ${B}
}

RDEPENDS_${PN} = "libwayland-egl"
