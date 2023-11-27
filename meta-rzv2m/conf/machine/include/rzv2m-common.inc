require conf/machine/include/${SOC_FAMILY}.inc
require conf/machine/include/rzg2-common.inc

IMAGE_INSTALL_append = " \
	openssh \
	openssh-sshd \
	openssl-bin \
"

RZ_FEATURE_BOOTLOADER = "${@'True' if 'meta-rz-features/meta-rz-bootloaders' in '${BBLAYERS}' else 'False'}"
EXTRA_IMAGEDEPENDS += " ${@oe.utils.conditional('RZ_FEATURE_BOOTLOADER', 'True', ' bootloader', '', d)}"
