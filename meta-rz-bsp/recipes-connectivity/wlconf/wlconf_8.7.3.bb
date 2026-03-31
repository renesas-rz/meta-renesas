DESCRIPTION = "Configuration utility for TI wireless drivers"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://README;beginline=1;endline=21;md5=adc05a1903d3f107f85c90328e3a9438"

# Tag: R8.7_SP3 (8.7.3)
SRCREV = "5048b59a444ac59ba7171d6e122d5a84581aebf2"
SRC_URI = "git://git.ti.com/wilink8-wlan/18xx-ti-utils.git;branch=master"

S = "${WORKDIR}/git/wlconf"

EXTRA_OEMAKE = "CC="${CC}""

do_install() {
    install -d ${D}${sbindir}/wlconf
    install -d ${D}${sbindir}/wlconf/official_inis
    install -d ${D}${libdir}/firmware/ti-connectivity

    # firmware
    install -m 0755 wl18xx-conf-default.bin ${D}${libdir}/firmware/ti-connectivity/wl18xx-conf.bin

    # wlconf binaries and configs
    install -m 0755 wlconf dictionary.txt struct.bin default.conf wl18xx-conf-default.bin \
                      README example.conf example.ini configure-device.sh \
                      ${D}${sbindir}/wlconf/

    # official inis
    install -m 0755 ${S}/official_inis/* ${D}${sbindir}/wlconf/official_inis/
}

FILES:${PN} += " \
       ${sbindir}/wlconf \
       ${sbindir}/wlconf/official_inis \
       ${libdir}/firmware/ti-connectivity/wl18xx-conf.bin \
"

FILES:${PN}-dbg += "${sbindir}/wlconf/.debug"
