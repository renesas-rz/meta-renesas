FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/:"

# Enable watchdog service for all machines
# except RZ/V2H, RZ/V2N, RZ/G3E and RZ/T2N
SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_AUTO_ENABLE:rzv2h-family = "disable"
SYSTEMD_AUTO_ENABLE:rzv2n-family = "disable"
SYSTEMD_AUTO_ENABLE:rzg3e-family = "disable"
SYSTEMD_AUTO_ENABLE:rzt2n-family = "disable"
