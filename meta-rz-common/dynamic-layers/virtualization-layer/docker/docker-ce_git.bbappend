INITSCRIPT_PACKAGES = "${@bb.utils.contains('DISTRO_FEATURES','systemd','', '${PN}',d)}"
INITSCRIPT_NAME:${PN} = "${@bb.utils.contains('DISTRO_FEATURES','systemd','', 'docker.init',d)}"
