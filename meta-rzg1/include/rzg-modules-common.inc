export BUILDDIR = "${STAGING_INCDIR}/.."
export LIBSHARED = "${STAGING_LIBDIR}"
export KERNELSRC = "${STAGING_KERNEL_DIR}"
export CROSS_COMPILE = "${TARGET_PREFIX}"
export KERNELDIR = "${STAGING_KERNEL_DIR}"
export LDFLAGS = ""
export CP = "cp"

inherit module

# Ensure one recipe isn't running do_make_scripts whilst another is using those
# scripts in do_compile.
do_compile[lockfiles] = "${TMPDIR}/kernel-scripts.lock"
