FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "\
	file://0001-hw_get_random_bytes-SUPPORT.patch \
"

SRC_URI_append = " \
	file://0001-g3s-optee-os-build.patch \
"

COMPATIBLE_MACHINE_rzg3s = "(rzg3s-dev|smarc-rzg3s)"

PLATFORM_FLAVOR_rzg3s-dev = "g3s_dev14_1"
