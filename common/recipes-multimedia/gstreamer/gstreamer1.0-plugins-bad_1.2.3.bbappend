DEPENDS += "libxml2 libuiomux libshvio"

TARGET_CFLAGS += "-D_GNU_SOURCE"

PACKAGECONFIG := "${@'${PACKAGECONFIG}'.replace('curl', '')}"
PACKAGECONFIG := "${@'${PACKAGECONFIG}'.replace('eglgles', '')}"
PACKAGECONFIG += "directfb"

EXTRA_OECONF += "--enable-experimental --disable-nls"
