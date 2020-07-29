FILESEXTRAPATHS_prepend := "${THISDIR}/sysvinit:"

SRC_URI += "${@'file://0001-include-sys-sysmacros.h-for-major-minor-defines-in-g.patch' \
	    if 'Buster' in '${MACHINE_FEATURES}' else ' '}"
