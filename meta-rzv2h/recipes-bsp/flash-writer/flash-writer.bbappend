FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

PV="0.6"

S = "${WORKDIR}"

COMPATIBLE_MACHINE = "(r9a09g057)"
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

SRC_URI = "file://Flash_Writer_SCIF_RZV2H_DEV_INTERNAL_MEMORY.mot"
SRC_URI[md5sum] = "33ac1ccb33a07f574255b4329feb02a9"
SRC_URI[sha256sum] = "90d62cf98015bdb6489461ca8bb5cb458c261fe0b5fa555170e45f0aca8ca244"

do_compile[noexec] = "1"
do_install[noexec] = "1"

do_deploy() {
	install -d ${DEPLOYDIR}
	install -m 755 ${S}/Flash_Writer_SCIF_RZV2H_DEV_INTERNAL_MEMORY.mot ${DEPLOYDIR}
}

addtask deploy before do_build after do_compile
