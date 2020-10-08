FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append += " \
           file://0001-systemd-meson.build-pass-D_GNU_SOURCE-when-checking-.patch \
           file://0002-missing_syscall-when-adding-syscall-replacements-use.patch \
           "
