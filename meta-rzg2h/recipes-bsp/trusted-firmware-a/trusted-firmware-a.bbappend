require include/rzg2h-security-config.inc

# For RZ/G2H/M/N/E
ATFW_OPT_r8a774c0 = "LSI=G2E RCAR_SA0_SIZE=0 RCAR_DRAM_DDR3L_MEMCONF=1 RCAR_DRAM_DDR3L_MEMDUAL=1 SPD="none""
ATFW_OPT_r8a774a1 = "LSI=G2M RCAR_DRAM_SPLIT=2 SPD="none""
ATFW_OPT_r8a774b1 = "LSI=G2N SPD="none""
ATFW_OPT_r8a774e1 = "LSI=G2H RCAR_DRAM_SPLIT=2 RCAR_DRAM_LPDDR4_MEMCONF=1 RCAR_DRAM_CHANNEL=5 SPD="none""

LOSSY_ENABLE ?= "1"
ATFW_OPT_LOSSY = "${@oe.utils.conditional("LOSSY_ENABLE", "1", "RCAR_LOSSY_ENABLE=1", "", d)}"

ATFW_OPT_append_r8a774c0 = "${@oe.utils.conditional("USE_ECC", "1", " LIFEC_DBSC_PROTECT_ENABLE=0 RZG_DRAM_ECC=1 ", "",d)}"
ATFW_OPT_append_r8a774a1 = "${@oe.utils.conditional("USE_ECC", "1", " LIFEC_DBSC_PROTECT_ENABLE=0 RCAR_DRAM_SPLIT=0 RZG_DRAM_ECC=1 ", " ${ATFW_OPT_LOSSY} ",d)}"
ATFW_OPT_append_r8a774b1 = "${@oe.utils.conditional("USE_ECC", "1", " LIFEC_DBSC_PROTECT_ENABLE=0 RZG_DRAM_ECC=1 ", " ${ATFW_OPT_LOSSY} ",d)}"
ATFW_OPT_append_r8a774e1 = "${@oe.utils.conditional("USE_ECC", "1", " LIFEC_DBSC_PROTECT_ENABLE=0 RCAR_DRAM_SPLIT=0 RZG_DRAM_ECC=1 ", " ${ATFW_OPT_LOSSY} ",d)}"

ATFW_OPT_append += " RZG_DRAM_ECC_FULL=${ECC_FULL} "

ATFW_OPT_append += " RCAR_RPC_HYPERFLASH_LOCKED=0 MBEDTLS_DIR=../mbedtls "

SRC_URI_append += " \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "file://0001-plat-rzg-add-support-SECURE-BOOT-for-RZ-G2-Platform.patch", "",d)} \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "file://0002-plat-rzg-add-the-security-tools-for-SECURE-BOOT.patch", "",d)} \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "file://0003-renesas-rpc-add-read-extern-mode-function.patch", "",d)} \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "file://0004-plat-rzg-add-support-SECURE-FIRMWARE-UPDATE.patch", "",d)} \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "file://0005-tools-rzg-change-Security-Module-address-in-boot-dev.patch", "",d)} \
"

ATFW_OPT_append += " \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "RCAR_SECURE_BOOT=1", "",d)} \
"

DEPENDS += " \
    ${@oe.utils.conditional("RZG2H_SECURITY_FEATURE", "ENABLE", "secprv-native secmod optee-ta-fwu ns-bl2u optee-os u-boot", "",d)} \
"

do_compile() {
    oe_runmake distclean
    oe_runmake bl2 bl31 rzg PLAT=${PLATFORM} ${ATFW_OPT}

    if [ "ENABLE" = "${RZG2H_SECURITY_FEATURE}" ] ; then
        oe_runmake -C tools/renesas/rzg_security_tools/fiptool clean
        oe_runmake -C tools/renesas/rzg_security_tools/fiptool

        oe_runmake -C tools/renesas/rzg_security_tools/sign_fw clean
        oe_runmake -C tools/renesas/rzg_security_tools/sign_fw

        oe_runmake -C tools/renesas/rzg_security_tools/encrypt_fw clean
        oe_runmake -C tools/renesas/rzg_security_tools/encrypt_fw
    fi
}


