# Basic packages
IMAGE_INSTALL_append = " \
    kernel-image \
    kernel-devicetree \
    bash \
    v4l-utils \
    v4l2-init \
    i2c-tools \
    coreutils \
"

update_issue() {
    # Set BSP version
    BSP_VERSION="3.0.5-update3"

    # Set SoC and Board info
    case "${MACHINE}" in
    smarc-rzg2l)
      BSP_SOC="RZG2L"
      BSP_BOARD="RZG2L-SMARC-EVK"
      ;;
    rzg2l-dev)
      BSP_SOC="RZG2L"
      BSP_BOARD="RZG2L-DEV"
      ;;
    smarc-rzg2lc)
      BSP_SOC="RZG2LC"
      BSP_BOARD="RZG2LC-SMARC-EVK"
      ;;
    rzg2lc-dev)
      BSP_SOC="RZG2LC"
      BSP_BOARD="RZG2LC-DEV"
      ;;
    smarc-rzg2ul)
      BSP_SOC="RZG2UL"
      BSP_BOARD="RZG2UL-SMARC-EVK"
      ;;
    rzg2ul-dev)
      BSP_SOC="RZG2UL"
      BSP_BOARD="RZG2UL-DEV"
      ;;
    smarc-rzv2l)
      BSP_SOC="RZV2L"
      BSP_BOARD="RZV2L-SMARC-EVK"
      ;;
    rzv2l-dev)
      BSP_SOC="RZV2L"
      BSP_BOARD="RZV2L-DEV"
      ;;
    smarc-rzfive)
      BSP_SOC="RZFive"
      BSP_BOARD="RZFive-SMARC-EVK"
      ;;
    rzfive-dev)
      BSP_SOC="RZFive"
      BSP_BOARD="RZFive-DEV"
      ;;
    rzv2m)
      BSP_SOC="RZV2M"
      BSP_BOARD="RZV2M Evaluation Board Kit"
      ;;
    rzv2ma)
      BSP_SOC="RZV2MA"
      BSP_BOARD="RZV2MA Evaluation Board Kit"
      ;;
    hihope-rzg2h)
      BSP_SOC="RZG2H"
      BSP_BOARD="HIHOPE-RZG2H"
      ;;
    hihope-rzg2m)
      BSP_SOC="RZG2M"
      BSP_BOARD="HIHOPE-RZG2M"
      ;;
    hihope-rzg2n)
      BSP_SOC="RZG2N"
      BSP_BOARD="HIHOPE-RZG2N"
      ;;
    ek874)
      BSP_SOC="RZG2E"
      BSP_BOARD="EK874"
      ;;
    iwg20m-g1m)
      BSP_SOC="RZG1M"
      BSP_BOARD="iWave RZ/G1M-PF Development Kit"
      ;;
    skrzg1m)
      BSP_SOC="RZG1M"
      BSP_BOARD="RZG1M-SK"
      ;;
    iwg20m-g1n)
      BSP_SOC="RZG1N"
      BSP_BOARD="iWave RZ/G1N-PF Development Kit"
      ;;
    iwg21m)
      BSP_SOC="RZG1H"
      BSP_BOARD="iWave RZ/G1H-PF Development Kit"
      ;;
    iwg22m)
      BSP_SOC="RZG1E"
      BSP_BOARD="iWave RZ/G1E-PF Development Kit"
      ;;
    skrzg1e)
      BSP_SOC="RZG1E"
      BSP_BOARD="RZG1E-SK"
      ;;
    iwg23s)
      BSP_SOC="RZG1C"
      BSP_BOARD="iWave RZ/G1C-PF Development Kit"
      ;;
    esac

    # Make issue file
    echo "BSP: ${BSP_SOC}/${BSP_BOARD}/${BSP_VERSION}" >> ${IMAGE_ROOTFS}/etc/issue
    echo "LSI: ${BSP_SOC}" >> ${IMAGE_ROOTFS}/etc/issue
    echo "Version: ${BSP_VERSION}" >> ${IMAGE_ROOTFS}/etc/issue
}
ROOTFS_POSTPROCESS_COMMAND += "update_issue; "

# Renesas Basic packages for 32bit
BASIC_32BIT_PKGS = " \
    lib32-coreutils \
    lib32-libstdc++ \
"

# Support secure environment
IMAGE_INSTALL_append = " \
    optee-client \
"

BASIC_32BIT_PKGS_append_rzg2h = " \
    lib32-optee-client \
"

# Installation for 32bit packages
IMAGE_INSTALL_append = " \
    ${@oe.utils.conditional("USE_32BIT_PKGS", "1", "${BASIC_32BIT_PKGS}", "", d)} \
"

# Qos user packages only supports 64bit.
QOS_USER_PKGS = ""
QOS_USER_PKGS_aarch64 = " \
    qosif-user-module \
    qosif-tp-user-module \
"

# Installation for QoS packages
IMAGE_INSTALL_append_rzg2h = " \
    kernel-module-qos \
    ${QOS_USER_PKGS} \
"

# Support Docker Engine
IMAGE_INSTALL_append = " \
    packagegroup-docker \
"

# Remove since RZG1 don't support LTTNG
IMAGE_INSTALL_remove_rzg1 = " \
  lttng-tools \
  lttng-modules \
  lttng-ust \
"

# Environment setup, support building kernel modules with kernel src in SDK
export KERNELSRC="$SDKTARGETSYSROOT/usr/src/kernel"
export KERNELDIR="$SDKTARGETSYSROOT/usr/src/kernel"
export HOST_EXTRACFLAGS="-I${OECORE_NATIVE_SYSROOT}/usr/include/ -L${OECORE_NATIVE_SYSROOT}/usr/lib"

# Default WKS is eMMC, except rzg2l devices which can support eSD boot
WKS_DEFAULT_FILE = "rz-image-bootpart-mmc.wks"
WKS_DEFAULT_FILE_rzg2l = "rz-image-bootpart-esd.wks"
WKS_DEFAULT_FILE_smarc-rzg2l = "rz-image-bootpart-esd-pmic.wks"

WKS_FILE ?= "${@oe.utils.conditional("WKS_SUPPORT", "1", "${WKS_DEFAULT_FILE}", "", d)}"

# Force remake wic image if its inputs were changed (WIC_INPUT_DEPENDS are defined in each machine conf)
# Note that environment variable WKS_FILE_DEPENDS can be used here, but it makes do_rootfs rerun as well
do_image_wic[depends] += "${WIC_INPUT_DEPENDS}"
