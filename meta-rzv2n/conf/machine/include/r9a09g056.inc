SOC_FAMILY =. "rzv2h:rzv2n:"
require conf/machine/include/soc-family.inc
LINUXLIBCVERSION = "5.10%"

MACHINE_FEATURES_append = " opengles opencl hwh264enc hwh264dec hwh265enc hwh265dec"
