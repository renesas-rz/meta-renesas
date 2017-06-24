require ../../include/gles-control.inc
require ../../include/multimedia-control.inc

PACKAGECONFIG_rzg1 := "${@'${PACKAGECONFIG}'.replace('x11', '')}"

PACKAGECONFIG_append_rzg1 = " \
    ${@base_conditional('USE_GLES', '1', '', 'fbdev', d)}"
DEPENDS_append_rzg1 = " \
    ${@base_conditional('USE_GLES', '1', 'gles-user-module', '', d)} \
    ${@base_conditional('USE_GLES_MULTIMEDIA', '1', 'libmediactl-v4l2', '', d)}"
REPENDS_append_rzg1 = " \
    ${@'vsp2-kernel-module' \
    if '${USE_GLES}' == '1' and '${USE_MULTIMEDIA}' == '1' else ''}"
    
EXTRA_OECONF_append_rzg1 = " \
    ${@base_conditional('USE_GLES', '1', '--enable-v4l2', \
    '--disable-xwayland-test WESTON_NATIVE_BACKEND=fbdev-backend.so', d)}"

SRCREV_rzg1 = "${@'f14615019f94897041164fd95df3b42349ec59e6' \
    if '1' in '${USE_GLES}' else '00781bcf518f6bab0d08e6962630b0994e8bf632'}"
SRC_URI_rzg1 = " \
    git://github.com/renesas-devel/weston.git;protocol=git;branch=RCAR-GEN2/1.5.0/gl-fallback \
    file://weston.desktop \
    file://weston.png \
    file://disable-wayland-scanner-pkg-check.patch \
    file://make-lcms-explicitly-configurable.patch \
    file://make-libwebp-explicitly-configurable.patch \
"
SRC_URI_append_rzg1 = " \
    ${@base_conditional("USE_GLES_MULTIMEDIA", "1", \
        "file://vsp-renderer-Change-VSP-device-from-VSP1-to-VSP2.patch", "", d)} \
"
S = "${WORKDIR}/git"

RDEPENDS_${PN}_append_rzg1 = " \
    ${@base_conditional('USE_GLES', '1', 'media-ctl', '', d)} \
    ${@base_conditional('USE_GLES_MULTIMEDIA', '1', 'vsp2-kernel-module', '', d)}"


SRC_URI_append_rzg1 = " \
    file://0001-desktop-shell-add-option-to-avoid-creating-the-panel.patch \
    file://0017-Fixed-memory-corruption-when-focus-listener-is-moved.patch \
    file://0020-set-position-to-fix-problem-app-under-weston-bar.patch \
"

# libinput improves touch features on Wayland/Weston
# Without this lib, Weston will use old touch implement and cannot
#    support multiple touch screens.
# Note that currently API of libinput is not stable, so newer version
#    of Weston may require newer version of libinput (and vice versa)
DEPENDS += "libinput"
EXTRA_OECONF += " --enable-libinput-backend "

# Rule for indentify LVDS touch device.
# Without this rule, if users connect HDMI touch device, they cannot touch
#    correctly on LVDS (all touch event will go to HDMI screen)
SRC_URI_append_iwg20m = " file://iwg20m-lvdstouch.rules "

do_install_append_iwg20m () {
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/iwg20m-lvdstouch.rules ${D}/${sysconfdir}/udev/rules.d/
}

FILES_${PN}_append_iwg20m += " ${sysconfdir}/udev/rules.d/iwg20m-lvdstouch.rules "

SRC_URI_append_iwg21m = " file://iwg21m-lvdstouch.rules "

do_install_append_iwg21m () {
    install -d ${D}/${sysconfdir}/udev/rules.d/
    install ${WORKDIR}/iwg21m-lvdstouch.rules ${D}/${sysconfdir}/udev/rules.d/
}

FILES_${PN}_append_iwg21m += " ${sysconfdir}/udev/rules.d/iwg21m-lvdstouch.rules "

# iwg23s have no default connected input for weston. This patch fix issue weston can't startup 
# if there's no input device
SRC_URI_append_iwg23s = " file://0001-fix-issue-weston-can-t-start-when-there-s-no-input-d.patch "

DEPENDS += " libmediactl-v4l2 "
