DESCRIPTION = "Mali EGL/GLES User Module"
LICENSE = "CLOSED"

require include/rzg2-path-common.inc

PN = "mali-user-module"
PV = "r30"
PR = "p0"

COMPATIBLE_MACHINE = "(r9a07g044l|r9a07g044c)"
PACKAGE_ARCH = "${MACHINE_ARCH}"

S = "${WORKDIR}/mali_um"

SRC_URI = "file://mali_um.tar.gz"

inherit systemd pkgconfig

DEPENDS += "patchelf-native"

do_fetch[file-checksums] = ""
do_populate_lic[noexec] = "1"
do_compile[noexec] = "1"
do_package_qa[noexec] = "1"

# Only need GBM header from mesa when using wayland feature
do_populate_sysroot[depends] += "${@bb.utils.contains("DISTRO_FEATURES", "wayland", "virtual/mesa:do_populate_sysroot", "", d)}"

USE_WAYLAND = "${@bb.utils.contains("DISTRO_FEATURES", "wayland", "1", "0", d)}"

# Default backend shoule be wayland if possible
MALI_BACKEND_DEFAULT ?= "${@'wayland' if '${USE_WAYLAND}' == '1' else 'fbdev'}"

LIB_MALI = "libmali.so"

do_install() {
	# Install header files
	install -d ${D}${includedir}/EGL
	install -d ${D}${includedir}/KHR
	install -d ${D}${includedir}/GLES
	install -d ${D}${includedir}/GLES2
	install -d ${D}${includedir}/GLES3
	install -m 644 ${S}/usr/include/EGL/*.h ${D}/${includedir}/EGL/
	install -m 644 ${S}/usr/include/KHR/*.h ${D}/${includedir}/KHR/
	install -m 644 ${S}/usr/include/GLES/*.h ${D}/${includedir}/GLES/
	install -m 644 ${S}/usr/include/GLES2/*.h ${D}/${includedir}/GLES2/
	install -m 644 ${S}/usr/include/GLES3/*.h ${D}/${includedir}/GLES3/

	# Install pre-builded binaries
	install -d ${D}${libdir}
	install -m 755 ${S}/usr/lib/*.so ${D}${libdir}/

	# Install supported windows system
	install -Dm 0644 ${S}/usr/lib/mali_wayland/${LIB_MALI} ${D}${libdir}/mali_wayland/${LIB_MALI}
	install -Dm 0644 ${S}/usr/lib/mali_fbdev/${LIB_MALI} ${D}${libdir}/mali_fbdev/${LIB_MALI}

	# Create symbolic link
	cd ${D}${libdir}
	if [ "${MALI_BACKEND_DEFAULT}" = "wayland" ]; then
		ln -fs mali_wayland/${LIB_MALI} ${LIB_MALI}
	else
		ln -fs mali_fbdev/${LIB_MALI} ${LIB_MALI}
	fi
	ln -fs libEGL.so libEGL.so.1
	ln -fs libGLESv1_CM.so libGLESv1_CM.so.1
	ln -fs libGLESv2.so libGLESv2.so.2
	ln -fs libmali.so libmali.so.0
	ln -fs libwayland-egl.so libwayland-egl.so.1
	ln -fs libgbm.so libgbm.so.1

	# Mali prebuilt binares do not have DT_SONAME, so we must set them manually.
	# This step help the package can be used in rdepend package.
	patchelf --set-soname libmali.so ${D}${libdir}/mali_wayland/libmali.so
	patchelf --set-soname libmali.so ${D}${libdir}/mali_fbdev/libmali.so
	patchelf --set-soname libEGL.so ${D}${libdir}/libEGL.so
	patchelf --set-soname libGLESv1_CM.so ${D}${libdir}/libGLESv1_CM.so
	patchelf --set-soname libGLESv2.so ${D}${libdir}/libGLESv2.so
	patchelf --set-soname libwayland-egl.so ${D}${libdir}/libwayland-egl.so
	patchelf --set-soname libgbm.so ${D}${libdir}/libgbm.so

	# Install pkgconfig
	install -d ${D}${libdir}/pkgconfig
	install -m 644 ${S}/usr/lib/pkgconfig/*.pc ${D}${libdir}/pkgconfig/
}

PACKAGES = "\
	${PN} \
"

PROVIDES += " libmali virtual/libegl virtual/egl virtual/libgles2 virtual/libgbm virtual/libwayland-egl"
RPROVIDES_${PN} += "\
	libmali \
	libegl \
	libegl1 \
	libgles1 \
	libglesv1-cm \
        libgles2-mesa \
        libgles2-mesa-dev \
	libgles2 \
	libgles2-dev \
	libgbm \
	libwayland-egl \
"
RDEPENDS_${PN} = " \
	kernel-module-mali \
"

FILES_${PN} = " \
	${includedir}/* \
	${libdir}/* \
	${libdir}/pkgconfig/* \
"

INSANE_SKIP_${PN} = "ldflags build-deps file-rdeps dev-so"

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"
