export BUILDDIR = "${STAGING_INCDIR}/.."
export INCSHARED = "${STAGING_INCDIR}"
export LIBSHARED = "${STAGING_LIBDIR}"
export KERNELSRC = "${STAGING_KERNEL_DIR}"
export CROSS_COMPILE = "${TARGET_PREFIX}"
export KERNELDIR = "${STAGING_KERNEL_DIR}"
export LDFLAGS = ""
export CP = "cp"
require include/rz-path-common.inc

# Fix error: openssl/bio.h: No such file or directory
do_make_scripts() {
unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
	make CC="${KERNEL_CC}" LD="${KERNEL_LD}" AR="${KERNEL_AR}" \
	           HOSTCC="${BUILD_CC} ${BUILD_CFLAGS} ${BUILD_LDFLAGS}" HOSTCPP="${BUILD_CPP}" \
           -C ${STAGING_KERNEL_DIR} O=${STAGING_KERNEL_BUILDDIR} scripts prepare
}

# Ensure one recipe isn't running do_make_scripts whilst another is using those
# scripts in do_compile.
do_compile[lockfiles] = "${TMPDIR}/kernel-scripts.lock"

do_make_scripts[depends] += "openssl-native:do_populate_sysroot"
