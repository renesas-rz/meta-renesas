FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

# Enable watchdog service for all machines except RZ/V2H
SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_AUTO_ENABLE:rzv2h-evk = "disable"
