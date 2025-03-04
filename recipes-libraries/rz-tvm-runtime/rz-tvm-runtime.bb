SUMMARY = "Apache TVM runtime library for the Renesas RZ series"
DESCRIPTION = "Apache TVM Runtime"
LICENSE = "CLOSED"

SRC_URI = "git://git@github.com/renesas-rz/rzv_drp-ai_tvm.git;protocol=ssh;branch=main"
SRCREV = "56b3dd425ba694dbbdd7766fa1295671f1ffccf0" 
PV = "git${SRCPV}"
S = "${WORKDIR}/git/"
# Only compatible with the V2H and V2N
COMPATIBLE_MACHINE = "(r9a09g057|r9a09g056)"
# Define the target library path
LIBDIR = "${D}${libdir}"
# Symbolic links need to be created to replace the original 3rd party folder thats in tvm/3rdparty/
do_configure() {
    git submodule update --init --recursive
    rm -Rf ${S}/tvm/3rdparty/dmlc-core
    rm -Rf ${S}/tvm/3rdparty/rang
    rm -Rf ${S}/tvm/3rdparty/vta-hw
    rm -Rf ${S}/tvm/3rdparty/protobuf
    rm -Rf ${S}/tvm/3rdparty/libbacktrace
    rm -Rf  ${S}/tvm/3rdparty/libbacktrace
    rm -Rf  ${S}/tvm/3rdparty/onnx
    # Look at the setup folder within the Git repository to understand why this needs to be done
    ln -sf ${S}/3rdparty/dmlc-core ${S}/tvm/3rdparty/dmlc-core
    ln -sf ${S}/3rdparty/rang ${S}/tvm/3rdparty/rang
    ln -sf ${S}/3rdparty/vta-hw ${S}/tvm/3rdparty/vta-hw
    ln -sf ${S}/3rdparty/protobuf ${S}/tvm/3rdparty/protobuf
    ln -sf ${S}/3rdparty/libbacktrace ${S}/tvm/3rdparty/libbacktrace
    ln -sf ${S}/3rdparty/onnx ${S}/tvm/3rdparty/onnx
    #Copy the custom header files into tvm
    cp -r ${S}/setup/include/*.h ${S}/tvm/include/tvm/runtime/
}
#Install header files and the runtime
do_install() {
    install -d ${D}${includedir}
    install -d ${LIBDIR}
    #Install the runtime
    install -m 0644 ${S}/obj/build_runtime/V2H/libtvm_runtime.so  ${LIBDIR}/libtvm_runtime.so.${SRCREV}
    ln -sf libtvm_runtime.so.${SRCREV} ${LIBDIR}/libtvm_runtime.so
    #Install the header files
    cp -R ${S}/tvm/include/tvm/ ${D}${includedir}/
    cp -R ${S}/tvm/3rdparty/dlpack/include/* ${D}${includedir}/
    cp -R ${S}/tvm/3rdparty/dmlc-core/include/* ${D}${includedir}/
    cp -R ${S}/tvm/3rdparty/compiler-rt/* ${D}${includedir}/
}

FILES_${PN} = "${libdir}/libtvm_runtime* ${includedir}/tvm/ ${includedir}/*"