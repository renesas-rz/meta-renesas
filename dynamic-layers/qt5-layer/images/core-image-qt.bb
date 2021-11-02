require recipes-graphics/images/core-image-weston.bb
require include/core-image-renesas-base.inc
require include/core-image-renesas-mmp.inc
require include/core-image-bsp.inc

SUMMARY = "Renesas core image with Qt5 platform support base on core-image-weston"

IMAGE_INSTALL_append = " packagegroup-qt5 packagegroup-qt5-examples "
IMAGE_INSTALL_append = " ${@oe.utils.conditional("QT_DEMO", "1", " \
			        kernel-module-uvcvideo \
			        qt5-launch-demo \
			        qt5everywheredemo \
			        cinematicexperience \
			        qtsmarthome \
			        qt5nmapper \
			        qt5nmapcarousedemo \
			        qt5ledscreen \
			        quitbattery \
			        quitindicators \
			        qtwebkit-examples-examples \
			        qtdemo-extrafiles \
				", "", d)}"
