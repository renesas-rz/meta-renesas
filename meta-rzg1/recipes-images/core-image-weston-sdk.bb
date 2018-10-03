require recipes-graphics/images/core-image-weston.bb
include core-image-weston.inc

inherit populate_sdk_qt5_base

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


# Some post process after installed sdk:
#    1) Update rpath to prevent missing library problem (may happens in current SDK)
#    2) Set up kernel source to allow building kernel module
sdk_post_process () {
	# Work around: current SDK may have a problem in rpath of each executable files
	# Use patchelf to fix the rpath in it happens
	$SUDO_EXEC bash -c 'source "$0" && cd "${OECORE_NATIVE_SYSROOT}/usr/bin/" && if [ -f "patchelf" ];then patchelf -h  &> /dev/null;fi' $env_setup_script
	if [ $? != '0' ];then
		echo "workaround: fix rpath of executable files under native sysroot"
		native_sysroot=$($SUDO_EXEC cat $env_setup_script |grep 'OECORE_NATIVE_SYSROOT='|cut -d'=' -f2|tr -d '"')
		$SUDO_EXEC bash -c '
			sysroot=$0
			export LD_LIBRARY_PATH=$sysroot/usr/lib:$sysroot/lib/;
			cd $sysroot/
			for xfile in bin/* sbin/* usr/bin/* usr/bin/*/* usr/libexec/arm-poky-linux-gnueabi/gcc/arm-poky-linux-gnueabi/*/*
			do
				if [ -x "$xfile" ] && [ ! -L "$xfile" ] && [ ! "$xfile" = "usr/bin/patchelf" ]; then
					usr/bin/patchelf --set-rpath "$sysroot/lib:$sysroot/usr/lib" "$xfile" &>/dev/null
				fi
			done' $native_sysroot
	fi

	# Set up kernel for building kernel config now
	echo "configuring scripts of kernel source for building .ko file..."
	$SUDO_EXEC bash -c 'source "$0" && cd "${OECORE_TARGET_SYSROOT=}/usr/src/kernel" && make silentoldconfig scripts' $env_setup_script
}
SDK_POST_INSTALL_COMMAND_append = " ${sdk_post_process}"

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

