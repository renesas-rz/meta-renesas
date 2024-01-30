DESCRIPTION = "Linux kernel for the RZ/V2H based board"

COMPATIBLE_MACHINE_rzv2h = "(rzv2h-dev|rzv2h-evk-alpha|rzv2h-evk-ver1)"

BRANCH = "rzv2h-5.10-cip17"
SRCREV = "397f22ac9c748f4635c3e9b032dcd45e58908011"

LINUX_VERSION = "5.10.145-cip17"

SRC_URI_remove = " \
	file://0001-Fixed-an-issue-that-caused-flicker-when-outputting-t.patch \
"
