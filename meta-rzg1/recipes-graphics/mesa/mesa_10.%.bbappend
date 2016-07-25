require ../../include/gles-control.inc


FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append := " \
			file://0001-Mesa-include-the-stat.h-for-fixing-compile-errors.patch \
"


def map_libs(d):
    if base_conditional('USE_GLES_WAYLAND', "1", "1", "0", d) == "1":
        return "wayland"

    if base_conditional('USE_GLES_X11', "1", "1", "0", d) == "1":
        return "x11"

    return "dummy"

MESATARGET := "${@map_libs(d)}"
include mesa-${MESATARGET}.inc
