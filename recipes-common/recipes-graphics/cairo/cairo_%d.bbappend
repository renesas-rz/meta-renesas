PACKAGECONFIG_append_class-target = " ${@' egl ' if '${EXT_GFX_BACKEND}' == '1' and 'x11' in '${DISTRO_FEATURES}' else ''} "
