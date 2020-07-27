# Don't depend on alsa-plugins-pulseaudio-conf.
# It is removed to prevent conflict between alsa and pulseaudio
RDEPENDS_pulseaudio-server_remove = "alsa-plugins-pulseaudio-conf"

#Fix build error with glibc due to memfd_create (added from version 2.27)
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += "${@'file://0001-memfd-wrappers-only-define-memfd_create-if-not-alrea.patch' if 'Buster' in '${MACHINE_FEATURES}' else ' '}"
