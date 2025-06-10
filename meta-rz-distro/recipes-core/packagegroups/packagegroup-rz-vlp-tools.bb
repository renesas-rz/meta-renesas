SUMMARY = "Merge machine and distro options for packages for RZ VLP"

#
# packages which content depend on MACHINE_FEATURES need to be MACHINE_ARCH
#
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

PACKAGES = " \
	packagegroup-rz-vlp-tools \
	packagegroup-rz-vlp-tools-base \
	packagegroup-rz-vlp-tools-multimedia \
	packagegroup-rz-vlp-tools-benchmark \
"

RDEPENDS:packagegroup-rz-vlp-tools = " \
	packagegroup-rz-vlp-tools-base \
	packagegroup-rz-vlp-tools-multimedia \
	packagegroup-rz-vlp-tools-benchmark \
"

RDEPENDS:packagegroup-rz-vlp-tools-base = " \
	packagegroup-base \
	busybox \
	ckermit \
	dosfstools \
	ethtool \
	i2c-tools \
	minicom \
	mtd-utils \
	tcf-agent \
	watchdog \
	"

RDEPENDS:packagegroup-rz-vlp-tools-multimedia = " \
	kernel-module-uvcvideo \
	libdrm \
 	libdrm-tests \
	v4l-utils \
	audio-init \
	v4l2-init \
 	yavta \
	"

RDEPENDS:packagegroup-rz-vlp-tools-benchmark = " \
	bonnie++ \
	iperf3 \
	memtester \
	"
