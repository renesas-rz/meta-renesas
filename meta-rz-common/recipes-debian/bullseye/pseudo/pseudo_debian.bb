# base recipe: meta/recipes-devtools/pseudo/pseudo_git.bb
# base branch: warrior
# base commit: bf363493fec990eaf7577769f1862d439404bd10

require ${COREBASE}/meta/recipes-devtools/pseudo/pseudo.inc

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://COPYING;md5=a1d8023a6f953ac6ea4af765ff62d574"

inherit debian-package
require recipes-common/recipes-debian/bullseye/sources/pseudo.inc
FILESPATH_append = ":${COREBASE}/meta/recipes-devtools/pseudo/files:${THISDIR}/pseudo"
DEPENDS += "python3-native"

SRC_URI += " \
	file://0001-configure-Prune-PIE-flags.patch \
	file://fallback-passwd \
	file://fallback-group \
"
