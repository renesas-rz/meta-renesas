SUMMARY = "Boot loader for RZV2M(A)"
SECTION = "Loader"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

PV_rzv2m = "v1.3.0"
PV_rzv2ma = "v1.1.0"
PR = "r1"

S = "${WORKDIR}"

PACKAGE_ARCH = "${MACHINE_ARCH}"
FILES_${PN}  = "/boot "

inherit deploy

SRC_URI_rzv2m = "file://rzv2m-bootloader-v130.tar.gz"
SRC_URI_rzv2m[md5sum] = "cbd296d9fa0d8ee41b69aa8055d03545"
SRC_URI_rzv2m[sha256sum] = "4955c99be4d4ff6bab1528e138183a02a15697e268e96eea6405264d6c533613"

SRC_URI_rzv2ma = "file://rzv2ma-bootloader-v110.tar.gz"
SRC_URI_rzv2ma[md5sum] = "02e92347f76584e92595394f687ab1a5"
SRC_URI_rzv2ma[sha256sum] = "e78e5a26cee3626ed9e9ad6d8a808a9c6d90dd162becad444fac5b0e35e18e67"

do_compile() {
	cd ${S}/source
	make TARGET=loader_1st
	make TARGET=loader_2nd
}

do_install() {
	install -d ${D}/boot
	install -m 755 ${S}/source/loader_1st.bin ${D}/boot/loader_1st.bin
	install -m 755 ${S}/source/loader_1st_128kb.bin ${D}/boot/loader_1st_128kb.bin
	install -m 755 ${S}/source/loader_2nd.bin ${D}/boot/loader_2nd.bin
	install -m 755 ${S}/source/loader_2nd_param.bin ${D}/boot/loader_2nd_param.bin
}

do_deploy() {
	install -d ${DEPLOYDIR}
	install -m 755 ${S}/source/loader_1st_128kb.bin ${DEPLOYDIR}/loader_1st_128kb.bin
	install -m 755 ${S}/source/loader_2nd.bin ${DEPLOYDIR}/loader_2nd.bin
	install -m 755 ${S}/source/loader_2nd_param.bin ${DEPLOYDIR}/loader_2nd_param.bin
	install -m 755 ${S}/source/loader_1st.elf ${DEPLOYDIR}/loader_1st.elf
	install -m 755 ${S}/source/loader_2nd.elf ${DEPLOYDIR}/loader_2nd.elf
}

addtask deploy before do_build after do_compile
