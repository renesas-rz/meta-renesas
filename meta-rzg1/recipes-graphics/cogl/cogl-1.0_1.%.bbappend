require ../../include/gles-control.inc

DEPENDS_append_rzg1 = " \
    ${@'libegl' if '${USE_GLES_WAYLAND}' == '1'  else ''}"