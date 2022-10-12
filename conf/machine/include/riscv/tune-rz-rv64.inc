require conf/machine/include/riscv/tune-riscv.inc

TUNEVALID[rz-rv64] = "Renesas RZ RISC-V 64-bit Series"

AVAILTUNES += " rz-rv64"

# RZ RISC-V 64-bit LSI Group
TUNE_FEATURES:tune-rz-rv64 = "${TUNE_FEATURES:tune-riscv64} rz-rv64"
TUNE_ARCH:tune-rz-rv64 = "riscv64"
TUNE_PKGARCH:tune-rz-rv64 = "riscv64"
PACKAGE_EXTRA_ARCHS:tune-rz-rv64 = "riscv64"

TUNE_CCARGS:append = "${@bb.utils.contains('TUNE_FEATURES', 'rz-rv64', ' -mtune=rz-rv64', ' ', d)}"
