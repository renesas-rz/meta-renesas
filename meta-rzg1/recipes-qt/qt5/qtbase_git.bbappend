#Revision for qt5.6.3
require qt5.6.3_git.inc
SRCREV = "e6f8b072d2bf15f8b82bede48ff29ce8ac8dbd9a"

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv21;md5=fb91571854638f10b2e5f36562661a5a \
    file://LICENSE.LGPLv3;md5=a909b94c1c9674b2aa15ff03a86f518a \
    file://LICENSE.GPLv3;md5=88e2b9117e6be406b5ed6ee4ca99a705 \
    file://LICENSE.FDL;md5=6d9f2a9af4c8b8c3c769f6cc1b6aaf7e \
"

# switch to GLES 2 support
PACKAGECONFIG_GL = "${@base_contains('DISTRO_FEATURES', 'opengl', 'gles2', '', d)}"

DEP = " ${@base_contains('DISTRO_FEATURES', 'opengl', 'gles-user-module', '', d)} \
       mtdev libxkbcommon freetype fontconfig libinput libproxy"
RDEPENDS_${PN} += "${DEP}"
RDEPENDS_${PN}-plugins += "${DEP}"
RDEPENDS_${PN}-examples += "${DEP}"

# add necessary packages
PACKAGECONFIG_append = " sql-sqlite sql-sqlite2 openssl icu accessibility examples alsa"

# Select wayland as the default platform abstraction plugin for Qt
CONF_ADD_X11 = "${@base_contains('DISTRO_FEATURES', 'x11', ' -qpa xcb -xcb -xcb-xlib -system-xcb -eglfs', '', d)}"
CONF_ADD_WAYLAND = "${@base_contains('DISTRO_FEATURES', 'wayland', ' -qpa wayland -no-xcb -no-eglfs -wayland', '', d)}"

PACKAGECONFIG_CONFARGS_append += " \
            ${CONF_ADD_WAYLAND} \
            "

DEPENDS_append = " gles-user-module"

# add necessary packages
PACKAGECONFIG_append += " sm"

# nis option is not supported anymore, disable it here
PACKAGECONFIG[nis] = ""
