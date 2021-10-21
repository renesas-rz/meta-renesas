do_install_append() {
	if [ "${EXT_GFX_BACKEND}" = "1" ]; then
		# These files are provided in other recipes
		rm -rf ${D}/${libdir}/libwayland-egl*
		rm -rf ${D}/${libdir}/pkgconfig/wayland-egl*
	fi
}
