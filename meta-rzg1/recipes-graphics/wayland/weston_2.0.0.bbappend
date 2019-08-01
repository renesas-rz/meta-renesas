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
    file://0019-weston-add-weston-desktop-api-set-xwayland-position-.patch \
    file://0020-libweston-libinput-seat-Change-Error-input-device-to.patch \
    file://0021-v4l2-renderer-fix-issue-can-not-read-setting-from-we.patch \
    file://0022-v4l2-renderer-enable-gl-fallback.patch \
    file://0023-desktop-shell-check-NULL-pointer-when-setting-xwayla.patch \
    file://0024-v4l2-renderer-gl-fallback-destroy-gbm-bo-for-surface.patch \
    file://0025-Pass-through-functions-if-keyboard-is-not-inserted.patch \
    file://add-symlink-vsp.rules \
    file://0026-Change-default-name-of-weston-device-node-in-vsp-mode.patch \
"

SRC_URI_append_iwg23s = " file://0001-libweston-fix-issue-can-t-display-to-LCD-at-GPU-mode.patch \
                          file://0001-v4l2-renderer-add-more-formats-for-gl-fallback.patch \
"
INSANE_SKIP_${PN} += "dev-so"
INSANE_SKIP_${PN} += "installed-vs-shipped"
TARGET_CC_ARCH += "${LDFLAGS}"
FILES_${PN} += "${libdir}/* "

RDEPENDS_weston-examples_append = " gles-user-module "
RDEPENDS_libweston-2_append = " gles-user-module "
RDEPENDS_${PN}_append = " gles-user-module xkeyboard-config"

DEPENDS += "libmediactl-v4l2"

# Rule for indentify LVDS touch device.
# Without this rule, if users connect HDMI touch device, they cannot touch
#    correctly on LVDS (all touch event will go to HDMI screen)
SRC_URI_append_iwg20m-g1m = " file://iwg20m-lvdstouch.rules "
SRC_URI_append_iwg20m-g1n = " file://iwg20m-lvdstouch.rules "
SRC_URI_append_iwg21m = " file://iwg21m-hdmitouch.rules "

do_install_append () {
    ln -sf v4l2-vsp-device.so ${D}/${libdir}/libweston-2/v4l2-fe928000-device.so
    ln -sf v4l2-vsp-device.so ${D}/${libdir}/libweston-2/v4l2-vsp2-device.so
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/add-symlink-vsp.rules ${D}/${sysconfdir}/udev/rules.d/
}

do_install_append_iwg20m-g1m () {
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/iwg20m-lvdstouch.rules ${D}/${sysconfdir}/udev/rules.d/
}

do_install_append_iwg20m-g1n () {
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/iwg20m-lvdstouch.rules ${D}/${sysconfdir}/udev/rules.d/
}

do_install_append_iwg21m () {
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/iwg21m-hdmitouch.rules ${D}/${sysconfdir}/udev/rules.d/
}


FILES_${PN}_append_iwg20m-g1m += " ${sysconfdir}/udev/rules.d/iwg20m-lvdstouch.rules "
FILES_${PN}_append_iwg20m-g1n += " ${sysconfdir}/udev/rules.d/iwg20m-lvdstouch.rules "
FILES_${PN}_append_iwg21m += " ${sysconfdir}/udev/rules.d/iwg21m-hdmitouch.rules "
FILES_${PN}_append += " ${sysconfdir}/udev/rules.d/add-symlink-vsp.rules "
