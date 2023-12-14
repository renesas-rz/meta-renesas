require include/rzg2h-optee-config.inc

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

ATFW_OPT_append += " RCAR_RPC_HYPERFLASH_LOCKED=0 "

ATFW_OPT_append += " \
    ${@oe.utils.conditional("ENABLE_SPD_OPTEE", "1", " SPD=opteed", "",d)} \
"

DEPENDS += " \
    ${@oe.utils.conditional("ENABLE_SPD_OPTEE", "1", " optee-os", "",d)} \
"

do_compile() {
    oe_runmake distclean
    oe_runmake bl2 bl31 rzg PLAT=${PLATFORM} ${ATFW_OPT}
}


do_deploy_append() {

    install -m 0644 ${S}/build/${PLATFORM}/release/bl2.srec ${DEPLOYDIR}/bl2-${MACHINE}.srec
    install -m 0644 ${S}/build/${PLATFORM}/release/bl31.srec ${DEPLOYDIR}/bl31-${MACHINE}.srec
    install -m 0644 ${S}/tools/renesas/rzg_layout_create/bootparam_sa0.srec ${DEPLOYDIR}/bootparam_sa0.srec
    install -m 0644 ${S}/tools/renesas/rzg_layout_create/bootparam_sa0.bin ${DEPLOYDIR}/bootparam_sa0.bin
    install -m 0644 ${S}/tools/renesas/rzg_layout_create/cert_header_sa6.srec ${DEPLOYDIR}/cert_header_sa6.srec
    install -m 0644 ${S}/tools/renesas/rzg_layout_create/cert_header_sa6.bin ${DEPLOYDIR}/cert_header_sa6.bin

}
