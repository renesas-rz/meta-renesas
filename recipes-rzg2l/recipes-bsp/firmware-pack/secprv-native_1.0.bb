SUMMARY = "RZ Security Provisioning"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

require include/rzg2l-security-config.inc
inherit native

DIRPATH_SEC_STORAGE  = "${HOME}/rz_secprv/${MACHINE}"

DIRPATH_GEN_KEY_ROOT = "${DIRPATH_SEC_STORAGE}/Key"
DIRPATH_SEC_LIB_ROOT = "${DIRPATH_SEC_STORAGE}/Lib"

SRC_URI = " \
	file://key_management_tool \
	file://manifest_generation_tool \
"

S = "${WORKDIR}"

DEPENDS += "openssl-native vim-native"

addtask newkey after do_configure
do_newkey[dirs] = "${S}"
do_newkey[nostamp] = "1"
do_newkey() {
	cd ./key_management_tool
	sh ./sec_keygen.sh -t ${DIRPATH_GEN_KEY_ROOT}
}

addtask update after do_configure
do_update[dirs] = "${S}"
do_update[nostamp] = "1"
do_update() {
	cd ./key_management_tool
	sh ./sec_keygen.sh -t ${DIRPATH_GEN_KEY_ROOT} -d ${DIR_USER_KEY_VERSION} -u
}

# do_compile() nothing
do_compile[noexec] = "1"

do_install() {

	if [ -d "${DIRPATH_GEN_KEY_ROOT}" ]; then
		install -d "${D}/${DIRPATH_SEC_DATADIR_NATIVE}"

		boot_key=$(find "${DIRPATH_GEN_KEY_ROOT}" -name "${DIR_USER_KEY_VERSION}")
		if [ -z ${boot_key} ]; then
			echo "Could not find the directory: ${DIRPATH_GEN_KEY_ROOT}/${DIR_USER_KEY_VERSION}"
			exit 1
		fi
		ln -nfs "${boot_key}" "${D}/${SYMLINK_NATIVE_BOOT_KEY_DIR}"

		prov_key=$(find "${DIRPATH_GEN_KEY_ROOT}" -name "${DIR_USER_FACTORY_PROG_KEY}")
		if [ -z ${prov_key} ]; then
			echo "Could not find the directory: ${DIRPATH_GEN_KEY_ROOT}/${DIR_USER_FACTORY_PROG_KEY}"
			exit 1
		fi
		ln -nfs "${prov_key}" "${D}/${SYMLINK_NATIVE_PROV_KEY_DIR}"
	fi

	if [ "${TRUSTED_BOARD_BOOT}" = "1" ]; then
		install -d "${D}${bindir}"
		cp -rf --no-preserve=ownership "${S}"/manifest_generation_tool "${D}${bindir}"
	fi

	if [ -d "${DIRPATH_SEC_LIB_ROOT}" ]; then
		install -d "${D}/${DIRPATH_SEC_LIBDIR_NATIVE}";
		ln -nfs "${DIRPATH_SEC_LIB_ROOT}" "${D}/${SYMLINK_NATIVE_SEC_LIB_DIR}"
	fi
}
