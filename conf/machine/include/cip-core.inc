DEBIAN_BASED = "${@bb.utils.contains('CIP_CORE', '1', 'debian', 'non_debian', d)}"
#DEBIAN_BASED = "non_debian" 
OVERRIDES .= ":${DEBIAN_BASED}"

BBMASK_non_debian += " recipes-debian"

BBMASK_debian += " perl_debian"

# Select gcc,gdb, python3 debian version
GCCVERSION_debian = "8.3.0"
SDKGCCVERSION_debian = "${GCCVERSION}"

GLIBCVERSION_debian = "2.28%"
PREFERRED_VERSION_glibc_debian = "${GLIBCVERSION}"
PREFERRED_VERSION_nativesdk-glibc_debian = "${GLIBCVERSION}"
PREFERRED_VERSION_nativesdk-glibc-locale_debian = "${GLIBCVERSION}" 

BINUVERSION_debian = "2.31.%"
PREFERRED_VERSION_nativesdk-binutils_debian = "${BINUVERSION}"

PREFERRED_VERSION_gdb_debian = "8.1"

PREFERRED_VERSION_busybox_debian = "1.31.%"

RDEPENDS_xz_append_debian = "bash"
RDEPENDS_gzip_append_debian = "bash"
RDEPENDS_adduser_append_debian = "perl"

