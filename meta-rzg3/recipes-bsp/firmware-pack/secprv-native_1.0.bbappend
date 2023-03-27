FILESEXTRAPATHS_prepend := "${THISDIR}/${BPN}:"

SRC_URI_append = " \
	file://bl2_encsign_g3s_info.xml;subdir=manifest_generation_tool/info \
	file://bl2_sign_g3s_info.xml;subdir=manifest_generation_tool/info \
	file://flash_encsign_g3s_info.xml;subdir=manifest_generation_tool/info \
	"
