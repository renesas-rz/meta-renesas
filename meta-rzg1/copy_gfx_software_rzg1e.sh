#!/bin/sh

### Note: To run this script, please stand on meta-rzg1 to run.

if [ ! -d $1/RZG_Series_Software_Package_for_Linux ] &&
   [ ! -d $1/RZG_Series_Evaluation_Software_Package_for_Linux ]
then
  tar -C $1 -zxf $1/RZG_Series_Software_Package_for_Linux*.tar.gz 2>/dev/null ||
  tar -C $1 -zxf $1/RZG_Series_Evaluation_Software_Package_for_Linux*.tar.gz
fi

if [ ! -d $1/RZG_Series_Software_Package_of_Linux_Drivers ] &&
   [ ! -d $1/RZG_Series_Evaluation_Software_Package_of_Linux_Drivers ]
then
  tar -C $1 -zxf $1/RZG_Series_Software_Package_of_Linux_Drivers*.tar.gz 2>/dev/null ||
  tar -C $1 -zxf $1/RZG_Series_Evaluation_Software_Package_of_Linux_Drivers*.tar.gz
fi

SGX_KM=`find $1 -name *SGX_KM_E2.tar.bz2 | tail -1`
if [ -z "$SGX_KM" ]; then
	echo "Error: can not find *SGX_KM_E2.tar.bz2"
	exit -1
fi
cp -r $SGX_KM recipes-kernel/gles-module/kernel-module-gles/SGX_KM_E2.tar.bz2

SGX_LIB=`find $1 -name *r8a7745_linux_sgx_binaries_gles2.tar.bz2 | tail -1`
if [ -z "$SGX_LIB" ]; then
	echo "Error: can not find *r8a7745_linux_sgx_binaries_gles2.tar.bz2"
	exit -1
fi
cp -r $SGX_LIB recipes-graphics/gles-module/gles-user-module/r8a7745_linux_sgx_binaries_gles2.tar.bz2
