COMPATIBLE_MACHINE = "(smarc-rzg3l)"
FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

FW_VERSION = "20240909"
LINUX_FW_REPO = "${KERNELORG_MIRROR}/linux/kernel/firmware/${BPN}-${FW_VERSION}.tar.xz;name=linux-firmware-${FW_VERSION};destsuffix=linux-firmware-${FW_VERSION}"
CYPRESS_GIT_REPO = "git://github.com/murata-wireless/cyw-fmac-nvram.git;protocol=https;branch=master;name=cyw-fmac-nvram;destsuffix=cyw-fmac-nvram"

SRC_URI:append = " \
	${LINUX_FW_REPO} \
	${CYPRESS_GIT_REPO} \
"

SRCREV_FORMAT = "linux-firmware"
SRCREV_cyw-fmac-nvram = "d0ddc35f8ade6ba5629c3a6d0a9c810078a9ebbc"
SRC_URI[linux-firmware-20240909.sha256sum] = "943fbd19883cf8eadf89e0b22422549db056557b1ecd30a56400615971369671"

do_install:append() {
	install -d ${D}/${nonarch_base_libdir}/firmware/cypress
	install -m 0644 ${WORKDIR}/linux-firmware-${FW_VERSION}/cypress/cyfmac4373-sdio.bin ${D}/${nonarch_base_libdir}/firmware/cypress/cyfmac4373-sdio.bin
	install -m 0644 ${WORKDIR}/linux-firmware-${FW_VERSION}/cypress/cyfmac4373-sdio.clm_blob ${D}/${nonarch_base_libdir}/firmware/cypress/cyfmac4373-sdio.clm_blob
	install -m 0644 ${WORKDIR}/cyw-fmac-nvram/cyfmac4373-sdio.2AE.txt ${D}/${nonarch_base_libdir}/firmware/cypress/cyfmac4373-sdio.txt

	install -d ${D}/${nonarch_base_libdir}/firmware/brcm
	cd ${D}/${nonarch_base_libdir}/firmware/brcm

	ln -sf ../cypress/cyfmac4373-sdio.bin brcmfmac4373-sdio.bin
	ln -sf ../cypress/cyfmac4373-sdio.clm_blob brcmfmac4373-sdio.clm_blob
	ln -sf ../cypress/cyfmac4373-sdio.txt brcmfmac4373-sdio.txt

	ln -sf ../cypress/cyfmac4373-sdio.bin brcmfmac4373-sdio.renesas,r9a08g046l48-smarc.bin
	ln -sf ../cypress/cyfmac4373-sdio.clm_blob brcmfmac4373-sdio.renesas,r9a08g046l48-smarc.clm_blob
	ln -sf ../cypress/cyfmac4373-sdio.txt brcmfmac4373-sdio.renesas,r9a08g046l48-smarc.txt
}

FILES:${PN}-bcm4373:append = " \
	${nonarch_base_libdir}/firmware/cypress/cyfmac4373-sdio.bin \
	${nonarch_base_libdir}/firmware/cypress/cyfmac4373-sdio.clm_blob \
	${nonarch_base_libdir}/firmware/cypress/cyfmac4373-sdio.txt \
	${nonarch_base_libdir}/firmware/brcm/brcmfmac4373-sdio.bin \
	${nonarch_base_libdir}/firmware/brcm/brcmfmac4373-sdio.clm_blob \
	${nonarch_base_libdir}/firmware/brcm/brcmfmac4373-sdio.txt \
	${nonarch_base_libdir}/firmware/brcm/brcmfmac4373-sdio.renesas,r9a08g046l48-smarc.bin \
	${nonarch_base_libdir}/firmware/brcm/brcmfmac4373-sdio.renesas,r9a08g046l48-smarc.clm_blob \
	${nonarch_base_libdir}/firmware/brcm/brcmfmac4373-sdio.renesas,r9a08g046l48-smarc.txt \
"
