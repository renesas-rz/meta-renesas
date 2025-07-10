FILESEXTRAPATHS_prepend := "${THISDIR}/glibc:"

SRC_URI += " \
    file://0001-elf-Ignore-LD_LIBRARY_PATH-and-debug-env-var-for-set.patch \
    file://0002-elf-Test-case-for-bug-32976-CVE-2025-4802.patch \
"
