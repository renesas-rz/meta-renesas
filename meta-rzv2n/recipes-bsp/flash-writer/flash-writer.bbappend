FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

PV="0.90"

S = "${WORKDIR}"

COMPATIBLE_MACHINE = "(r9a09g056)"
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

SRC_URI = "file://Flash_Writer_SCIF_RZV2N_DEV_LPDDR4X.mot"
SRC_URI[md5sum] = "711dfa19738f47b88fc2487d3b7fb90a"
SRC_URI[sha256sum] = "7452346978257441f9e0b96b3788e3d10d1c85d3c08d087357137bd9673f8981"

do_compile[noexec] = "1"
do_install[noexec] = "1"

do_deploy() {
	install -d ${DEPLOYDIR}
	install -m 755 ${S}/Flash_Writer_SCIF_RZV2N_DEV_LPDDR4X.mot ${DEPLOYDIR}
}

addtask deploy before do_build after do_compile
