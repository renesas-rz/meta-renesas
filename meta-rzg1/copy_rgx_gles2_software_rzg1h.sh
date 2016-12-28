#!/bin/sh

### Note: To run this script, please stand on meta-rzg1 to run.

if [ ! -d $1/RZG_Series_Evaluation_Software_Package_for_Linux ]
then
  tar -C $1 -zxf $1/RZG_Series_Evaluation_Software_Package_for_Linux-*.tar.gz
fi

if [ ! -d $1/RZG_Series_Evaluation_Software_Package_of_Linux_Drivers ]
then
  tar -C $1 -zxf $1/RZG_Series_Evaluation_Software_Package_of_Linux_Drivers-*.tar.gz
fi

RGX_KM=`find $1/RZG_Series_Evaluation_Software_Package_of_Linux_Drivers/rgx_gles2_h2_v1111b_eva -name *RGX_KM_H2.tar.bz2 | tail -1`
echo "Copy from "${RGX_KM}
if [ -z "$RGX_KM" ]; then
	echo "Error: can not find *RGX_KM_H2.tar.bz2"
	exit -1
fi
cp -r $RGX_KM recipes-kernel/gles-module/gles-kernel-module/RGX_KM_H2.tar.bz2

RGX_LIB=`find $1 -name *r8a7742_linux_rgx_binaries_gles2.tar.bz2 | tail -1`
echo "Copy from "${RGX_LIB}
if [ -z "$RGX_LIB" ]; then
	echo "Error: can not find *r8a7742_linux_rgx_binaries_gles2.tar.bz2"
	exit -1
fi
cp -r $RGX_LIB recipes-graphics/gles-module/gles-user-module/r8a7742_linux_rgx_binaries_gles2.tar.bz2
