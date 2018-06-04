require weston.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = "\
    file://0001-add-vsp-renderer.patch        \
    file://0002-add-dmabuf-support-direct-renderring.patch      \
    file://0003-Add-V4L2_RENDERER_LIBS-to-libweston-2-folder.patch      \
    file://0001-port-patches-from-yocto-2-0.patch      \
"

INSANE_SKIP_${PN} += "dev-so"
INSANE_SKIP_${PN} += "installed-vs-shipped"
TARGET_CC_ARCH += "${LDFLAGS}"
FILES_${PN} += "${libdir}/* ${libdir}/${BPN}/v4l2-fe928000-device.so ${libdir}/libweston-2/v4l2-vsp2-device.so"

RDEPENDS_weston-examples_append = " gles-user-module "
RDEPENDS_libweston-2_append = " gles-user-module "
RDEPENDS_${PN}_append = " gles-user-module xkeyboard-config"

# Rule for indentify LVDS touch device.
# Without this rule, if users connect HDMI touch device, they cannot touch
#    correctly on LVDS (all touch event will go to HDMI screen)
SRC_URI_append_iwg20m = " file://iwg20m-lvdstouch.rules "

do_install_append_iwg20m () {
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/iwg20m-lvdstouch.rules ${D}/${sysconfdir}/udev/rules.d/

    ln -sf v4l2-vsp-device.so ${D}/${libdir}/libweston-2/v4l2-fe928000-device.so
    ln -sf v4l2-vsp-device.so ${D}/${libdir}/libweston-2/v4l2-vsp2-device.so
}

FILES_${PN}_append_iwg20m += " ${sysconfdir}/udev/rules.d/iwg20m-lvdstouch.rules "
