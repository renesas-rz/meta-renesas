require trusted-firmware-a.inc

COMPATIBLE_MACHINE_rzg3s = "(rzg3s-dev|smarc-rzg3s)"

PLATFORM_rzg3s-dev = "g3s"
EXTRA_FLAGS_rzg3s-dev = "BOARD=dev14_1_lpddr PLAT_SYSTEM_SUSPEND=vbat"

PLATFORM_smarc-rzg3s = "g3s"
EXTRA_FLAGS_smarc-rzg3s = "BOARD=smarc PLAT_SYSTEM_SUSPEND=vbat"
