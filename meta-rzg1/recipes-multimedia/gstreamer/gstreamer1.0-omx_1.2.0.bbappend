require ../../include/gles-control.inc

DEPENDS_append_rzg1 = " omx-user-module mmngrbuf-user-module"
EXTRA_OECONF_append_rzg1 = " \
    --with-omx-target=rcar --enable-experimental \
    '${@'--enable-nv12-page-alignment' if '${USE_GLES_WAYLAND}' == '1' else ''}' \
    '${@'--disable-dmabuf' if '${USE_GLES}' == '0' and '${USE_WAYLAND}' == '1' else ''}'"

# Overwrite do_install[postfuncs] += " set_omx_core_name "
# because it will force the plugin to use bellagio instead of our config
revert_omx_core_name() {
    sed -i -e "s;^core-name=.*;core-name=/usr/local/lib/libomxr_core.so;" "${D}/etc/xdg/gstomx.conf"
}
REVERT_OMX_CORE_NAME = ""
REVERT_OMX_CORE_NAME_rzg1 = "revert_omx_core_name"
do_install[postfuncs] += "${REVERT_OMX_CORE_NAME}"

FILESEXTRAPATHS_prepend_rzg1 := '${THISDIR}/${PN}:'

SRC_URI += " \
	file://0001-config-Add-config-for-RCar-Platform-support-aacdec.patch \
	file://0002-omxaudiodec-workaround-for-issue-can-not-decode-file.patch \
	file://0003-omxaacdec-Update-information-that-Renesas-MC-support.patch \
	file://0004-omxaudiodec-Fix-issue-memory-leak-of-omxaacdec-due-t.patch \
	file://0005-omxaacdec-workaround-for-calculation-wrong-number-of.patch \
	file://0006-config-Add-config-for-RCar-Platform-support-h264dec.patch \
	file://0007-gstomx-set-the-default-path-of-gstomx.conf.patch \
	file://0008-omxvideodec-Support-copy-mode-for-omxh264dec.patch \
	file://0009-omxvideodec-Support-no-copy-mode-for-omxh264dec.patch \
	file://0010-omxvideodec-Enable-using-buffer-pool.patch \
	file://0011-gstomx-Add-private-data-field-to-GstOMXBuffer-in-ord.patch \
	file://0012-omxbufferpool-avoid-the-duplicated-buffers-insertion.patch \
	file://0013-omxbufferpool-Create-multiple-GstMemory-instances-fo.patch \
	file://0014-omxvideodec-Fix-the-buffer-index-determination-to.patch \
	file://0015-omxvideodec-Support-dmabuf-mode-for-omxh264dec.patch \
	file://0016-gstomx-Set-the-used-flag-of-the-GstOMXBuffer-if-the.patch \
	file://0017-omxbufferpool-Don-t-set-the-offset-in-the-memory-whe.patch \
	file://0018-omxvideodec-Fix-not-negotiated-error-due-to.patch \
	file://0019-omxvideodec-Support-no-reorder-option.patch \
	file://0020-config.ac-Add-config-to-disable-to-export-dmabuf-fil.patch \
	file://0021-omxvideodec-Skip-the-video-decoder-negotiation-when-.patch \
	file://0022-omxvideodec-Fix-the-assertion-error-when-recieving-a.patch \
	file://0023-gstomx-Once-reinitialize-an-instance-and-then-retry.patch \
	file://0024-omxvideodec-Fix-a-memory-error-due-to-mistakenly.patch \
	file://0025-omxvideodec-Activate-the-buffer-pool-of-gst-omx-by.patch \
	file://0026-omxh264dec-Support-receiving-input-is-avc-instead-of.patch \
	file://0027-omxvideodec-Manually-calculate-timestamp-if-not-prov.patch \
	file://0028-omxbufferpool-Add-the-condition-for-returning-a-buff.patch \
	file://0029-omxh264dec-Support-receiving-byte-stream-format.patch \
	file://0030-omxvideodec-Add-hacks-to-choose-default-mode-for.patch \
	file://0031-omxvideodec-Add-hack-to-skip-querying-drain-from-dow.patch \
	file://0032-omxh264dec-Correct-size-of-buffer-when-malloc.patch \
	file://0033-gst145-omxvideoenc-Support-omxh264enc-for-RCarGen2.patch \
	file://0034-gst145-omxvideoenc-Support-NV16.patch \
	file://0035-gst145-gstomx-Workaround-a-restriction-when-nBufferS.patch \
	file://0036-gst145-omxvideodec-Fix-an-incorrect-plane-size-calcu.patch \
	file://0037-gst145-omxvideodec-Align-a-memory-size-specified-whe.patch \
	file://0038-gst145-Revert-omxvideodec-Set-the-already_acquired-f.patch \
	file://0039-gst145-omxvideodec-Drop-frames-which-are-not-keyfram.patch \
	file://0040-gst145-omxvideodec-Avoid-detaching-buffer-metadata-w.patch \
	file://0041-gst145-omxvideodec-Add-a-support-for-the-page-alignm.patch \
	file://0042-gst145-omxvideodec-Export-a-first-dmabuf-file-descri.patch \
	file://0043-gst145-omxbufferpool-fix-memory-leak-in-gst_omx_buff.patch \
	file://0044-gst145-gstomx-fix-memory-leak-in-_class_init-functio.patch \
	file://0045-gst145-omxvideoenc-add-nPFrames-for-AVCINTRAPERIOD-c.patch \
	file://0046-gst145-omxvideoenc-Handle-for-valid-output-frames-on.patch \
	file://0047-gst145-omxh264enc-Support-periodicty_idr-and-interva.patch \
	file://0048-gst145-omxbufferpool-Fixed-memory-corruption-and-bad-acc.patch \
	file://0049-gst145-omxvideodec-add-planebuf-to-allocation-reques.patch \
	file://0050-gst145-omxvideoenc-add-UseBuffer-with-physical-addr.patch \
	file://0051-gst145-omxvideoenc-Add-re-matching-p_address.patch \
	file://0052-gst145-omxvideoenc-add-querysink-for-inbuf-address.patch \
	"

LIC_FILES_CHKSUM_remove_rzg1 = " file://omx/gstomx.h;beginline=1;endline=21;md5=5c8e1fca32704488e76d2ba9ddfa935f"
LIC_FILES_CHKSUM_append_rzg1 = " file://omx/gstomx.h;beginline=1;endline=22;md5=9281ffe981001da5a13db0303fa7c4ab"
