IMAGE_FSTYPES:append = " tar.gz wic.gz wic.bmap"
WKS_FILE ?= "rz-image-bootpart-mmc.wks"

SERIAL_CONSOLES = "115200;ttySC0"

IS_DOCKER_ENABLED ?= "0"

# Support Docker Engine
DISTRO_FEATURES:append = " \
	${@oe.utils.conditional("IS_DOCKER_ENABLED", "1", " virtualization", "",d)} \
	${@oe.utils.conditional("IS_DOCKER_ENABLED", "1", " docker", "",d)} \
"
IMAGE_INSTALL:append = " \
	${@oe.utils.conditional("IS_DOCKER_ENABLED", "1", " packagegroup-docker", " ",d)} \
"
