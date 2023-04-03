FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/:"

SRC_URI += " \
	file://0001-systemd-networkd-wait-online.service-WA-remove-netwo.patch \
"
