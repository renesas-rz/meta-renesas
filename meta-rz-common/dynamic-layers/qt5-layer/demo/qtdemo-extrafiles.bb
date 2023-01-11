DESCRIPTION = "Recipe for extra files for Qt demonstration"
LICENSE = "CLOSED"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI = " \
	file://qtdemo-extrafiles.tar \
	http://resource.renesas.com/resource/lib/img/products/media/auto-j/microcontrollers-microprocessors/rz/rzg/qt-videos/renesas-bigideasforeveryspace.mp4;name=video \
 	http://resource.renesas.com/resource/lib/img/products/media/auto-j/microcontrollers-microprocessors/rz/rzg/hmi-mmpoc-videos/h264-hd-30.mp4;name=video_hd30 \
	http://resource.renesas.com/resource/lib/img/products/media/auto-j/microcontrollers-microprocessors/rz/rzg/hmi-mmpoc-videos/h264-bl10-fhd-30p-5m-aac-lc-stereo-124k-48000x264.mp4;name=video_fhd30 \
	"

SRC_URI[video.md5sum] = "44748e486a971d1e039fbfc3bc15b6f1"
SRC_URI[video_hd30.md5sum] = "619825b0713dc39f7689c85750f136a7"
SRC_URI[video_fhd30.md5sum] = "33696ae57ae684e2cc6f83b3aabee005"

SRC = "${WORKDIR}/extrafiles/"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}/home/root/demo/icons
	install -d ${D}/home/root/demo/scripts/
	install -d ${D}/home/root/videos
	install -d ${D}/home/root/audios
	install -d ${D}/home/root/info/img

	install -Dm 755 ${SRC}/demo/icons/* ${D}/home/root/demo/icons/
	install -Dm 755 ${SRC}/demo/scripts/* ${D}/home/root/demo/scripts/
	install -Dm 644 ${WORKDIR}/*.mp4 ${D}/home/root/videos/
	install -Dm 644 ${SRC}/audios/* ${D}/home/root/audios/
	install -Dm 644 ${SRC}/info/img/* ${D}/home/root/info/img/
	install -Dm 755 ${SRC}/info/renesas_rzg2l_info.html ${D}/home/root/info/

}

FILES_${PN} = " \
	/home/root/demo/* \
	/home/root/videos/* \
	/home/root/audios/* \
	/home/root/info/* \
"
