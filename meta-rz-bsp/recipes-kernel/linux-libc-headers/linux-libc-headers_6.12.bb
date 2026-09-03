require recipes-kernel/linux-libc-headers/linux-libc-headers.inc

KERNEL_URL = "git://github.com/renesas-rz/rz_linux-cip.git"
LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

python __anonymous() {
    pk = d.getVar("PREFERRED_PROVIDER_virtual/kernel") or ""
    if pk.endswith("-rt"):
        d.appendVar("OVERRIDES", ":rt")
}

# default: non-RT
KERNEL_BRANCH ?= "rz-6.12-cip14"
KERNEL_REV ?= "1fb07478288ad3bc054318258ea36d010026e363"
KERNEL_BRANCH:rzg3l-family = "rz-6.12-cip8"
KERNEL_REV:rzg3l-family = "e6c894b7436f14ba9ddda9e5807d3e19e9e2e803"
KERNEL_BRANCH:rzt2n-family = "rz-6.12-cip15"
KERNEL_REV:rzt2n-family = "c5ec1a096276c7cc6d346aaf71c23120bdecf51b"

# RT override
KERNEL_BRANCH:rt = "rz-6.12-cip14-rt"
KERNEL_REV:rt = "197e2b7ac8885618d0db4489e86392040f794987"
KERNEL_BRANCH:rzt2n-family:rt= "rz-6.12-cip15-rt"
KERNEL_REV:rzt2n-family:rt= "1fc7381cbab913328e6540b09ad64275a413f387"

BRANCH = "${KERNEL_BRANCH}"
SRCREV = "${KERNEL_REV}"

SRC_URI = "${KERNEL_URL};branch=${BRANCH};protocol=https"

FILESEXTRAPATHS:prepend := "${THISDIR}/../linux/files:"

S = "${WORKDIR}/git"
