PACKAGECONFIG_append = " gstreamer"

RDEPENDS_${PN}-plugins += " \
		gstreamer1.0 \
		gstreamer1.0-libav \
		gstreamer1.0-plugins-base \
		gstreamer1.0-plugins-base-app \
		gstreamer1.0-plugins-good \
		gstreamer1.0-plugins-good-video4linux2 \
		gstreamer1.0-plugins-bad \
		gstreamer1.0-plugins-bad-camerabin2 \
		libgstbasecamerabinsrc-1.0 \
"
