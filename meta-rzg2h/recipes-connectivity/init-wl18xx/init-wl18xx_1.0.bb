SUMMARY = "Startup script for WL18xx modules to disable Extreme Low Power mode"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI_append = " \
	file://wl18xx-init.sh \
	file://COPYING.MIT \
"

S = "${WORKDIR}"

do_install() {
        install -d ${D}/${sysconfdir}/profile.d
        install -m 0644 ${WORKDIR}/wl18xx-init.sh ${D}/${sysconfdir}/profile.d/wl18xx-init.sh
}

do_configure[noexec] = "1"
do_patch[noexec] = "1"
do_compile[noexec] = "1"

FILES_${PN} = " \
        ${sysconfdir}/profile.d/wl18xx-init.sh \
"
