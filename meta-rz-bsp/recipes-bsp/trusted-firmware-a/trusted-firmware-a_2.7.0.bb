require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg3e-family|rzg3s-family)"

LIC_FILES_CHKSUM = "file://${WORKDIR}/git/docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"
PV = "2.7+git${SRCPV}"

S = "${WORKDIR}/git"

TFA_URI ?= "git://github.com/renesas-rz/rzg_trusted-firmware-a.git;nobranch=1;protocol=https"
TFA_REV ?= "cca4398c9dfa3a375295630234367caccad5a285"

SRC_URI = "${TFA_URI}"
SRCREV = "${TFA_REV}"

BUILD_DIR = "${B}/${TFA_PLATFORM}"
BUILD_DIR .= "/${@'debug' if d.getVar("TFA_DEBUG") == '1' else 'release'}"

EXTRA_OEMAKE += "FIP_ALIGN=16"

do_compile:prepend() {
	# This is still needed to have the native tools executing properly by
	# setting the RPATH
	sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/fiptool/Makefile
}

do_deploy[noexec] = "1"
