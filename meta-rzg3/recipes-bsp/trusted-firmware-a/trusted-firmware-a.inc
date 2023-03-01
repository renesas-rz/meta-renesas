FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

LIC_FILES_CHKSUM = " \
        file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

BRANCH = "v2.7/rzg3s"
BRANCH_mbedtls = "mbedtls-2.28"

SRC_URI = " \
	git://github.com/renesas-rz/rzg_trusted-firmware-a.git;branch=${BRANCH};protocol=https \
	git://github.com/ARMmbed/mbedtls.git;branch=${BRANCH_mbedtls};name=mbedtls;destsuffix=mbedtls \
"

SRCREV = "63ac802d242b031887dcfa050cda6b0074b969b0"
SRCREV_mbedtls = "dd79db10014d85b26d11fe57218431f2e5ede6f2"

SRC_URI_append = " \
	file://0001-rzg3s-cpg-Add-SDHI2-initialization.patch \
	file://0002-rzg3s-Add-SMC-command-for-PCIe-RST_RSM_B-terminal-co.patch \
	file://0003-rzg3s-Add-SMC-command-for-USB-PWRRDY-terminal-contro.patch \
"

S = "${WORKDIR}/git"

PV = "v2.7+git"
