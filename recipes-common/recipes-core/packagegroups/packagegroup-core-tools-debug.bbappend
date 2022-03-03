# Remove these packages if user chooses to build without GPLv3
# since they do not have other license
RDEPENDS_${PN}_remove = "${@bb.utils.contains('INCOMPATIBLE_LICENSE', 'GPLv3', 'gdbserver gdb', '', d)}"
