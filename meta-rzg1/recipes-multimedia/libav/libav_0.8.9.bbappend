# Don't depend on x11 in core-image-weston or error will happen because libGL does not exist
PACKAGECONFIG = "${@'bzip2 x264' if 'wayland' in '${DISTRO_FEATURES}' else 'bzip2 x264 x11'}"
