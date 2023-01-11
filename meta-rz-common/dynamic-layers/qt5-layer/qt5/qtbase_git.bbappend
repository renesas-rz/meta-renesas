#Revision for qt5.6.3
require qt5.6.3_git.inc
SRCREV = "e6f8b072d2bf15f8b82bede48ff29ce8ac8dbd9a"

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv21;md5=fb91571854638f10b2e5f36562661a5a \
    file://LICENSE.LGPLv3;md5=a909b94c1c9674b2aa15ff03a86f518a \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
    file://LICENSE.FDL;md5=6d9f2a9af4c8b8c3c769f6cc1b6aaf7e \
"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:" 
 
SRC_URI_append = " \
    file://0001-Fix-division-by-zero-in-radial-gradiants-with-NEON.patch \
    file://0002-Make-tst_QOpenGLWindow-pass-on-platforms-where-the-d.patch \
    file://0003-Blacklist-and-skip-failing-tests-for-Boot2Qt-64-bit-.patch \
    file://0004-Skip-failing-tests-in-tst_QWindow-on-Wayland.patch \
    file://0005-mkspecs-linux-oe-g-Add-check-oe-device-extra.pri-bef.patch \
    file://0006-qt-base-remove-use-of-OE_QMAKE_WAYLAND_SCANNER.patch \
"

# switch to GLES 2 support
PACKAGECONFIG_GL = "${@bb.utils.contains('DISTRO_FEATURES', 'opengl', 'gles2', '', d)}"

DEP = " mtdev libxkbcommon freetype fontconfig libinput libproxy"

RDEPENDS_${PN} += "${DEP}"
RDEPENDS_${PN}-plugins += "${DEP}"
RDEPENDS_${PN}-examples += "${DEP}"

# qtbase does not support openssl 1.1 until version 5.10
PACKAGECONFIG_remove = "openssl"

# add necessary packages
PACKAGECONFIG_append = " sql-sqlite sql-sqlite2 openssl icu accessibility examples"

# Select wayland as the default platform abstraction plugin for Qt
CONF_ADD_X11 = "${@bb.utils.contains('DISTRO_FEATURES', 'x11', ' -qpa xcb -xcb -xcb-xlib -system-xcb -eglfs', '', d)}"
CONF_ADD_WAYLAND = "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', ' -qpa wayland -no-xcb -wayland', '', d)}"

PACKAGECONFIG_CONFARGS_append += "\
	-no-kms \
	-no-gbm \
	-no-pulseaudio \
	-no-alsa \
	-no-gtkstyle \
	-no-evdev \
	-no-kms \
	-no-sse2 \
	-no-sse3 \
	${CONF_ADD_WAYLAND} \
"

# add necessary packages
PACKAGECONFIG_append += " sm linuxfb gles2"

# nis option is not supported anymore, disable it here
PACKAGECONFIG[nis] = ""

INSANE_SKIP_qtbase-plugins = " file-rdeps"

#Skip QA for patch-fuzz here because main layer meta-qt5 has patch that is not matched with source, also their source too.
WARN_QA_remove = "patch-fuzz"
