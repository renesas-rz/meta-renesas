SOC_FAMILY =. "rzg1:"
require conf/machine/include/soc-family.inc
LINUXLIBCVERSION = "4.4%"
PREFERRED_PROVIDER_u-boot ?= "u-boot"
EXTRA_IMAGEDEPENDS += "u-boot"
