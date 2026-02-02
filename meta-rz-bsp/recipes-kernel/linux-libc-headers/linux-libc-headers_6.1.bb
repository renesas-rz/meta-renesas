require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL = "git://github.com/renesas-rz/rz_linux-cip.git"
LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

python __anonymous() {
    pk = d.getVar("PREFERRED_PROVIDER_virtual/kernel") or ""
    if pk.endswith("-rt"):
        d.appendVar("OVERRIDES", ":rt")
}

# default: non-RT
KERNEL_BRANCH ?= "rz-6.1-cip48"
KERNEL_REV ?= "192b966668eeb6c2f8edebd4dd474d360c338f29"

# RT override
KERNEL_BRANCH:rt = "rz-6.1-cip48-rt26"
KERNEL_REV:rt = "192b966668eeb6c2f8edebd4dd474d360c338f29"

BRANCH = "${KERNEL_BRANCH}"
SRCREV = "${KERNEL_REV}"

SRC_URI = "${KERNEL_URL};branch=${BRANCH}"

FILESEXTRAPATHS:prepend := "${THISDIR}/../linux/files:"

S = "${WORKDIR}/git"
