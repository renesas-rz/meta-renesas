FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append = " file://0001-protocol-Add-pkgconfig-file-to-be-referred-from-clie.patch"

do_install_append() {
    # install xml for client applications
    install -d ${D}/${datadir}/wayland-protocols/
    install -m 644 ${S}/protocol/linux-dmabuf.xml ${D}/${datadir}/wayland-protocols/
}
