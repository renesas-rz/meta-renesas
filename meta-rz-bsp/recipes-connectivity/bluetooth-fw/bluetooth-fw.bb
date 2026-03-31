DESCRIPTION = "Firmware files for Bluetooth"
LICENSE = "TI-TSPA"
LIC_FILES_CHKSUM = "file://LICENSE;md5=f39eac9f4573be5b012e8313831e72a9"
NO_GENERIC_LICENSE[TI-TSPA] = "LICENSE"

PV = "8.7.1+git${SRCPV}"

CLEANBROKEN = "1"

SRCREV = "3aa1d75f3c2ae77f6e4d36194e3d281b899ab149"
BRANCH = "master"
SRC_URI = "git://git.ti.com/ti-bt/service-packs.git;branch=${BRANCH};protocol=https"

S = "${WORKDIR}/git"

do_compile() {
    :
}

do_install() {
	install -d ${D}${libdir}/firmware/ti-connectivity
	oe_runmake "DEST_DIR=${D}" "BASE_LIB_DIR=${libdir}" install
}

FILES:${PN} += "${libdir}/firmware/ti-connectivity/*"
