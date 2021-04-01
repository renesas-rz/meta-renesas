do_install_append_class-native() {
	ln -fs python3-native/python3 ${D}${bindir}/python
}
