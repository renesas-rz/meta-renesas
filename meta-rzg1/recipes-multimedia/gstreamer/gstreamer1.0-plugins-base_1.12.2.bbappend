require ../../include/multimedia-control.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

DEPENDS += " kernel-module-mmngr mmngr-user-module kernel-module-mmngrbuf mmngrbuf-user-module vspm-user-module kernel-module-vspm"

SRC_URI_append += " ${@bb.utils.contains("USE_MULTIMEDIA", "1", " \
    file://0001-gst-plugins-base-vspmfilter-Add-new-plugin-support-DMAbuf.patch \
    file://0002-gst-plugins-base-vspmfilter-add-outbuf-alloc-mode.patch \
    file://0003-gst-plugins-base-videoencoder-fix-error-w-I420-format.patch \
    file://0004-vspmfilter-Align-the-start-address-of-the-CbCr-ingre.patch \
    file://0006-vspmfilter-add-RGB-and-RGBx-output.patch \
    file://0007-vspmfilter-fix-memory-leak.patch \
    file://0008-vspmfilter-Rewrite-implement-for-swap.patch \
    file://0009-vspmfilter-Add-all-possible-format-that-vspm-can-han.patch \
    file://0010-vspmfilter-Rewrite-caps-with-available-format-only.patch \
    file://0011-vspmfilter-Update-setting-in-out-params.patch \
    file://0012-gstvspmfilter-add-bufferpool.patch \
    file://0014-gstvspmfilter-change-to-output-alloc-as-default.patch \
    file://0015-gstplaybin-change-vspmfilter-as-default-converter.patch \
    file://0017-vspmfilter-Fix-mistake-in-storing-dmabuf_pid.patch \
    file://0018-vspmfilter-Fix-crash-issue-in-dmabuf-use-mode-with-s.patch \
    file://0019-Add-vspmfilter-replace-videoconvert.patch \
    file://0020-vspmfilter-Fix-wrong-stride-numbers.patch \
    file://0021-vspmfilter-replace-old-dmabuf-query-method.patch \
    file://0022-vspmfilter-prevent-issue-lack-of-property-dmabuf-use.patch \
    file://0023-vspmfilter-Fix-wrong-color-due-to-wrong-physical-add.patch \
    file://0024-vspmfilter-only-add-dmabuf-when-user-enable-it.patch \
    file://0025-vspmfilter-disable-outbuf-alloc-mode-in-default-sett.patch \
    file://0026-playback-set-TRUE-value-for-outbuf-alloc-property-on.patch \
    file://0027-encoding-add-vspmfilter-and-omxh264enc-caps-in-encod.patch \
    file://0028-vspmfilter-enable-passthrough.patch \
    file://0029-vspmfilter-prevent-outbuf-alloc-set-to-false-when-us.patch \
    ", "", d)}"
