# base recipe: meta/recipes-graphics/xorg-lib/libxshmfence_1.3.bb
# base branch: warrior
# base commit: 36166dbade7ef35ef656068425d3bde6607ab9c5

SUMMARY = "Shared memory 'SyncFence' synchronization primitive"

DESCRIPTION = "This library offers a CPU-based synchronization primitive compatible \
with the X SyncFence objects that can be shared between processes \
using file descriptor passing."

require ${COREBASE}/meta/recipes-graphics/xorg-lib/xorg-lib-common.inc
# clear SRC_URI
SRC_URI = ""
inherit debian-package-buster
require sources/libxshmfence.inc
DEBIAN_PATCH_TYPE = "nopatch"
DEBIAN_UNPACK_DIR = "${WORKDIR}/${XORG_PN}-${PV}"

LICENSE = "MIT-style"
LIC_FILES_CHKSUM = "file://COPYING;md5=47e508ca280fde97906eacb77892c3ac"

#do_debian_verify_version[noexec] = "1"
#do_debian_patch[noexec] = "1"

DEPENDS += "virtual/libx11"

BBCLASSEXTEND = "native nativesdk"
