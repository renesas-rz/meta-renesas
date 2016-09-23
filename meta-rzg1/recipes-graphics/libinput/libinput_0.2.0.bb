SUMMARY = "Library to handle input devices in Wayland compositors"
HOMEPAGE = "http://www.freedesktop.org/wiki/Software/libinput/"
SECTION = "libs"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=673e626420c7f859fbe2be3a9c13632d"

DEPENDS = "libevdev udev mtdev"

SRC_URI = "http://www.freedesktop.org/software/${BPN}/${BP}.tar.xz \
"
SRC_URI[md5sum] = "76472cd9764ac40615442cb911c621a1"
SRC_URI[sha256sum] = "822bad40cac1fa90e38569da189a989d4b5f8ef58ec6bc6fefef8b78f825599c"

inherit autotools pkgconfig

FILES_${PN} += "${libdir}/udev/"
FILES_${PN}-dbg += "${libdir}/udev/.debug"
