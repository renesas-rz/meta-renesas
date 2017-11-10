SRC_URI_append = " \
    file://keymap_input_file.patch \
    file://add_stdint.patch \
    file://Change-udevadm-settle-timeout-3-seconds-to-6-seconds-in-etc-init.d-udev.patch;apply=no \
    file://0001-udev-disable-udev-cache.patch;apply=no \
"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

do_patch_append () {
    os.system("patch -p1 -d ${WORKDIR} -i ${WORKDIR}/Change-udevadm-settle-timeout-3-seconds-to-6-seconds-in-etc-init.d-udev.patch")
    os.system("patch -p1 -d ${WORKDIR} -i ${WORKDIR}/0001-udev-disable-udev-cache.patch")
}
