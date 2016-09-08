SUMMARY = "Startup script for modules"
LICENSE = "CLOSED"

SRC_URI = "file://rtl_module_init"

S = "${WORKDIR}"

do_install() {
	install -d ${D}/${sysconfdir}/init.d
	install -m755 ${WORKDIR}/rtl_module_init ${D}/${sysconfdir}/init.d/rc.modules
}

inherit allarch update-rc.d

INITSCRIPT_NAME = "rc.modules"
INITSCRIPT_PARAMS = "start 8 5 2 . stop 21 0 1 6 ."
