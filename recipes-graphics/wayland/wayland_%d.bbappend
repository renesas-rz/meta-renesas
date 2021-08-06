do_install_append() {
	# These files is provided in other recipes
	rm -rf ${D}/${libdir}/libwayland-egl*
	rm -rf ${D}/${libdir}/pkgconfig/wayland-egl*
}
