require include/gles-control.inc
DEPENDS_append = " \
    ${@'libegl gles-user-module' if '${USE_GLES_WAYLAND}' == '1'  else ''} \
"
