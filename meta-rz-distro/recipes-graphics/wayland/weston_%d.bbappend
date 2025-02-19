FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

SRC_URI:append = " \
	file://0001-Revert-gl-renderer-Don-t-use-TEXTURE_EXTERNAL-for-mu.patch \
"
