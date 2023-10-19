FILESEXTRAPATHS_append := "${THISDIR}/${PN}/:"

SRC_URI_append = " \
	file://watchdog.conf \
"
