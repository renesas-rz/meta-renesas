require include/rzg2h-security-config.inc
inherit native

SUMMARY = "RZ/G2H Security Provisioning Tool"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DIRPATH_SEC_STORAGE = "${HOME}/.secprv"

DIRPATH_GEN_KEY_ROOT = "${DIRPATH_SEC_STORAGE}/${MACHINE}/key"
DIRPATH_SEC_LIB_ROOT = "${DIRPATH_SEC_STORAGE}/${MACHINE}/lib"

DIR_V_MAJOR = '0'
DIR_V_MINOR = '0'
DIR_V_TRACE = '0'
DIR_VERSION = "${DIR_V_MAJOR}.${DIR_V_MINOR}.${DIR_V_TRACE}"

DIR_GEN_USER_KEY = "UserKey"
DIR_GEN_PROV_KEY = "Provisioning"

SRC_URI = "file://tool"

S = "${WORKDIR}/tool"

DEPENDS += "openssl-native vim-native"

addtask newkey after do_configure
do_newkey[dirs] = "${S}"
do_newkey() {
    sh ./sec_keygen.sh -t ${DIRPATH_GEN_KEY_ROOT}
}

addtask update after do_configure
do_update[dirs] = "${S}"
do_update() {
	sh ./sec_keygen.sh -t ${DIRPATH_GEN_KEY_ROOT} -u -d ${DIR_V_MAJOR}.${DIR_V_MINOR}
}

# do_compile() nothing
do_compile[noexec] = "1"

do_install() {

    install -d "${D}/${DIRPATH_SEC_DATADIR_NATIVE}"

    boot_key=$(find "${DIRPATH_GEN_KEY_ROOT}" -name ${DIR_VERSION})
    if [ ! -z ${boot_key} ]; then
        ln -nfs "${boot_key}" "${D}/${SYMLINK_NATIVE_BOOT_KEY_DIR}"
    fi

    user_key=$(find "${boot_key}" -name "${DIR_GEN_USER_KEY}")
    if [ ! -z ${user_key} ]; then
        ln -nfs "${user_key}" "${D}/${SYMLINK_NATIVE_USER_KEY_DIR}"
    fi

    prov_key=$(find "${DIRPATH_GEN_KEY_ROOT}" -name "${DIR_GEN_PROV_KEY}")
    if [ ! -z ${prov_key} ]; then
        ln -nfs "${prov_key}" "${D}/${SYMLINK_NATIVE_PROV_KEY_DIR}"
    fi

    install -d "${D}/${DIRPATH_SEC_LIBDIR_NATIVE}";
    ln -nfs "${DIRPATH_SEC_LIB_ROOT}" "${D}/${SYMLINK_NATIVE_SEC_LIB_DIR}"
}

FILES_${PN} = "${DIRPATH_SEC_DATADIR_NATIVE} ${DIRPATH_SEC_LIBDIR_NATIVE}"
