#
# base recipe: meta/recipes-core/eglibc/eglibc.inc
# base branch: daisy
#

inherit debian-package
PV = "2.19"
DPN = "glibc"
SRCREV = "e2c178d0fc01a2909d14d3b64f2a285c06990310"

require glibc-ld.inc
require glibc-testing.inc

STAGINGCC = "gcc-cross-initial-${TARGET_ARCH}"
STAGINGCC_class-nativesdk = "gcc-crosssdk-initial-${SDK_SYS}"
PATH_prepend = "${STAGING_BINDIR_TOOLCHAIN}.${STAGINGCC}:"

# glibc can't be built without optimization, if someone tries to compile an
# entire image as -O0, add -Wno-error to make it buildable
python () {
    opt_effective = "-O"
    for opt in d.getVar('SELECTED_OPTIMIZATION').split():
        if opt in ("-O0", "-O", "-O1", "-O2", "-O3", "-Os"):
            opt_effective = opt
    if opt_effective == "-O0":
        bb.fatal("%s can't be built with %s, try -O1 instead" % (d.getVar('PN'), opt_effective))
    if opt_effective in ("-O", "-O1", "-Os"):
        bb.note("%s doesn't build cleanly with %s, adding -Wno-error to SELECTED_OPTIMIZATION" % (d.getVar('PN'), opt_effective))
        d.appendVar("SELECTED_OPTIMIZATION", " -Wno-error")
}

# siteconfig.bbclass runs configure which needs a working compiler
# For the compiler to work we need a working libc yet libc isn't
# in the sysroots directory at this point. This means the libc.so
# linker script won't work as the --sysroot setting isn't correct.
# Here we create a hacked up libc linker script and pass in the right
# flags to let configure work. Ugly.
EXTRASITECONFIG = "CFLAGS='${CFLAGS} -Wl,-L${WORKDIR}/site_config_libc -L${WORKDIR}/site_config_libc -L${SYSROOT_DESTDIR}${libdir} -L${SYSROOT_DESTDIR}${base_libdir} -Wl,-L${SYSROOT_DESTDIR}${libdir} -Wl,-L${SYSROOT_DESTDIR}${base_libdir}'"
siteconfig_do_siteconfig_gencache_prepend = " \
	mkdir -p ${WORKDIR}/site_config_libc; \
	cp ${SYSROOT_DESTDIR}${libdir}/libc.so ${WORKDIR}/site_config_libc; \
	sed -i -e 's# ${base_libdir}# ${SYSROOT_DESTDIR}${base_libdir}#g' -e 's# ${libdir}# ${SYSROOT_DESTDIR}${libdir}#g' ${WORKDIR}/site_config_libc/libc.so; \
"

# nptl needs unwind support in gcc, which can't be built without glibc.
DEPENDS = "virtual/${TARGET_PREFIX}gcc-initial libgcc-initial linux-libc-headers virtual/${TARGET_PREFIX}libc-initial"
# nptl needs libgcc but dlopens it, so our shlibs code doesn't detect this
#RDEPENDS_${PN} += "${@['','libgcc']['nptl' in '${GLIBC_ADDONS}']}"
RDEPENDS_${PN}-utils += "bash"
PROVIDES = "virtual/libc virtual/${TARGET_PREFIX}libc-for-gcc"
PROVIDES += "virtual/libintl virtual/libiconv"
inherit autotools
require glibc-options.inc

LEAD_SONAME = "libc.so"

CACHED_CONFIGUREVARS += " \
	ac_cv_path_BASH_SHELL=${base_bindir}/bash \
	libc_cv_slibdir=${base_libdir} \
	libc_cv_rootsbindir=${base_sbindir} \
	libc_cv_localedir=${localedir} \
	libc_cv_ssp=no \
"

GLIBC_EXTRA_OECONF ?= ""
GLIBC_EXTRA_OECONF_class-nativesdk = ""
INHIBIT_DEFAULT_DEPS = "1"

ARM_INSTRUCTION_SET = "arm"

# glibc uses PARALLELMFLAGS variable to pass parallel build info so transfer
# PARALLEL_MAKE into PARALLELMFLAGS and empty out PARALLEL_MAKE
EGLIBCPARALLELISM := "PARALLELMFLAGS="${PARALLEL_MAKE}""
EXTRA_OEMAKE[vardepsexclude] += "EGLIBCPARALLELISM"
EXTRA_OEMAKE += "${EGLIBCPARALLELISM}"
PARALLEL_MAKE = ""

# glibc make-syscalls.sh has a number of issues with /bin/dash and
# it's output which make calls via the SHELL also has issues, so 
# ensure make uses /bin/bash
EXTRA_OEMAKE += "SHELL=/bin/bash"

OE_FEATURES = "${@features_to_glibc_settings(d)}"
do_configure_prepend() {
	sed -e "s#@BASH@#/bin/sh#" -i ${S}/elf/ldd.bash.in
	echo '${OE_FEATURES}' > ${B}/option-groups.config
}

do_configure_append() {
	oe_runmake config

	# Remove quotation marks from OPTION_EGLIBC_NSSWITCH_FIXED_*. This will
	# avoid install error.
	sed -i 's/^OPTION_EGLIBC_NSSWITCH_FIXED_\(.*\)="\(.*\)"$/OPTION_EGLIBC_NSSWITCH_FIXED_\1=\2/' option-groups.config
}

GLIBC_ADDONS ?= "ports,nptl,libidn"
