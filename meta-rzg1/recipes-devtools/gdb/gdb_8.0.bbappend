FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://gdb-Fix-ia64-defining-TRAP_HWBKPT-before-including-g.patch' if 'Buster' in '${CIP_MODE}' else ' '}"
