# openssl-bin is required by new ca-certificates recipe
PACKAGES =+ "${PN}-bin"
FILES_${PN}-bin += "${bindir}/"

