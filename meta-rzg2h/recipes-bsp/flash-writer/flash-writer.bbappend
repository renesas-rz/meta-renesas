require include/rzg2h-security-config.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SEC_PRV_KEY_ENC = "${SYMLINK_NATIVE_PROV_KEY_DIR}/${FILE_PROVISIONING_KEY_ENC}"

SRC_URI_append = " \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "file://0001-Add-the-Provisioning-function-for-SECURE-BOOT.patch", "",d)} \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "file://0002-Add-the-Provisioning-function-for-SECURE-FIRMWARE-UPDATE.patch", "",d)} \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "file://0003-Fix-Provisioning-function-for-SECURE-BOOT.patch", "",d)} \
"

EXTRA_OEMAKE_append += " \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "SEC_PRV=ENABLE SEC_PRV_KEY_ENC=${SEC_PRV_KEY_ENC}", "",d)} \
"

DEPENDS += " \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "secprv-native", "",d)} \
"
