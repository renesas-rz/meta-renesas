#Workaround: Fix build error due to confict with glibc
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "${@'file://0050-misc-create_inode.c-Fix-conflict-copy_file_range.patch' if 'Buster' in '${MACHINE_FEATURES}' else ' '}"
