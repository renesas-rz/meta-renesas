# Fix error due to conflict version of header in multilib
inherit multilib_header
do_install_append() {
	oe_multilib_header gmp.h
}
