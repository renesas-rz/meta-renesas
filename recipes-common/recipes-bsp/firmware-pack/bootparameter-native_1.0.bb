SECTION = "bootloaders"
DESCRIPTION = "Application to create binaries in the correct format for rzg2l board flashing"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

inherit native

S = "${WORKDIR}"

SRC_URI = "file://bootparameter.c"

do_compile () {
         ${CC} bootparameter.c -o bootparameter
}

do_install () {
    install -d ${D}${bindir}
    install ${WORKDIR}/bootparameter ${D}${bindir}
}
