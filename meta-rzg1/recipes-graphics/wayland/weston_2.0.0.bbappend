require weston.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = "\
    file://0001-add-vsp-renderer.patch        \
    file://0002-add-dmabuf-support-direct-renderring.patch      \
    file://0003-Add-V4L2_RENDERER_LIBS-to-libweston-2-folder.patch      \
    file://0001-port-patches-from-yocto-2-0.patch      \
    file://0006-weston-fix-No-usable-crtc-encoder-pair-for-connector.patch \
    file://0007-v4l2-vsp-renderer-Improve-dmabuf-and-support-more-fo.patch \
    file://0018-weston-correct-warning-of-weston-not-start-if-no-input-devices.patch      \
"

SRC_URI_append_iwg23s = " file://0001-libweston-fix-issue-can-t-display-to-LCD-at-GPU-mode.patch "
INSANE_SKIP_${PN} += "dev-so"
INSANE_SKIP_${PN} += "installed-vs-shipped"
TARGET_CC_ARCH += "${LDFLAGS}"
FILES_${PN} += "${libdir}/* "

RDEPENDS_weston-examples_append = " gles-user-module "
RDEPENDS_libweston-2_append = " gles-user-module "
RDEPENDS_${PN}_append = " gles-user-module xkeyboard-config"

# Rule for indentify LVDS touch device.
# Without this rule, if users connect HDMI touch device, they cannot touch
#    correctly on LVDS (all touch event will go to HDMI screen)
SRC_URI_append_iwg20m = " file://iwg20m-lvdstouch.rules "
SRC_URI_append_iwg22m = " file://iwg22m-lvdstouch.rules "

do_install_append () {
    ln -sf v4l2-vsp-device.so ${D}/${libdir}/libweston-2/v4l2-fe928000-device.so
    ln -sf v4l2-vsp-device.so ${D}/${libdir}/libweston-2/v4l2-vsp2-device.so
}

do_install_append_iwg20m () {
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/iwg20m-lvdstouch.rules ${D}/${sysconfdir}/udev/rules.d/
}

do_install_append_iwg22m () {
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/iwg22m-lvdstouch.rules ${D}/${sysconfdir}/udev/rules.d/
}

FILES_${PN}_append_iwg20m += " ${sysconfdir}/udev/rules.d/iwg20m-lvdstouch.rules "
FILES_${PN}_append_iwg22m += " ${sysconfdir}/udev/rules.d/iwg22m-lvdstouch.rules "
