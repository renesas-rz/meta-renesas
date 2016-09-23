LICENSE = "CLOSED"
DESCRIPTION = "Linux bluetooth firmware"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI = " \
	file://rtl8723a_fw.bin \
	file://rtl8723b_fw.bin \
	file://rtl8761a_fw.bin \
	file://rtl8821a_fw.bin \
	file://LICENCE.txt \
"

S = "${WORKDIR}"

do_install () {
	install -d ${D}/${base_libdir}/firmware
	install -m 775 ${S}/rt*.bin ${D}/${base_libdir}/firmware
	install -m 775 ${S}/LICENCE.txt ${D}/${base_libdir}/firmware

	install -d ${D}/${base_libdir}/firmware/rtl_bt
	install -m 775 ${S}/rt*.bin ${D}/${base_libdir}/firmware/rtl_bt
	install -m 775 ${S}/LICENCE.txt ${D}/${base_libdir}/firmware/rtl_bt
}

INSANE_SKIP_${PN} += "ldflags"
do_patch[noexec] = "1"
do_cofigure[noexec] = "1"
do_compile[noexec] = "1"

PACKAGES = "${PN}"

FILES_${PN} = " /* "
