SUMMARY = "RZ/G2 TF-A NS_BL2U"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=f0ee3f2f59c4b4f33c4876647af7eb9f"

PACKAGE_ARCH = "${MACHINE_ARCH}"

NS_BL2U_URL = "git://github.com/renesas-rz/rzg_tf-a_ns-bl2u.git"
BRANCH = "main"

SRC_URI = "${NS_BL2U_URL};branch=${BRANCH};protocol=https"
SRCREV = "b7a9f96c5ba81ab920cd46d96a89a248e1cb9ff5"

SRC_URI_append = " \
	file://0001-Fix-build-with-gcc-8.3.patch \
"

inherit deploy

S = "${WORKDIR}/git"

do_compile() {
    oe_runmake
}

do_deploy() {
    install -d ${DEPLOYDIR}

    install -m 0644 ${B}/out/ns_bl2u.elf ${DEPLOYDIR}/ns_bl2u-${MACHINE}.elf
    install -m 0644 ${B}/out/ns_bl2u.bin ${DEPLOYDIR}/ns_bl2u-${MACHINE}.bin
}
addtask deploy before do_build after do_compile
