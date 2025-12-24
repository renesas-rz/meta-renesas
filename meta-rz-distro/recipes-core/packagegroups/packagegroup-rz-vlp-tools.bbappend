# On RZ/G3L, remove kernel-module-uas since this board does not support USB3
# and UAS support is not enabled in the kernel.
RDEPENDS:packagegroup-rz-vlp-tools-base:remove:rzg3l-family = "kernel-module-uas"


