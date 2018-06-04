require include/gles-control.inc

PACKAGECONFIG_rzg1 := "${@'${PACKAGECONFIG}'.replace('x11', '')}"
PACKAGECONFIG_virtclass-multilib-lib32 := "${@'${PACKAGECONFIG}'.replace('launch', '')}"
DEPENDS_append_rzg1 = " \
    ${@base_conditional('USE_GLES', '1', 'libegl', '', d)} \
    ${@base_conditional('USE_GLES_MULTIMEDIA', '1', 'libmediactl-v4l2', '', d)}"
EXTRA_OECONF_append = " \
    ${@base_conditional('USE_GLES', '1', '', \
    ' WESTON_NATIVE_BACKEND="fbdev-backend.so"', d)}"