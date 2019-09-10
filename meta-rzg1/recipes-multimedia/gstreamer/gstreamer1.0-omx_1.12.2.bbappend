FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI_remove = "http://gstreamer.freedesktop.org/src/gst-omx/gst-omx-${PV}.tar.xz"
SRC_URI_append = " \
    git://github.com/renesas-rcar/gst-omx.git;branch=RCAR-GEN3/1.12.2;name=base \
    git://anongit.freedesktop.org/gstreamer/common;destsuffix=git/common;name=common \
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
    file://0023-omxvideoenc-Handle-for-valid-output-frames-only.patch \
    file://0024-omxvideoenc-Set-default-value-for-Control-rate-in-se.patch \
    file://0025-omxvideoenc-Support-hack-renesas-encmc-stride-align.patch \
    file://0026-omxvideoenc-Support-scan-type-option.patch \
    file://0027-omxh264enc-Support-use-incaps-header-option.patch \
    file://0028-omxvideoenc-Support-no-copy-option-for-video-encoder.patch \
    file://0029-omxbufferpool-Add-handling-of-sharing-memory-buffer-.patch \
    file://0030-omxvideoenc-edit-nStride-value.patch \
    file://0035-build-include-OMX_IndexExt-and-OMX_ComponentExt-if-p.patch  \
    file://0036-gst145-omxh264enc-Support-periodicty_idr-and-interva.patch \
    file://0037-omxh264enc-Add-timestamp-information-for-buffer-cont.patch \
    file://0038-bufferpool-Fix-mistake-in-memory-size.patch \
    file://0039-omxvideodec-Support-dynamic-change-in-src-pad.patch \
    file://0040-omxvideodec-don-t-drop-frame-if-it-contains-header-d.patch \
    file://0041-omxvideoenc-Correct-handling-for-alignment-au.patch \
    file://0042-omxvideoenc-add-nPFrames-for-AVCINTRAPERIOD-c.patch \
"

DEPENDS += "omx-user-module mmngrbuf-user-module"

SRCREV_base = "d00664578bbef19091cfcaebc2caef17e30221af"
SRCREV_common = "48a5d85ebf4a0bad1c997c83100f710fe2154fbf"
SRCREV_FORMAT = "base"

LIC_FILES_CHKSUM = "file://COPYING;md5=4fbd65380cdd255951079008b364516c \
    file://omx/gstomx.h;beginline=1;endline=22;md5=e2c6664eda77dc22095adbed9cb6c6e4 \
"
    
S = "${WORKDIR}/git"

GSTREAMER_1_0_OMX_TARGET = "rcar"
GSTREAMER_1_0_OMX_CORE_NAME = "/usr/local/lib/libomxr_core.so"
EXTRA_OECONF_append = " --enable-experimental"

do_configure_prepend() {
    cd ${S}
    install -m 0644 ${WORKDIR}/gstomx.conf ${S}/config/rcar/
    ./autogen.sh --noconfigure
    cd ${B}
}

RDEPENDS_${PN} = "libwayland-egl"
