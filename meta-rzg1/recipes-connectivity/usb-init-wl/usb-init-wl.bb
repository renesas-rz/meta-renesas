SUMMARY = "Startup script for USB modules"
LICENSE = "CLOSED"

SRC_URI = "file://usbwl-init"

S = "${WORKDIR}"

do_install() {
	install -d ${D}/${sysconfdir}/init.d
	install -m755 ${WORKDIR}/usbwl-init ${D}/${sysconfdir}/init.d/rc.usbwl
}

inherit allarch update-rc.d

INITSCRIPT_NAME = "rc.usbwl"
INITSCRIPT_PARAMS = "start 8 5 2 . stop 21 0 1 6 ."
