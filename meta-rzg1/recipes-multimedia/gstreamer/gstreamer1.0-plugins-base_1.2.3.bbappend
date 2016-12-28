require ../../include/gles-control.inc
require ../../include/multimedia-control.inc

SRC_URI_rzg1 = "git://github.com/renesas-devel/gst-plugins-base.git;protocol=git;branch=RCAR-GEN2/1.2.3"
SRCREV_rzg1 = "b3a5d9f75ed82739ecae6d866f9b268d1e13cec5"
LIC_FILES_CHKSUM_remove_rzg1 = "\
    file://common/coverage/coverage-report.pl;beginline=2;endline=17;md5=a4e1830fce078028c8f0974161272607 \
"

S = "${WORKDIR}/git"

do_configure() {
    ./autogen.sh --noconfigure
    oe_runconf
}

# For Common
FILESEXTRAPATHS_prepend_rzg1 := '${THISDIR}/${PN}:'
VSPFILTER_CONFIGS = " \
    file://gstvspfilter-skrzg1m.conf \
    file://gstvspfilter-skrzg1e.conf \
    file://gstvspfilter-iwg20m.conf \
    file://gstvspfilter-iwg21m.conf \
"

# For wayland
PACKAGECONFIG_remove_rzg1 = "${@base_contains("DISTRO_FEATURES", "wayland", "orc", "", d)}"

SRC_URI_append_rzg1 = " \
    ${@'${VSPFILTER_CONFIGS}' \
    if '${USE_WAYLAND}' == '1' else ''}"

EXTRA_OECONF_append_rzg1 = " \
    ${@'--enable-vspfilter' \
    if '${USE_WAYLAND}' == '1' else ''}"

do_install_append_rzg1() {
    if [ '${USE_WAYLAND}' = '1' ] ; then
        mkdir ${D}/etc/
        install -m644 ${WORKDIR}/gstvspfilter-${MACHINE}.conf ${D}/etc/gstvspfilter.conf
    fi
}

FILES_${PN}_append_rzg1 = " \
    ${@'${datadir}/gst-plugins-base/1.0/* ${sysconfdir}/*.conf' \
    if '${USE_WAYLAND}' == '1' else ''}"

# For x11
# None

# Add vspmfilter
SRC_URI_append_rzg1 += ' ${@base_contains("USE_MULTIMEDIA", "1", " \
    file://0001-gst-plugins-base-vspmfilter-Add-new-plugin-support-DMAbuf.patch \
    file://0002-gst-plugins-base-vspmfilter-add-outbuf-alloc-mode.patch \
    file://0003-gst-plugins-base-videoencoder-fix-error-w-I420-format.patch \
    file://0004-vspmfilter-Align-the-start-address-of-the-CbCr-ingre.patch \
    file://0005-gst-plugins-base-playbin-add-properties-decode-dmabuf-and-decode-nocopy.patch \
    file://0006-vspmfilter-add-RGB-and-RGBx-output.patch \
    file://0007-vspmfilter-fix-memory-leak.patch \
    file://0008-vspmfilter-Rewrite-implement-for-swap.patch \
    file://0009-vspmfilter-Add-all-possible-format-that-vspm-can-han.patch \
    file://0010-vspmfilter-Rewrite-caps-with-available-format-only.patch \
    file://0011-vspmfilter-Update-setting-in-out-params.patch \
    file://0012-gstvspmfilter-add-bufferpool.patch \
    file://0013-gstvspmfilter-re-add-memory_alignment.patch \
    file://0015-gstplaybin-change-vspmfilter-as-default-converter.patch \
    file://0017-vspmfilter-Fix-mistake-in-storing-dmabuf_pid.patch \
    file://0018-vspmfilter-Fix-crash-issue-in-dmabuf-use-mode-with-s.patch \
    ", "", d)}'

DEPENDS_append += ' ${@base_contains("USE_MULTIMEDIA", "1", " \
    mmngr-kernel-module mmngr-user-module mmngrbuf-kernel-module \
    mmngrbuf-user-module vspm-user-module vspm-kernel-module \
    ", "", d)}'
