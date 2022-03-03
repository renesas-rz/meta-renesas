# Basic packages
IMAGE_INSTALL_append = " \
    bash \
    v4l-utils \
    i2c-tools \
    coreutils \
"

IMAGE_FEATURES_remove = " ssh-server-dropbear"
IMAGE_FEATURES_append = " ssh-server-openssh"

update_issue() {
    # Set BSP version
    BSP_VERSION="1.3"

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
IMAGE_INSTALL_append_rzg2h = " \
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
QOS_USER_PKGS_aarch64-poky-linux = " \
    qosif-user-module \
    qosif-tp-user-module \
"

# Installation for QoS packages
IMAGE_INSTALL_append_rzg2h = " \
    kernel-module-qos \
    ${QOS_USER_PKGS} \
"

# Environment setup, support building kernel modules with kernel src in SDK
export KERNELSRC="$SDKTARGETSYSROOT/usr/src/kernel"
export KERNELDIR="$SDKTARGETSYSROOT/usr/src/kernel"
export HOST_EXTRACFLAGS="-I${OECORE_NATIVE_SYSROOT}/usr/include/ -L${OECORE_NATIVE_SYSROOT}/usr/lib"