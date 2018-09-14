# Don't depend on alsa-plugins-pulseaudio-conf.
# It is removed to prevent conflict between alsa and pulseaudio
RDEPENDS_pulseaudio-server_remove = "alsa-plugins-pulseaudio-conf"
