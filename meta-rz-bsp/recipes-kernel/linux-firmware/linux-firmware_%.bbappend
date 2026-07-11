COMPATIBLE_MACHINE = "(smarc-rzg3l)"
FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

CYPRESS_GIT_REPO = "git://github.com/murata-wireless/cyw-fmac-nvram.git;protocol=https;branch=master;name=cyw-fmac-nvram;destsuffix=cyw-fmac-nvram"

SRC_URI:append = " \
	${CYPRESS_GIT_REPO} \
"

SRCREV_cyw-fmac-nvram = "d0ddc35f8ade6ba5629c3a6d0a9c810078a9ebbc"

SRCREV_FORMAT = "default_cyw-fmac-nvram"

do_install:append() {
	install -d ${D}${nonarch_base_libdir}/firmware/cypress
	install -m 0644 ${WORKDIR}/cyw-fmac-nvram/cyfmac4373-sdio.2AE.txt \
		${D}${nonarch_base_libdir}/firmware/cypress/cyfmac4373-sdio.txt

	install -d ${D}${nonarch_base_libdir}/firmware/brcm
	cd ${D}${nonarch_base_libdir}/firmware/brcm

	ln -sf ../cypress/cyfmac4373-sdio.txt brcmfmac4373-sdio.txt
	ln -sf ../cypress/cyfmac4373-sdio.txt brcmfmac4373-sdio.renesas,r9a08g046l48-smarc.txt
}

FILES:${PN}-bcm4373:append = " \
	${nonarch_base_libdir}/firmware/cypress/cyfmac4373-sdio.txt \
	${nonarch_base_libdir}/firmware/brcm/brcmfmac4373-sdio.txt \
	${nonarch_base_libdir}/firmware/brcm/brcmfmac4373-sdio.renesas,r9a08g046l48-smarc.txt \
"
