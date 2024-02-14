require trusted-firmware-a.inc

COMPATIBLE_MACHINE_rzv2n = "(rzv2n-dev|rzv2n-evk)"

PLATFORM_rzv2n = "v2n"
EXTRA_FLAGS_rzv2n-dev = "BOARD=dev_1 ENABLE_STACK_PROTECTOR=default"
EXTRA_FLAGS_rzv2n-evk = "BOARD=evk_1 ENABLE_STACK_PROTECTOR=default"
