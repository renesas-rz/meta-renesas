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
