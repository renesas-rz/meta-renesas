inherit systemd

SUMMARY = "Watchdog Timer Service"
LICENSE = "MIT"
LIC_FILES_CHKSUM = " \
	file://COPYING.MIT;md5=d81509f2a88139ee9635b880116710dc \
"

SYSTEMD_AUTO_ENABLE ?= "enable"
SYSTEMD_SERVICE_${PN} = "watchdog.service"
DEPENDS = "linux-renesas"

FILES_${PN} += " \
        ${systemd_unitdir}/system/watchdog.service \
        ${bindir}/watchdog-test \
"

INSANE_SKIP_${PN} = "ldflags"

SRC_URI = " \
	file://watchdog.service \
	file://COPYING.MIT \
"

S = "${WORKDIR}"

do_compile() {
	${CC} -o watchdog-test ${STAGING_KERNEL_DIR}/tools/testing/selftests/watchdog/watchdog-test.c
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 watchdog-test ${D}${bindir}
	install -d ${D}${systemd_unitdir}/system
	install -m 0755 ${WORKDIR}/watchdog.service ${D}${systemd_unitdir}/system
}
