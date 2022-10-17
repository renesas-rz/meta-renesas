include core-image-weston.inc

update_issue() {
    # Set BSP version
    BSP_VERSION="2.1.16"

    # Set SoC and Board info
    case "${MACHINE}" in
    iwg21m)
      BSP_SOC="RZG1H"
      BSP_BOARD="iWave"
      ;;
    iwg22m)
      BSP_SOC="RZG1E"
      BSP_BOARD="iWave"
      ;;
    iwg23s)
      BSP_SOC="RZG1C"
      BSP_BOARD="iWave"
      ;;
    skrzg1e)
      BSP_SOC="RZG1E"
      BSP_BOARD="RZG1E-SK"
      ;;
    skrzg1m)
      BSP_SOC="RZG1M"
      BSP_BOARD="RZG1M-SK"
      ;;
    iwg20m-g1m)
      BSP_SOC="RZG1M"
      BSP_BOARD="iWave"
      ;;
    iwg20m-g1n)
      BSP_SOC="RZG1N"
      BSP_BOARD="iWave"
      ;;
    esac

    # Make issue file
    echo "BSP: ${BSP_SOC}/${BSP_BOARD}/${BSP_VERSION}" > ${IMAGE_ROOTFS}/etc/issue
    echo "LSI: ${BSP_SOC}" >> ${IMAGE_ROOTFS}/etc/issue
    echo "Version: ${BSP_VERSION}" >> ${IMAGE_ROOTFS}/etc/issue
}
ROOTFS_POSTPROCESS_COMMAND += "update_issue; "
