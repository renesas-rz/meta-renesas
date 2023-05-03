require conf/machine/include/${SOC_FAMILY}.inc
require conf/machine/include/rzg2-common.inc

IMAGE_INSTALL_remove = " kernel-module-uvcvideo "

IMAGE_INSTALL_append = " \
	openssh \
	openssh-sshd \
	openssl-bin \
"
