# For Security Features purpose

# Enable Secure Boot
TRUSTED_BOARD_BOOT          := '0'

# Enable build and load of OP-TEE
ENABLE_SPD_OPTEE            := '0'

# Trusted Board Boot Verification Mode: "encsign" or "sign"
IMG_AUTH_MODE               = "encsign"

# The name of the directory on the host PC where the user keys are stored
DIR_V_MAJOR                 = '0'
DIR_V_MINOR                 = '0'
DIR_V_TRACE                 = '0'
DIR_USER_KEY_VERSION        = "${DIR_V_MAJOR}.${DIR_V_MINOR}.${DIR_V_TRACE}"

# The name of the directory on the host PC where the UFPK is stored
DIR_USER_FACTORY_PROG_KEY   = "user_factory_prog"

DIRPATH_SEC_DATADIR_NATIVE  = "${STAGING_DATADIR_NATIVE}/secprv/${MACHINE}/${DIR_USER_KEY_VERSION}"
SYMLINK_NATIVE_BOOT_KEY_DIR = "${DIRPATH_SEC_DATADIR_NATIVE}/bootkey"
SYMLINK_NATIVE_PROV_KEY_DIR = "${DIRPATH_SEC_DATADIR_NATIVE}/provkey"

DIRPATH_SEC_LIBDIR_NATIVE   = "${STAGING_LIBDIR_NATIVE}/secprv/${MACHINE}"
SYMLINK_NATIVE_SEC_LIB_DIR  = "${DIRPATH_SEC_LIBDIR_NATIVE}/seclib"

DIRPATH_MANIFEST_GENTOOL    = "${STAGING_BINDIR_NATIVE}/manifest_generation_tool"
KCERT_COMMON_OPTION         = "-halgo SHA2-256 -salgo ECDSA-P256 -mskey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/root_of_trust_key.pem"
CCERT_COMMON_OPTION         = "-halgo SHA2-256 -salgo ECDSA-P256"
CCERT_COMMON_OPTION_append  = " \
	${@oe.utils.conditional("IMG_AUTH_MODE", "encsign", " -encimage -ealgo AES-CBC -iekey ${SYMLINK_NATIVE_BOOT_KEY_DIR}/cmn_key_idx0.txt", "",d)} \
"
MANIFEST_GENERATION_KCERT   = "${DIRPATH_MANIFEST_GENTOOL}/manifest_generation_tool.py genkcert ${KCERT_COMMON_OPTION}"
MANIFEST_GENERATION_CCERT   = "${DIRPATH_MANIFEST_GENTOOL}/manifest_generation_tool.py genccert ${CCERT_COMMON_OPTION}"
