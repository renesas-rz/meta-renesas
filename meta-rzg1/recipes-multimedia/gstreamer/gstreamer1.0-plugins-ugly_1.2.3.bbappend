SRC_URI_rzg1 = "gitsm://github.com/renesas-devel/gst-plugins-ugly.git;protocol=git;branch=RCAR-GEN2/1.2.3"
SRCREV_rzg1 = "af884db954b53bf083ebc39e3a90b639f81513e1"
S = "${WORKDIR}/git"

do_configure() {
    ./autogen.sh --noconfigure
    oe_runconf
}
