PV = "5.6.3+git${SRCPV}"

RDEPENDS_${PN} += " mali-user-module"
RDEPENDS_${PN}-tools += " mali-user-module"
RDEPENDS_${PN}-examples += " mali-user-module"
RDEPENDS_${PN}-plugins += " mali-user-module libdrm"
