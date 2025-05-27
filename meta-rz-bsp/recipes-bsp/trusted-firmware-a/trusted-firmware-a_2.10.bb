require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg3e-family)"

LIC_FILES_CHKSUM = "file://${WORKDIR}/git/docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"
PV = "2.10+git${SRCPV}"

S = "${WORKDIR}/git"

TFA_URI ?= "git://github.com/renesas-rz/rzg_trusted-firmware-a.git;protocol=https"
TFA_REV ?= "1388d7f30cc76fdfc2adc17bea35cba20f03a322"
TFA_BRANCH ?= "2.10.5/rz_main"

SRC_URI = "${TFA_URI};branch=${TFA_BRANCH}"
SRCREV = "${TFA_REV}"

BUILD_DIR = "${B}/${TFA_PLATFORM}"
BUILD_DIR .= "/${@'debug' if d.getVar("TFA_DEBUG") == '1' else 'release'}"

do_compile:prepend() {
	# This is still needed to have the native tools executing properly by
	# setting the RPATH
	sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/fiptool/Makefile
}

do_deploy[noexec] = "1"

EXTRA_OEMAKE:append = " PLAT_SYSTEM_SUSPEND=1"
