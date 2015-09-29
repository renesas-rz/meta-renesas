SRC_URI_append = " \
    file://Change-udevadm-settle-timeout-3-seconds-to-6-seconds-in-etc-init.d-udev.patch;apply=no \
"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

do_patch_append () {
    os.system("patch -p1 -d ${WORKDIR} -i ${WORKDIR}/Change-udevadm-settle-timeout-3-seconds-to-6-seconds-in-etc-init.d-udev.patch")
}
