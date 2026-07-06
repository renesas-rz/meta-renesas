FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:remove = "https://gstreamer.freedesktop.org/src/gst-plugins-bad/gst-plugins-bad-${PV}.tar.xz"

SRC_URI:append = " \
    git://github.com/renesas-rz/gst-plugins-bad.git;branch=RZ/1.22.12;protocol=https \
    file://0001-New-libbayersink-Bayer-to-RAW-converter-and-display-.patch \
    file://0002-ext-bayerconvert-add-bayerconvert-plugin.patch \
"

SRC_URI:append:mali-family = " \
    ${@bb.utils.contains('BBFILE_COLLECTIONS', 'meta-rz-graphics', 'file://0003-ext-bayersink-Remove-EGL_PIXMAP_BIT-while-using-mali.patch', '', d)} \
    ${@bb.utils.contains('BBFILE_COLLECTIONS', 'meta-rz-graphics', 'file://0004-ext-bayerconvert-Add-support-for-DMA-BUF-input-buffe.patch', '', d)} \
    ${@bb.utils.contains('BBFILE_COLLECTIONS', 'meta-rz-graphics', 'file://0005-ext-bayersink-Add-support-for-DMA-BUF-input-buffer.patch', '', d)} \
    ${@bb.utils.contains('BBFILE_COLLECTIONS', 'meta-rz-graphics', 'file://0006-ext-bayerconvert-Add-GBM-fallback-when-Wayland-Westo.patch', '', d)} \
"

SRCREV = "ceac55ae56085391caa2b8f460757ddd9b9233ed"

S  = "${WORKDIR}/git"

DEPENDS += "bayer2raw virtual/libgles2 mmngr-user-module mmngrbuf-user-module"

RDEPENDS:gstreamer1.0-plugins-bad-bayersink += "bayer2raw"
RDEPENDS:gstreamer1.0-plugins-bad-bayerconvert += "bayer2raw"

PACKAGECONFIG:append = "faac faad"
