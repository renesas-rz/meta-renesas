require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg3e-family|rzv2h-evk)"

LIC_FILES_CHKSUM = "file://${WORKDIR}/git/docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"
PV = "2.7+git${SRCPV}"

S = "${WORKDIR}/git"

TFA_URI ?= "git://github.com/renesas-rz/rzg_trusted-firmware-a.git;protocol=https"
TFA_REV:rzg3e-family = "01ca346330ed617fce814000c62ac7762eea4bdb"
TFA_BRANCH:rzg3e-family = "2.7.0/rz_dev"
SRC_URI:rzg3e-family = "${TFA_URI};branch=${TFA_BRANCH}"

TFA_REV:rzv2h-evk = "bee53e1a5f2f009a1af320a871d8bac25ad09a5e"
SRC_URI:rzv2h-evk = "${TFA_URI};nobranch=1"

SRCREV = "${TFA_REV}"

BUILD_DIR = "${B}/${TFA_PLATFORM}"
BUILD_DIR .= "/${@'debug' if d.getVar("TFA_DEBUG") == '1' else 'release'}"

do_compile:prepend() {
	# This is still needed to have the native tools executing properly by
	# setting the RPATH
	sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/fiptool/Makefile
}

do_deploy[noexec] = "1"
