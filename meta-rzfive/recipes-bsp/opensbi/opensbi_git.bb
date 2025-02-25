SUMMARY = "RISC-V Open Source Supervisor Binary Interface (OpenSBI)"
DESCRIPTION = "OpenSBI aims to provide an open-source and extensible implementation of the RISC-V SBI specification for a platform specific firmware (M-mode) and a general purpose OS, hypervisor or bootloader (S-mode or HS-mode). OpenSBI implementation can be easily extended by RISC-V platform or System-on-Chip vendors to fit a particular hadware configuration."
LICENSE = "BSD-2-Clause"
LIC_FILES_CHKSUM = "file://COPYING.BSD;md5=42dd9555eb177f35150cf9aa240b61e5"

inherit autotools-brokensep deploy

PV = "1.5+git${SRCPV}"

BRANCH = "rzfive-release-1.5.x"
SRCREV="40e7d0d04bce6622a8118d6f2a8ab884bf91ad00"

SRC_URI = " \
	git://github.com/renesas-rz/rz_opensbi.git;protocol=https;branch=${BRANCH} \
"

S = "${WORKDIR}/git"

RISCV_SBI_PLAT = "generic"
EXTRA_OEMAKE += "PLATFORM=${RISCV_SBI_PLAT} "

do_deploy () {
	install -m 755 ${S}/build/platform/${RISCV_SBI_PLAT}/firmware/fw_dynamic.* ${DEPLOYDIR}/
}

addtask deploy before do_build after do_install

FILES:${PN} += "/share/opensbi/*/${RISCV_SBI_PLAT}/firmware/fw_jump.*"
FILES:${PN} += "/share/opensbi/*/${RISCV_SBI_PLAT}/firmware/fw_payload.*"
FILES:${PN} += "/share/opensbi/*/${RISCV_SBI_PLAT}/firmware/fw_dynamic.*"

COMPATIBLE_HOST = "(riscv64|riscv32).*"
INHIBIT_PACKAGE_STRIP = "1"

SECURITY_CFLAGS = ""
