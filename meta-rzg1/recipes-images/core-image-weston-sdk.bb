require recipes-graphics/images/core-image-weston.bb
include core-image-weston.inc

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
		LD_LIBRARY_PATH_OLD=$LD_LIBRARY_PATH
		export LD_LIBRARY_PATH=$native_sysroot/usr/lib:$native_sysroot/lib/
		cd $native_sysroot/
		for exefile in bin/* sbin/* usr/bin/* usr/bin/*/* usr/libexec/arm-poky-linux-gnueabi/gcc/arm-poky-linux-gnueabi/*/*; do
			if [ -x "$exefile" ] && [ ! -L "$exefile" ] && [ ! "$exefile" = "usr/bin/patchelf" ]; then
				usr/bin/patchelf --set-rpath "$native_sysroot/lib:$native_sysroot/usr/lib" "$exefile" &>/dev/null
			fi
		done
		if [ ! -z $LD_LIBRARY_PATH_OLD ];then export LD_LIBRARY_PATH=$LD_LIBRARY_PATH_OLD;
		else unset LD_LIBRARY_PATH;fi
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

