FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI_append = " \
    file://audio.sh \
    file://COPYING.MIT \
"
S = "${WORKDIR}"

do_install() {
    install -d ${D}/${sysconfdir}/profile.d
    install -m 0755 ${WORKDIR}/audio.sh ${D}/${sysconfdir}/profile.d/audio.sh
}
do_configure[noexec] = "1"
do_patch[noexec] = "1"
do_compile[noexec] = "1"

FILES_${PN} = " \
    ${sysconfdir}/profile.d/audio.sh \
"
