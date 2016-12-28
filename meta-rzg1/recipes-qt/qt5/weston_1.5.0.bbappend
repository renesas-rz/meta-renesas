FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
	 file://0001-qt-event-notifier.patch \
	file://0001-workaround-hotplug.patch \
"