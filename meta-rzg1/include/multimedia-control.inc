USE_MULTIMEDIA = "${@'1' if 'multimedia' in '${MACHINE_FEATURES}' else '0'}"
USE_MULTIMEDIA_TEST = "${@'1' if 'mm-test' in '${DISTRO_FEATURES}' and '${USE_MULTIMEDIA}'  == '1' else '0'}"
