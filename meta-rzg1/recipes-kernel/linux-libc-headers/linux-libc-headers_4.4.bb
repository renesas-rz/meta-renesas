require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

RENESAS_URL="git://github.com/renesas-rz/renesas-cip.git"
SRCREV = "b72f2f57d1e89f5532869198c530ce25808b207f"
SRC_URI = " \
	${RENESAS_URL};protocol=git;branch=v4.4.138-cip25 \
	file://0001-include-uapi-linux-if_pppox.h-include-linux-in.h-and.patch \
"

S = "${WORKDIR}/git"
