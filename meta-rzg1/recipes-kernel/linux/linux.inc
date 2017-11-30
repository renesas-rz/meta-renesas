DESCRIPTION = "Linux Kernel"
SECTION = "kernel"
LICENSE = "GPLv2"

LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

inherit kernel siteinfo

# Enable OABI compat for people stuck with obsolete userspace
ARM_KEEP_OABI ?= "1"

# Quirk for udev greater or equal 141
UDEV_GE_141 ?= "1"

# Set the verbosity of kernel messages during runtime
# You can define CMDLINE_DEBUG in your local.conf or distro.conf to override this behaviour
CMDLINE_DEBUG ?= '${@base_conditional("DISTRO_TYPE", "release", "quiet", "debug", d)}'
CMDLINE_append = " ${CMDLINE_DEBUG}"

kernel_configure_variable() {
    # Remove the config
    CONF_SCRIPT="${S}/scripts/config --file ${B}/.config"
    if test "$2" = "n" ; then
        $CONF_SCRIPT --disable CONFIG_$1
    elif test "$2" = "m" ; then
	$CONF_SCRIPT --module CONFIG_$1
    else
        $CONF_SCRIPT --enable CONFIG_$1
    fi
}

kernel_configure_variable_val() {
    # Remove the config
    CONF_SCRIPT="${S}/scripts/config --file ${B}/.config"
    $CONF_SCRIPT --set-val CONFIG_$1 $2
}

kernel_configure_variable_str() {
    # Remove the config
    CONF_SCRIPT="${S}/scripts/config --file ${B}/.config"
    $CONF_SCRIPT --set-str CONFIG_$1 "$2"
}
