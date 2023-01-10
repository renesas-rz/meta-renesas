SOC_FAMILY =. "rzv2l:"
require conf/machine/include/soc-family.inc
LINUXLIBCVERSION = "5.10%"

MACHINE_FEATURES_append = " opengles opencl hwh264dec hwh264enc"
