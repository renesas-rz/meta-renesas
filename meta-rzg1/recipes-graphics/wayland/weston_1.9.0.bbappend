FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append = " file://0001-protocol-Add-pkgconfig-file-to-be-referred-from-clie.patch \
                   file://0002-Weston-add-support-set-position-from-client.patch \
                   file://0003-Weston-add-support-set-scaling-from-client.patch \
                   file://0004-media-ctl-Separate-libmediactl-code-from-weston.patch \
                 "

do_install_append() {
    # install xml for client applications
    install -d ${D}/${datadir}/wayland-protocols/
    install -m 644 ${S}/protocol/linux-dmabuf.xml ${D}/${datadir}/wayland-protocols/
}
