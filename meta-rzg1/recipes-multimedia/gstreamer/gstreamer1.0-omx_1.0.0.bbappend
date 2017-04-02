require ../../include/gles-control.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_rzg1 = "gitsm://github.com/renesas-devel/gst-omx.git;protocol=git;branch=RCAR-GEN2/1.0.0"
SRCREV_rzg1 = "${@'74ba6e88d431691ffe0aa8f14c3c0300aaafcc6b' \
    if '1' in '${USE_GLES_WAYLAND}' else '05563465faad99243ee2dd30547e3075eb8cf5e3'}"

LIC_FILES_CHKSUM_remove_rzg1 = " file://omx/gstomx.h;beginline=1;endline=21;md5=5c8e1fca32704488e76d2ba9ddfa935f"
LIC_FILES_CHKSUM_append_rzg1 = " file://omx/gstomx.h;beginline=1;endline=22;md5=17e5f2943dace9e5cde4a8587a31e8f9"
S = "${WORKDIR}/git"

do_configure() {
    ./autogen.sh --noconfigure
    oe_runconf
}

DEPENDS_append_rzg1 = " omx-user-module mmngrbuf-user-module"
EXTRA_OECONF_append_rzg1 = " \
    --with-omx-target=rcar --enable-experimental \
    '${@'--enable-nv12-page-alignment' if '${USE_GLES_WAYLAND}' == '1' else ''}' \
    '${@'--disable-dmabuf' if '${USE_GLES}' == '0' and '${USE_WAYLAND}' == '1' else ''}'"

# Overwrite do_install[postfuncs] += " set_omx_core_name "
# because it will force the plugin to use bellagio instead of our config
revert_omx_core_name() {
    sed -i -e "s;^core-name=.*;core-name=/usr/local/lib/libomxr_core.so;" "${D}/etc/xdg/gstomx.conf"
}

REVERT_OMX_CORE_NAME = ""
REVERT_OMX_CORE_NAME_rzg1 = "revert_omx_core_name"
do_install[postfuncs] += "${REVERT_OMX_CORE_NAME}"

SRC_URI_append_rzg1 = "${@\
    ' file://0005-omxvideoenc-add-nPFrames-for-AVCINTRAPERIOD-config.patch \
      file://0011-fix-memory-leak-for-omx.patch \
      file://0012-fix-memory-leak-for-omxvideodec.patch' \
    if '1' in '${USE_GLES_WAYLAND}' else ''}"

