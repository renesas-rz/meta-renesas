require recipes-graphics/images/core-image-weston.bb
include core-image-weston.inc
include core-image-weston-sdk.inc

inherit ${QT5_BASE_INHERIT}

DESCRIPTION = " \
    Image with weston support that includes everything within \
    core-image-weston plus meta-toolchain, development headers and libraries to \
    form a standalone SDK. \
"

IMAGE_FEATURES += "dev-pkgs tools-sdk \
        tools-debug eclipse-debug tools-profile tools-testapps debug-tweaks ssh-server-openssh"

# Add kernel source to allowing build kernel module
# Add libwayland-egl-dev to support building gles user library
#     since it requires header wayland-egl-priv.h in this package
TOOLCHAIN_TARGET_TASK_append = " kernel-devsrc libwayland-egl-dev eudev-dev \
                                 s3ctl-user-module-dev vspm-user-module-dev \
                                 fdpm-user-module-dev alsa-lib-dev \
                                 libusb1-dev pciutils-dev"

# Add some necessary tool
TOOLCHAIN_HOST_TASK_append = " nativesdk-bison nativesdk-flex nativesdk-patchelf"

# Add below environments variables to support cross-compile kernel module
toolchain_create_sdk_env_script_append() {
	echo "export KERNELSRC=$sysroot/usr/src/kernel" >> $script
	echo "export KERNELDIR=$sysroot/usr/src/kernel" >> $script
}

# Add below modules to support self-compile for GStreamer app
IMAGE_INSTALL_append = " \
	gstreamer1.0-plugins-base-app \
	gstreamer1.0-rtsp-server \
"

### For cross-compile Qt ###
TOOLCHAIN_HOST_TASK_append = '${@base_conditional("ENABLE_QT_FRAMEWORK", "1", \
    " nativesdk-qtbase-tools", "", d)} \
'

### For self-compile Qt ###
IMAGE_INSTALL_append = '${@base_conditional("ENABLE_QT_FRAMEWORK", "1", \
    " packagegroup-qt5-toolchain-target ", "", d)} \
'

# Set up environment variables for self-compiling
setup_qt_env () {
	if [ ! -e ${IMAGE_ROOTFS}${sysconfdir}/profile.d/setup_qt_env ]
	then
		echo 'export PATH=$PATH:/usr/bin/qt5' > ${IMAGE_ROOTFS}${sysconfdir}/profile.d/setup_qt_env
		echo 'export INCLUDEPATH=$INCLUDEPATH:/usr/include/qt5' >> ${IMAGE_ROOTFS}${sysconfdir}/profile.d/setup_qt_env
	fi
}
ROOTFS_POSTPROCESS_COMMAND_append = '${@base_conditional("ENABLE_QT_FRAMEWORK", "1", \
    " setup_qt_env;", "", d)} \
'

# qt multimedia needs alsa-dev when self-compiling
IMAGE_INSTALL_append = " alsa-dev "

# weston drm-backend need xkeyboard-config
IMAGE_INSTALL_append = " xkeyboard-config "

