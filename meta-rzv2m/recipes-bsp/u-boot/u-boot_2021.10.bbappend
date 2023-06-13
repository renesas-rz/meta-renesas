FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

BRANCH_rzv2m = "v2m/v2021.10/rz"
SRCREV_rzv2m = "873a42e1d0bd69ec73abb2ca7d56245fe4033904"

BRANCH_rzv2ma = "v2ma/v2021.10/rz"
SRCREV_rzv2ma = "31ac07aba125e40c938fb19b16c7b05d85e44fca"


EXE_PYTHON = "python3"
PY_FILE = "${B}/${config}/scripts/sum.py"

do_compile_append(){
	rm -f ${B}/${config}/u-boot_param.bin
	python3 ${B}/${config}/source/scripts/sum.py ${B}/${config}/${UBOOT_SYMLINK} ${B}/${config}/u-boot_param.bin
}

do_install_append () {
	install -m 644 ${B}/${config}/u-boot_param.bin ${D}/boot/u-boot_param.bin
}

do_deploy_append  () {
	install -m 644 ${B}/${config}/u-boot_param.bin ${DEPLOYDIR}/u-boot_param.bin
}
