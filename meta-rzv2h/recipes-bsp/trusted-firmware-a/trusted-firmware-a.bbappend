require trusted-firmware-a.inc

COMPATIBLE_MACHINE_rzv2h = "(rzv2h-dev|rzv2h-evk-alpha|rzv2h-evk-ver1)"

PLATFORM_rzv2h = "v2h"
EXTRA_FLAGS_rzv2h-dev = "BOARD=dev_1 ENABLE_STACK_PROTECTOR=default"
EXTRA_FLAGS_rzv2h-evk-alpha = "BOARD=evk_alpha ENABLE_STACK_PROTECTOR=default"
EXTRA_FLAGS_rzv2h-evk-ver1 = "BOARD=evk_1 ENABLE_STACK_PROTECTOR=default"
