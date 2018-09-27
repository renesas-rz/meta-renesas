kernel_configure_variable() {
    # Remove the config
    CONF_SCRIPT="${S}/scripts/config --file ${B}/.config"
    if test "$2" = "n" ; then
        $CONF_SCRIPT --disable CONFIG_$1
    elif test "$2" = "m" ; then
        $CONF_SCRIPT --module CONFIG_$1
    elif test "$2" = "y" ; then
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

