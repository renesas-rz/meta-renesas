FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append += " \
           file://0001-ckermit-fix-error-FILE-aka-struct-_IO_FILE-has-no-me.patch \
           "
