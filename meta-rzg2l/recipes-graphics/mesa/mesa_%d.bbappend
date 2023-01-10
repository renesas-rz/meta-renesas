#These packages will be provided by external graphics library
PACKAGECONFIG_remove = " ${@oe.utils.conditional('EXT_GFX_BACKEND', '1', 'egl gles',' ',d)}"

#Mesa only need provide gbm header
INSTALLED_HEADER = "src/gbm/main/gbm.h"

do_install_append() {
        install -d ${D}/usr/include
        install -m 644 ${S}/${INSTALLED_HEADER} ${D}/usr/include/
        if [ "${EXT_GFX_BACKEND}" = "1" ]; then
                #These header files will be provied by external graphics library
                rm -rf ${D}/${libdir}/libgbm.so*
                rm -rf ${D}/${libdir}/pkgconfig/gbm.pc
                rm -rf ${D}/usr/include/KHR
        fi
}

FILES_{$PN} += " \
	${D}/usr/include/* \
"

INSANE_SKIP_${PN} = "installed-vs-shipped"
