FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

EXTRA_OECONF += "\
    --with-inputdrivers=linuxinput \
"
