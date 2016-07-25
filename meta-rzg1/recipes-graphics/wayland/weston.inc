require include/gles-control.inc

PACKAGECONFIG_rzg1 := "${@'${PACKAGECONFIG}'.replace('x11', '')}"
PACKAGECONFIG_virtclass-multilib-lib32 := "${@'${PACKAGECONFIG}'.replace('launch', '')}"
DEPENDS_append_rzg1 = " \
    ${@base_conditional('USE_GLES', '1', 'libegl', '', d)}"

RDEPENDS_${PN}_append_rzg1 = " \
    ${@base_conditional('USE_GLES', '1', 'libegl', '', d)}"
RDEPENDS_${PN}-examples_append_rzg1 = " \
    ${@base_conditional('USE_GLES', '1', 'libegl', '', d)}"

EXTRA_OECONF_append = " \
    ${@base_conditional('USE_GLES', '1', '', \
    ' WESTON_NATIVE_BACKEND="fbdev-backend.so"', d)}"

PACKAGES_prepend = "${PN}-bin "

FILES_${PN}-bin = "${bindir}/weston \
    ${bindir}/weston-terminal \
    ${bindir}/weston-info \
    ${bindir}/weston-launch \
    ${bindir}/wcap-decode \
"

FILES_${PN} = " \
    ${libdir}/weston \
    ${datadir} \
"

USERADD_PACKAGES = "${PN}-bin"
GROUPADD_PARAM_${PN}-bin = "--system weston-launch"
