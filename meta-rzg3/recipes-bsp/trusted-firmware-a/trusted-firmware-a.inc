FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

LIC_FILES_CHKSUM = " \
        file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde \
"

BRANCH_mbedtls = "mbedtls-2.28"

SRC_URI = " \
	git://github.com/renesas-rz/rzg_trusted-firmware-a.git;nobranch=1;protocol=https \
	git://github.com/ARMmbed/mbedtls.git;branch=${BRANCH_mbedtls};name=mbedtls;destsuffix=mbedtls \
"

SRCREV = "8835919b365956fa9bb63fbd8edfa97390d16307"
SRCREV_mbedtls = "dd79db10014d85b26d11fe57218431f2e5ede6f2"

S = "${WORKDIR}/git"

PV = "v2.7+git"