do_deploy_append() {
    install -m 0644 ${S}/build/${PLATFORM}/release/bl2.srec ${DEPLOYDIR}/bl2-${MACHINE}.srec
    install -m 0644 ${S}/build/${PLATFORM}/release/bl31.srec ${DEPLOYDIR}/bl31-${MACHINE}.srec
    install -m 0644 ${S}/tools/renesas/rzg_layout_create/bootparam_sa0.srec ${DEPLOYDIR}/bootparam_sa0.srec
    install -m 0644 ${S}/tools/renesas/rzg_layout_create/cert_header_sa6.srec ${DEPLOYDIR}/cert_header_sa6.srec

    if [ "ENABLE" = "${RZG2H_SECURITY_FEATURE}" ] ; then
        ./tools/renesas/rzg_security_tools/fiptool/fiptool_fw_ipl create --align 16 \
            --tb-fw-cert  ${S}/tools/renesas/rzg_layout_create/bootparam_sa0.bin \
            --soc-fw-cert ${S}/tools/renesas/rzg_layout_create/cert_header_sa6.bin \
            --tb-fw       ${DEPLOYDIR}/bl2-${MACHINE}.bin \
            --sec-mod     ${DEPLOY_DIR_IMAGE}/sec_module-${MACHINE}.bin \
            ./tools/renesas/rzg_security_tools/fiptool/fip_fw_ipl.bin

        ./tools/renesas/rzg_security_tools/fiptool/fiptool_keyring create --align 16 \
            --key-ring    ${SYMLINK_NATIVE_BOOT_KEY_DIR}/${FILE_BOOT_KEYRING_ENC} \
            ./tools/renesas/rzg_security_tools/fiptool/fip_keyring.bin

        temp_encrypt ${DEPLOYDIR}/bl31-${MACHINE}.bin ${DEPLOYDIR}/bl31-${MACHINE}_Enc.bin
        temp_encrypt ${DEPLOY_DIR_IMAGE}/u-boot-${MACHINE}.bin ${DEPLOYDIR}/u-boot-${MACHINE}_Enc.bin
        ./tools/renesas/rzg_security_tools/fiptool/fiptool_boot_fw create --align 16 \
            --soc-fw ${DEPLOYDIR}/bl31-${MACHINE}_Enc.bin   \
            --nt-fw  ${DEPLOYDIR}/u-boot-${MACHINE}_Enc.bin \
            ./tools/renesas/rzg_security_tools/fiptool/fip_boot_fw.bin

        if ${@bb.utils.contains('ATFW_OPT', 'SPD=\"opteed\"', 'true', 'false', d)}; then
            temp_encrypt ${DEPLOY_DIR_IMAGE}/tee-${MACHINE}.bin ${DEPLOYDIR}/tee-${MACHINE}_Enc.bin
            ./tools/renesas/rzg_security_tools/fiptool/fiptool_boot_fw update --align 16 \
                --tos-fw ${DEPLOYDIR}/tee-${MACHINE}_Enc.bin    \
                ./tools/renesas/rzg_security_tools/fiptool/fip_boot_fw.bin
        fi

        temp_encrypt ${DEPLOY_DIR_IMAGE}/ns_bl2u-${MACHINE}.bin ${DEPLOYDIR}/ns_bl2u-${MACHINE}_Enc.bin
        ./tools/renesas/rzg_security_tools/fiptool/fiptool_fwu_ns create --align 16 \
        --nt-fwu ${DEPLOYDIR}/ns_bl2u-${MACHINE}_Enc.bin \
        ./tools/renesas/rzg_security_tools/fiptool/fip_fwu_ns.bin

       ./tools/renesas/rzg_security_tools/fiptool/fiptool_fwu_ns update --align 16 \
            --plat-toc-flags ${FIP_FLAGS_END_OF_PACKAGE} ./tools/renesas/rzg_security_tools/fiptool/fip_fwu_ns.bin

        cat > ./tools/renesas/rzg_security_tools/fiptool/fip.bin
        cat ./tools/renesas/rzg_security_tools/fiptool/fip_fw_ipl.bin  >> ./tools/renesas/rzg_security_tools/fiptool/fip.bin
        cat ./tools/renesas/rzg_security_tools/fiptool/fip_keyring.bin >> ./tools/renesas/rzg_security_tools/fiptool/fip.bin
        cat ./tools/renesas/rzg_security_tools/fiptool/fip_boot_fw.bin >> ./tools/renesas/rzg_security_tools/fiptool/fip.bin
        cat ./tools/renesas/rzg_security_tools/fiptool/fip_fwu_ns.bin  >> ./tools/renesas/rzg_security_tools/fiptool/fip.bin

        install -m 0633 ./tools/renesas/rzg_security_tools/fiptool/fip.bin ${DEPLOYDIR}/fip-${MACHINE}.bin

        objcopy -I binary -O srec --adjust-vma=0x50000000 --srec-forceS3 \
            "${DEPLOYDIR}/fip-${MACHINE}.bin" "${DEPLOYDIR}/fip-${MACHINE}.mot"
    fi
}

temp_encrypt() {

    FILE_PATH_IN=${1}
    FILE_PATH_OUT=${2}
    FILE_PATH_SIG="./tools/renesas/rzg_security_tools/sign_fw/sign.bin"

    STR_EKEY_DATA=$(cat ${SYMLINK_NATIVE_BOOT_KEY_DIR}/${FILE_BOOTPRG_VERIFY_ENC_KEY} | xxd -p | tr -d '\n\r')
    STR_ENC_KEY="$(echo "${STR_EKEY_DATA}" | cut -c 1-32)"
    STR_ENC_IV0="$(echo "${STR_EKEY_DATA}" | cut -c 33-64)"
    FILE_PATH_SIG_KEY="${SYMLINK_NATIVE_BOOT_KEY_DIR}/${FILE_BOOTPRG_VERIFY_SIG_KEY}"

    ./tools/renesas/rzg_security_tools/sign_fw/sign_fw --key-alg rsa --hash-alg sha256 --align 16 \
        --key ${FILE_PATH_SIG_KEY} --in ${FILE_PATH_IN} --out ${FILE_PATH_SIG}

    ./tools/renesas/rzg_security_tools/encrypt_fw/encrypt_fw --key-alg cbc --nonce ${STR_ENC_IV0} \
        --key ${STR_ENC_KEY} --in ${FILE_PATH_SIG} --out ${FILE_PATH_OUT}
}
