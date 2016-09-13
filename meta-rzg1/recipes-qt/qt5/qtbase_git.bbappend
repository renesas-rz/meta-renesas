

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
