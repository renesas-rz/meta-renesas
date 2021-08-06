SUMMARY = "A Mali GPU Linux Kernel module"
SECTION = "kernel/modules"
LICENSE = "GPLv2"

LIC_FILES_CHKSUM = " \ 
	file://license.txt;md5=13e14ae1bd7ad5bff731bba4a31bb510 "

PN = "kernel-module-mali"
PV = "r30"
PR = "p0"

SRC_URI = " \
	file://mali_km.tar.gz \
	"

inherit module
require include/rzg2-modules-common.inc

S = "${WORKDIR}/mali_km"

COMPATIBLE_MACHINE = "(r9a07g044l|r9a07g044c)"

do_fetch[file-checksums] = ""

MALI_KBASE_DIR = "drivers/gpu/arm/midgard"
EXTRA_OEMAKE = 'KDIR="${STAGING_KERNEL_DIR}" \
		ARCH="${ARCH}" \
		BUILD=release \
		CROSS_COMPILE="${CROSS_COMPILE}" \
		MALI_PLATFORM_NAME="devicetree" \
		CONFIG_MALI_MIDGARD=m \
		'
module_do_compile() {
	cd ${MALI_KBASE_DIR}
	oe_runmake
}

module_do_install() {
	install -d ${D}/lib/modules/${KERNEL_VERSION}/extra
	cd ${MALI_KBASE_DIR}
	install -m 644 mali_kbase.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/
	install -m 644 Module.symvers ${STAGING_KERNEL_BUILDDIR}/mali.symvers
}

FILES_${PN} = " \
	/lib/modules/${KERNEL_VERSION}/extra/mali_kbase.ko \
"

PACKAGES = "\
	${PN} \
"

RPROVIDES_${PN} += "kernel-module-mali"

KERNEL_MODULE_AUTOLOAD_append = "mali_kbase"
