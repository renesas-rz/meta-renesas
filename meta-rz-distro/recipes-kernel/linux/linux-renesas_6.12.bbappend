FILESEXTRAPATHS:prepend := "${THISDIR}/files/:"

SRC_URI:append:rzg3l-family = " \
	${@bb.utils.contains('IMAGE_INSTALL', 'linux-firmware-bcm4373', 'file://bcm.cfg', '',d)} \
"
