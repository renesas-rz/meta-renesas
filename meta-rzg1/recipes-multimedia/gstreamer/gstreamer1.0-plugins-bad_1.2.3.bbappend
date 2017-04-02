require ../../include/gles-control.inc
require ../../include/multimedia-control.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_rzg1 = "gitsm://github.com/renesas-devel/gst-plugins-bad.git;protocol=git;branch=RCAR-GEN2/1.2.3"

SRCREV_rzg1 = "${@'bfd9dfa9c843edd23f7197f8bc1ec08b2ee363c3' \
    if '1' in '${USE_GLES_WAYLAND}' else 'c1f5e09ce341f3438fb601a852ee70e72d375646'}"
LIC_FILES_CHKSUM_remove_rzg1 = "\
    file://common/coverage/coverage-report.pl;beginline=2;endline=17;md5=a4e1830fce078028c8f0974161272607 \
"

S = "${WORKDIR}/git"

do_configure() {
    ./autogen.sh --noconfigure
    oe_runconf
}

# for wayland
PACKAGECONFIG_remove_rzg1 = "${@'orc' if '1' in '${USE_GLES_WAYLAND}' else ''}"
PACKAGECONFIG_append_rzg1 = " ${@base_contains('USE_GLES_WAYLAND', '1', 'wayland', '', d)}"


SRC_URI_append_rzg1 = "${@\
     ' file://0001-gst-plugins-bad-waylandsink-Add-set-window-position.patch \
       file://0002-gst-plugins-bad-waylandsink-Add-set-window-scale.patch \
       file://0003-waylandsink-fix-memory-leak.patch \
       file://0004-fix-segmentation-fault-of-waylandsink-inspect.patch' \
     if '1' in '${USE_GLES_WAYLAND}' else ''}"


# Depend to libmemcpy as it is used in patch 0003
DEPENDS_append = "${@' libmemcpy' if '1' in '${USE_GLES_WAYLAND}' else ''}"

