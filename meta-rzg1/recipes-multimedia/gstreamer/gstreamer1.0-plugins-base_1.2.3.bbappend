require ../../include/gles-control.inc

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
