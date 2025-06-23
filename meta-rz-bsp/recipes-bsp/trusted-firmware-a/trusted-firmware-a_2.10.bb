require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg3e-family)"

LIC_FILES_CHKSUM = "file://${WORKDIR}/git/docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"
PV = "2.10+git${SRCPV}"

S = "${WORKDIR}/git"

TFA_URI ?= "git://github.com/renesas-rz/rzg_trusted-firmware-a.git;protocol=https;nobranch=1"
TFA_REV ?= "14edb76fc287f360812eb0cc820a2a60265bebcc"

SRC_URI = "${TFA_URI}"
SRCREV = "${TFA_REV}"

BUILD_DIR = "${B}/${TFA_PLATFORM}"
BUILD_DIR .= "/${@'debug' if d.getVar("TFA_DEBUG") == '1' else 'release'}"

do_deploy[noexec] = "1"

EXTRA_OEMAKE:append = " PLAT_SYSTEM_SUSPEND=1"
