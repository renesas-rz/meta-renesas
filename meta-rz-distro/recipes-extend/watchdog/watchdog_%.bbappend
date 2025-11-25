FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

# Enable watchdog service for all machines except RZ/V2H and RZ/V2N
SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_AUTO_ENABLE:rzv2h-evk = "disable"
SYSTEMD_AUTO_ENABLE:rzv2n-evk = "disable"
