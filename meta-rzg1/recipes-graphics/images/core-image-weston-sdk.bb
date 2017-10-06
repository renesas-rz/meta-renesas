require recipes-graphics/images/core-image-weston.bb
include core-image-weston.inc

DESCRIPTION = " \
    Image with weston support that includes everything within \
    core-image-weston plus meta-toolchain, development headers and libraries to \
    form a standalone SDK. \
"

IMAGE_FEATURES += "dev-pkgs tools-sdk tools-debug debug-tweaks ssh-server-openssh"

IMAGE_INSTALL += "kernel-dev ltp"

# Allow compiling kernel-module
TOOLCHAIN_TARGET_TASK_append = " kernel-devsrc "

# Current cross-compile SDK already included kernel source. But to support
#    cross-compile kernel module, need to "make scripts" in that kernel source
#    to get neccesary tools. Below scripts do it automatically in SDK installer
fakeroot create_shar_append() {
	sed -i '/SDK has been successfully set up and is ready to be used/ i\
echo "configuring scripts of kernel source for building .ko file..."\
export OLD_PWD=-\
cd $target_sdk_dir/sysroots/cortexa*/usr/src/kernel\
$SUDO_EXEC bash -c "source $target_sdk_dir/environment-setup* && make silentoldconfig scripts"\
cd $OLD_PWD' ${SDK_DEPLOY}/${TOOLCHAIN_OUTPUTNAME}.sh
}

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
