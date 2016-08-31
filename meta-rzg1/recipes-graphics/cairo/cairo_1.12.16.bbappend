require meta-rzg1/include/gles-control.inc

PACKAGECONFIG_append = "${@' egl glesv2' if '${USE_GLES_WAYLAND}' == '1'  else ''}"
