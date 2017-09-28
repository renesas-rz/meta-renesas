FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append = " file://0001-protocol-Add-pkgconfig-file-to-be-referred-from-clie.patch \
                   file://0002-Weston-add-support-set-position-from-client.patch \
                   file://0003-Weston-add-support-set-scaling-from-client.patch \
                   file://0004-media-ctl-Separate-libmediactl-code-from-weston.patch \
                   file://0005-Revert-V4L2-renderer-workaround-for-a-bulid-error.patch \
                   file://0006-fix-kernel-warning-for-v4l2-renderer.patch \
		   file://0007-compositor-drm-map-framebuffers-with-read-write-perm.patch \
                   file://0008-v4l2-renderer-clear-dmabuf-fd-when-a-kms-buffer-is-d.patch \
                   file://0009-v4l2-renderer-set-length-and-bytesused-of-each-plane.patch \
                   file://0010-vsp-renderer-set-bytesused-and-length-of-v4l2_surfac.patch \
                   file://0011-vsp-renderer-save-returned-length-and-bytesused-from.patch \
                   file://0012-vsp-renderer-initialize-v4l2_mbus_framefmt-variable.patch \
                   file://0013-Fix-memory-leaks.patch \
                   file://0014-Fix-memory-leak-in-vsp-renderer.patch \
                   file://0015-Fix-gl-fallback.patch \
		   file://0016-Fix-kernel-warning.patch \
		   file://0017-workaround-rcar-crtc.patch \
		   file://0018-weston_fix_issue_not_start_if_no_input_device.patch \
                 "

do_install_append() {
    # install xml for client applications
    install -d ${D}/${datadir}/wayland-protocols/
    install -m 644 ${S}/protocol/linux-dmabuf.xml ${D}/${datadir}/wayland-protocols/
}

# Rule for indentify LVDS touch device.
# Without this rule, if users connect HDMI touch device, they cannot touch
#    correctly on LVDS (all touch event will go to HDMI screen)
SRC_URI_append_iwg20m = " file://iwg20m-lvdstouch.rules "

do_install_append_iwg20m () {
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/iwg20m-lvdstouch.rules ${D}/${sysconfdir}/udev/rules.d/
}

FILES_${PN}_append_iwg20m += " ${sysconfdir}/udev/rules.d/iwg20m-lvdstouch.rules "
