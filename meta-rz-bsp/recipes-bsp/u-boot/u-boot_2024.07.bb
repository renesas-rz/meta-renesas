require u-boot-renesas.inc

COMPATIBLE_MACHINE = "(rzg3e-family|rzv2h-family|rzg2l-family|rzg3s-family|rzt2h-family|rzv2n-family)"

UBOOT_URI = "git://github.com/renesas-rz/renesas-u-boot-cip.git;protocol=https;nobranch=1"
UBOOT_REV:rzg3e-family = "deef73d62a080ba09180fefe3c8b8d08b050c076"
UBOOT_REV:rzv2h-family = "8e0b7870026f1c7debdc503435fa51bfa3ae7006"
UBOOT_REV:rzg2l-family = "4eebfbaa4e61f8d3fa0e44ae59449213ffee981c"
UBOOT_REV:rzg3s-family = "4eebfbaa4e61f8d3fa0e44ae59449213ffee981c"
UBOOT_REV:rzt2h-family = "b39b4cf21a79b8b02bdbe5633cc9d469f6f1cf00"
UBOOT_REV:rzv2n-family = "6e36246bf4dfb88b3d0cf08581bf5684a9797744"

PV="2024.07+git${SRCPV}"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=2ca5f2c35c8cc335f0a19756634782f1"

do_deploy:append:rzg2l-family() {
    if [ -n "${UBOOT_CONFIG}" ]
    then
        for config in ${UBOOT_MACHINE}; do
            i=$(expr $i + 1);
            for type in ${UBOOT_CONFIG}; do
                j=$(expr $j + 1);
                if [ $j -eq $i ]
                then
                    install -m 644 ${B}/${config}/${UBOOT_SREC} ${DEPLOYDIR}/u-boot-elf-${type}-${PV}-${PR}.${UBOOT_SREC_SUFFIX}
                    cd ${DEPLOYDIR}
                    ln -sf u-boot-elf-${type}-${PV}-${PR}.${UBOOT_SREC_SUFFIX} u-boot-elf-${type}.${UBOOT_SREC_SUFFIX}
                fi
            done
            unset j
        done
        unset i
    else
        install -m 644 ${B}/${UBOOT_SREC} ${DEPLOYDIR}/${UBOOT_SREC_IMAGE}
        cd ${DEPLOYDIR}
        rm -f ${UBOOT_SREC} ${UBOOT_SREC_SYMLINK}
        ln -sf ${UBOOT_SREC_IMAGE} ${UBOOT_SREC_SYMLINK}
        ln -sf ${UBOOT_SREC_IMAGE} ${UBOOT_SREC}
    fi
}
