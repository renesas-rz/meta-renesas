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

create_sdk_files_append () {
	# Setup site file for external use
	toolchain_create_sdk_siteconfig ${SDK_OUTPUT}/${SDKPATH}/site-config-${REAL_MULTIMACH_TARGET_SYS}

	toolchain_create_sdk_env_script ${SDK_OUTPUT}/${SDKPATH}/environment-setup-${REAL_MULTIMACH_TARGET_SYS}

	# Add version information
	toolchain_create_sdk_version ${SDK_OUTPUT}/${SDKPATH}/version-${REAL_MULTIMACH_TARGET_SYS}

	echo "export PATH=${SDKPATHNATIVE}/usr/bin/qt5:\$PATH" >> $script
	echo 'export OE_QMAKE_COMPILER="arm-poky-linux-gnueabi-gcc -march=armv7-a -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a7 --sysroot=$SDKTARGETSYSROOT"' >> $script
	echo 'export OE_QMAKE_CC="arm-poky-linux-gnueabi-gcc -march=armv7-a -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a7 --sysroot=$SDKTARGETSYSROOT"' >> $script
	echo 'export OE_QMAKE_CXX="arm-poky-linux-gnueabi-g++ -march=armv7-a -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a7 --sysroot=$SDKTARGETSYSROOT"' >> $script
	echo 'export OE_QMAKE_CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types"' >> $script
	echo 'export OE_QMAKE_CXXFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -fvisibility-inlines-hidden"' >> $script
	echo 'export OE_QMAKE_LINK="arm-poky-linux-gnueabi-g++ -march=armv7-a -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a7 --sysroot=$SDKTARGETSYSROOT"' >> $script
	echo 'export OE_QMAKE_LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed"' >> $script
	echo 'export OE_QMAKE_AR="arm-poky-linux-gnueabi-ar"' >> $script
	echo 'export OE_QMAKE_STRIP="echo"' >> $script
	echo 'export OE_QMAKE_INCDIR_QT="$SDKTARGETSYSROOT/usr/include/qt5"' >> $script
	echo 'export OE_QMAKE_WAYLAND_SCANNER="${SDKPATHNATIVE}/usr/bin/wayland-scanner"' >> $script
}

# This allow reuse of Qt paths
inherit qmake5_paths

create_sdk_files_prepend () {
	# make a symbolic link to mkspecs for compatibility with QTCreator
	(cd ${SDK_OUTPUT}/${SDKPATHNATIVE}; \
	    ln -sf ${SDKTARGETSYSROOT}${libdir}/${QT_DIR_NAME}/mkspecs mkspecs;)

	# Generate oe-device-extra.pri
	oe_device_extra_pri=${SDK_OUTPUT}/${SDKTARGETSYSROOT}${libdir}/${QT_DIR_NAME}/mkspecs/oe-device-extra.pri
	touch $oe_device_extra_pri

	# Generate a qt.conf file to be deployed with the SDK
	qtconf=${SDK_OUTPUT}/${SDKPATHNATIVE}${OE_QMAKE_PATH_HOST_BINS}/qt.conf
	touch $qtconf
	echo '[Paths]' >> $qtconf
	echo 'Prefix = ${SDKTARGETSYSROOT}' >> $qtconf
	echo 'Headers = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QT_HEADERS}' >> $qtconf
	echo 'Libraries = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_LIBS}' >> $qtconf
	echo 'ArchData = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QT_ARCHDATA}' >> $qtconf
	echo 'Data = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QT_DATA}' >> $qtconf
	echo 'Binaries = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QT_BINS}' >> $qtconf
	echo 'LibraryExecutables = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_LIBEXECS}' >> $qtconf
	echo 'Plugins = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_PLUGINS}' >> $qtconf
	echo 'Imports = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_IMPORTS}' >> $qtconf
	echo 'Qml2Imports = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QML}' >> $qtconf
	echo 'Translations = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QT_TRANSLATIONS}' >> $qtconf
	echo 'Documentation = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QT_DOCS}' >> $qtconf
	echo 'Settings = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QT_SETTINGS}' >> $qtconf
	echo 'Examples = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QT_EXAMPLES}' >> $qtconf
	echo 'Tests = ${SDKTARGETSYSROOT}${OE_QMAKE_PATH_QT_TESTS}' >> $qtconf
	echo 'HostPrefix = ${SDKPATHNATIVE}' >> $qtconf
	echo 'HostBinaries = ${SDKPATHNATIVE}${OE_QMAKE_PATH_HOST_BINS}' >> $qtconf
}

IMAGE_INSTALL_append = " qtmultimedia qtconnectivity qtwebchannel qtwebkit qtwebsockets qtwayland qtserialport "
TOOLCHAIN_HOST_TASK_append = " nativesdk-qtbase-tools nativesdk-packagegroup-qt5-toolchain-host"

### For self-compile ###
IMAGE_INSTALL_append = " packagegroup-qt5-toolchain-target "

# Set up environment variables for self-compileing
setup_qt_env () {
	if [ ! -e ${IMAGE_ROOTFS}${sysconfdir}/profile.d/setup_qt_env ]
	then
		echo 'export PATH=$PATH:/usr/bin/qt5' > ${IMAGE_ROOTFS}${sysconfdir}/profile.d/setup_qt_env
		echo 'export INCLUDEPATH=$INCLUDEPATH:/usr/include/qt5' >> ${IMAGE_ROOTFS}${sysconfdir}/profile.d/setup_qt_env
	fi
}
ROOTFS_POSTPROCESS_COMMAND_append = " setup_qt_env"

# qt multimedia needs alsa-dev when self-compiling
IMAGE_INSTALL_append = " alsa-dev "

# weston drm-backend need xkeyboard-config
IMAGE_INSTALL_append = " xkeyboard-config "

