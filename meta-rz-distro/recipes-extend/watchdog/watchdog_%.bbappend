FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

# Enable watchdog service for all machines
# except RZ/V2H, RZ/V2N and RZ/G3E
SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_AUTO_ENABLE:rzv2h-evk = "disable"
SYSTEMD_AUTO_ENABLE:rzv2n-evk = "disable"
SYSTEMD_AUTO_ENABLE:smarc-rzg3e = "disable"
