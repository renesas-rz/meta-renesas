PACKAGES:append = ' \
	${@bb.utils.contains("MACHINE_FEATURES", "can", "packagegroup-base-can", "",d)} \
	'

RDEPENDS:packagegroup-base:append = "\
	${@bb.utils.contains('COMBINED_FEATURES', 'can', 'packagegroup-base-can', '',d)} \
	"

RDEPENDS:packagegroup-base-alsa:append = "\
	alsa-utils"

RDEPENDS:packagegroup-base-ext2:append = "\
	e2fsprogs-e2scrub \
	e2fsprogs-resize2fs \
	e2fsprogs-tune2fs"

SUMMARY:packagegroup-base-can = "CAN network support"
RDEPENDS:packagegroup-base-can = "\
	can-utils"

