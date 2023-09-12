FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
	${@oe.utils.conditional("USE_ECC", "1", "file://0001-arch-riscv-dts-renesas-r9a07g043f01-smarc-dev-reserv.patch", "", d)} \
"
