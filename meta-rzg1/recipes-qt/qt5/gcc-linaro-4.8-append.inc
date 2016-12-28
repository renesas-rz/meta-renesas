FILESEXTRAPATHS_prepend := "${THISDIR}/gcc-linaro-${BASEPV}:"

# apply patches
SRC_URI_append = " \
	   file://0001-Backport-r205087-to-fix-linaro-Bug307.patch \
	  "

