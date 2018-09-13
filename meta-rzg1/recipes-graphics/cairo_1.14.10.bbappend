require include/gles-control.inc

# Enable egl and glesv2 config for using Cairo in Wayland environment
# But don't add these configs to native class or error will happen
PACKAGECONFIG_append_class-target = "${@' egl glesv2' if '${USE_GLES_WAYLAND}' == '1'  else ''}"

RDEPENDS_${PN}-script-interpreter += "gles-user-module"
RDEPENDS_${PN}-gobject += "gles-user-module"
RDEPENDS_${PN}_class-target += "gles-user-module"
