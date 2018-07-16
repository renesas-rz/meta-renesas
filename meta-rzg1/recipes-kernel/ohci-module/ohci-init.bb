SUMMARY = "Script for unloading ohci during rebooting or shutting down system"
LICENSE = "CLOSED"

SRC_URI = "file://init"

S = "${WORKDIR}"

do_install() {
	install -d ${D}/${sysconfdir}/init.d
	install -m755 ${WORKDIR}/init ${D}/${sysconfdir}/init.d/ohci
}

inherit allarch update-rc.d

INITSCRIPT_NAME = "ohci"
INITSCRIPT_PARAMS = "stop 100 0 1 6 ."
