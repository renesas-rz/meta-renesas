FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI = " \
	file://FlashWriter.bin;subdir=${BPN} \
	file://FlashWriter.mot;subdir=${BPN} \
	"
SRC_URI[FlashWriter.bin.md5sum] = "f57f27b3d186cf4765cf2dd4b9343bcb"
SRC_URI[FlashWriter.bin.sha256sum] = "e5d18cd9ab6ef3a7a2eb59fe582ea589d441914215c609e1da93ed547274decc"
SRC_URI[FlashWriter.mot.md5sum] = "d78d10b248c2dc97f932f2887227bd0b"
SRC_URI[FlashWriter.mot.sha256sum] = "e6643dc1a98a981f5f72350c711d1de6ddc8bd61f019745069d8085d930ada0c"

PV = "0127"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

S = "${WORKDIR}/${BPN}"
BUILD_TBB_DIR = "${S}/build_tbb"

do_configure[noexec] = "1"

do_compile () {
	# Convert to srec
	objcopy -I binary -O srec --adjust-vma=0xA1E00 --srec-forceS3 ${S}/FlashWriter.bin ${S}/FlashWriter.srec
}

do_deploy () {
	# Create deploy folder
	install -d ${DEPLOYDIR}

	# Copy fip images
	install -m 0644  ${S}/FlashWriter.srec ${DEPLOYDIR}/FlashWriter-${MACHINE}.srec
	install -m 0644  ${S}/FlashWriter.mot ${DEPLOYDIR}/FlashWriter-${MACHINE}.mot
}

addtask deploy before do_build after do_compile
