do_install:append () {
	sed -i '/iface wlan0 inet dhcp/i auto wlan0' ${D}/${sysconfdir}/network/interfaces
}
