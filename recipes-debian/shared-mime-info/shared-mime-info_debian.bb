require shared-mime-info.inc

inherit debian-package
require recipes-debian/sources/shared-mime-info.inc

SRC_URI += "file://parallelmake.patch \
	    file://install-data-hook.patch"
