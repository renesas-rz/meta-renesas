DISTRO_FEATURES_append = " docker"

PACKAGES = " \
    packagegroup-docker \
    "

DOCKER_PKGS = "docker ca-certificates ntpdate kernel-module-nf-conntrack-netlink"
RDEPENDS_packagegroup-docker = " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'docker', '${DOCKER_PKGS}', '',d)} \
"
