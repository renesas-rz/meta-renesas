require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL = "git://github.com/renesas-rz/rz_linux-cip.git"
LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

python __anonymous() {
    pk = d.getVar("PREFERRED_PROVIDER_virtual/kernel") or ""
    if pk.endswith("-rt"):
        d.appendVar("OVERRIDES", ":rt")
}

# default: non-RT
KERNEL_BRANCH ?= "rz-6.12-cip7"
KERNEL_REV ?= "03d16609f9f970a5c1af057dff88d475a26328fc"

# RT override
KERNEL_BRANCH:rt = "rz-6.12-cip7-rt"
KERNEL_REV:rt = "be1f7505aa30da8da520b0e2fd5320eadebd851b"

BRANCH = "${KERNEL_BRANCH}"
SRCREV = "${KERNEL_REV}"

SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

FILESEXTRAPATHS:prepend := "${THISDIR}/../linux/files:"

S = "${WORKDIR}/git"
