# egl/gles/gbm is provided in other recipe
PACKAGECONFIG_remove = "gbm gles egl libgl"

PACKAGES_remove = " \
	libgbm-dev libgbm \
	libegl-mesa-dev libegl-mesa \
	libegl-dev libegl \
	libgles2-mesa libgles2-mesa-dev \
	libgl \
"

#Mesa only need provide gbm header
INSTALLED_HEADER = "src/gbm/main/gbm.h"

do_configure[noexec] = ""
do_compile[noexec] = ""

do_install() {
	install -d ${D}/usr/include
	install -m 644 ${S}/${INSTALLED_HEADER} ${D}/usr/include/
}

FILES_{$PN} += " \
	${D}/usr/include/* \
"

INSANE_SKIP_${PN} = "installed-vs-shipped"
