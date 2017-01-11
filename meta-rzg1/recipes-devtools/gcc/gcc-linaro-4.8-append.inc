FILESEXTRAPATHS_prepend := "${THISDIR}/gcc-linaro-${BASEPV}:"

SRC_URI_prepend = " https://releases.linaro.org/archive/${MMYY}/components/toolchain/gcc-linaro/${BASEPV}/gcc-${PV}-${RELEASE}.tar.xz "

# apply patches
SRC_URI_append = " \
	   file://0001-Backport-r205087-to-fix-linaro-Bug307.patch \
"
