#!/bin/sh

if [ ! -d $1/RZG_Series_Evaluation_Software_Package_for_Linux ]
then
  tar -C $1 -zxf $1/RZG_Series_Evaluation_Software_Package_for_Linux-*.tar.gz
fi

if [ ! -d $1/RZG_Series_Evaluation_Software_Package_of_Linux_Drivers ]
then
  tar -C $1 -zxf $1/RZG_Series_Evaluation_Software_Package_of_Linux_Drivers-*.tar.gz
fi

find_change_name(){
    cur_path=`pwd`
	fileP=`find . -name $1 | tail -1`
	if [ "X${fileP}" != "X" ]; then
		tmp_path=`dirname $fileP | tail -1`
		cd $tmp_path
		mv -f $1 $2
	fi
	cd $cur_path
}
change_names() {
	if [ ! -e $1 ]; then
		echo "Directory $1 not existed. Exit !"
		exit
	fi
	current_path=`pwd`
	cd $1

	find_change_name libomxr_core.so.0.0.0 libomxr_core.so.2.0.0
	find_change_name libomxr_mc_cmn.so.0.0.0 libomxr_mc_cmn.so.2.0.0
	find_change_name libomxr_mc_h264d.so.0.0.0 libomxr_mc_h264d.so.2.0.0
	find_change_name libomxr_mc_h264e.so.0.0.0 libomxr_mc_h264e.so.2.0.0
	find_change_name libomxr_mc_vecmn.so.0.0.0 libomxr_mc_vecmn.so.2.0.0
	find_change_name libomxr_mc_vcmn.so.0.0.0 libomxr_mc_vcmn.so.2.0.0
	find_change_name libomxr_mc_vdcmn.so.0.0.0 libomxr_mc_vdcmn.so.2.0.0
	find_change_name libuvcs_dec.so.0.0.0 libuvcs_dec.so.1.0.0
	find_change_name libuvcs_enc.so.0.0.0 libuvcs_enc.so.1.0.0
	find_change_name libvcp3_avcd.so.0.0.0 libvcp3_avcd.so.1.0.0
	find_change_name libvcp3_avce.so.0.0.0 libvcp3_avce.so.1.0.0
	find_change_name libvcp3_mcvd.so.0.0.0 libvcp3_mcvd.so.1.0.0
	find_change_name libvcp3_mcve.so.0.0.0 libvcp3_mcve.so.1.0.0

	cd $current_path
}


TMPDIRS=

trap 'delete_tmp_dirs' QUIT TERM HUP EXIT

delete_tmp_dirs()
{
	if [ -n "$TMPDIRS" ] ; then
		echo deleting temp dirs...
		echo $TMPDIRS
		rm -rf $TMPDIRS
	else
		echo no tmp dirs
	fi
}

TMP=`mktemp -d`
TMPDIRS="$TMPDIRS $TMP"

MM_DRVs=`find $1 -type d -name RCH2M2MMPRDL001 | tail -1`
if [ -z "$MM_DRVs" ]
then
	echo "Could not find directory RCH2M2MMPRDL001" >&2
	exit 1
fi
cp -rf $MM_DRVs $TMP

MM_LIBs=`find $1 -type d -name RCH2M2MMPRLL001 | tail -1`
if [ -z "$MM_LIBs" ]
then
	echo "Could not find directory RCH2M2MMPRLL001" >&2
	exit 1
fi
cp -rf $MM_LIBs $TMP

KERNEL_MODULES="$TMP/RCH2M2MMPRDL001"
tar -C $KERNEL_MODULES/fdpm/fdpm-module/files/ -jcf fdpm-kernel.tar.bz2 .
tar -C $KERNEL_MODULES/mmngr/mmngr-module/files/ -jcf mmngr-kernel.tar.bz2 .
tar -C $KERNEL_MODULES/mmngrbuf/mmngrbuf-module/files/ -jcf mmngrbuf-kernel.tar.bz2 .
tar -C $KERNEL_MODULES/s3ctl/s3ctl-module/files/ -jcf s3ctl-kernel.tar.bz2 .
tar -C $KERNEL_MODULES/vspm/vspm-module/files/ -jcf vspm-kernel.tar.bz2 .

USER_MODULES="$TMP/RCH2M2MMPRLL001"
tar -C $USER_MODULES/fdpm/fdpm-module/files/ -jcf fdpm.tar.bz2 .
tar -C $USER_MODULES/mmngr/mmngr-module/files/ -jcf mmngr.tar.bz2 .
tar -C $USER_MODULES/mmngrbuf/mmngrbuf-module/files/ -jcf mmngrbuf.tar.bz2 .
tar -C $USER_MODULES/s3ctl/s3ctl-module/files/ -jcf s3ctl.tar.bz2 .
tar -C $USER_MODULES/vspm/vspm-module/files/ -jcf vspm.tar.bz2 .

rm -rf $TMP/*

mv fdpm-kernel.tar.bz2 recipes-kernel/fdpm-module/files
mv mmngr-kernel.tar.bz2 recipes-kernel/mmngr-module/files/mmngr.tar.bz2
mv mmngrbuf-kernel.tar.bz2 recipes-kernel/mmngr-module/files/mmngrbuf.tar.bz2
mv s3ctl-kernel.tar.bz2 recipes-kernel/s3ctl-module/files
mv vspm-kernel.tar.bz2 recipes-kernel/vspm-module/files

mv fdpm.tar.bz2 recipes-multimedia/fdpm-module/files
mv mmngr.tar.bz2 recipes-multimedia/mmngr-module/files
mv mmngrbuf.tar.bz2 recipes-multimedia/mmngr-module/files
mv s3ctl.tar.bz2 recipes-multimedia/s3ctl-module/files
mv vspm.tar.bz2 recipes-multimedia/vspm-module/files/vspm-user.tar.bz2

###
OMXTMP=`mktemp -d`
TMPDIRS="$TMPDIRS $OMXTMP"

#cp -a $1/R-Car_Series_Evaluation_Software_Package_for_Linux/omx_video_m2e2_v160_eva/* $OMXTMP
#cp -a $1/R-Car_Series_Evaluation_Software_Package_of_Linux_Drivers/omx_video_v160_eva/* $OMXTMP
OMX_LIBs=`find $1 -name omx_video_m2e2_v* | tail -1`
OMX_DRVs=`find $1 -name omx_video_v* | tail -1`
cp -rf $OMX_LIBs/* $OMXTMP
cp -rf $OMX_DRVs/* $OMXTMP

unzip -q -d $TMP $OMXTMP/EVARTM0AC0000XCMCTL20SL32C.zip
mv $TMP/EVARTM0AC0000XCMCTL20SL32C $TMP/RTM0AC0000XCMCTL20SL32C
tar zxf $TMP/RTM0AC0000XCMCTL20SL32C/Software.tar.gz -C $TMP/RTM0AC0000XCMCTL20SL32C/
rm $TMP/RTM0AC0000XCMCTL20SL32C/Software.tar.gz
change_names "$TMP/RTM0AC0000XCMCTL20SL32C"
tar -C $TMP/ -jcf RTM0AC0000XCMCTL20SL32C.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000XCMCTL20SL32C.tar.bz2 recipes-multimedia/omx-module/files/

unzip -q -d $TMP $OMXTMP/EVARTM0AC0000XV264D20SL32C.zip
mv $TMP/EVARTM0AC0000XV264D20SL32C $TMP/RTM0AC0000XV264D20SL32C
tar zxf $TMP/RTM0AC0000XV264D20SL32C/Software.tar.gz -C $TMP/RTM0AC0000XV264D20SL32C
rm $TMP/RTM0AC0000XV264D20SL32C/Software.tar.gz
change_names "$TMP/RTM0AC0000XV264D20SL32C"
tar -C $TMP/ -jcf RTM0AC0000XV264D20SL32C.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000XV264D20SL32C.tar.bz2 recipes-multimedia/omx-module/files/

unzip -q -d $TMP $OMXTMP/EVARTM0AC0000XV264E20SL32C.zip
mv $TMP/EVARTM0AC0000XV264E20SL32C $TMP/RTM0AC0000XV264E20SL32C
tar zxf $TMP/RTM0AC0000XV264E20SL32C/Software.tar.gz -C $TMP/RTM0AC0000XV264E20SL32C
rm $TMP/RTM0AC0000XV264E20SL32C/Software.tar.gz
change_names "$TMP/RTM0AC0000XV264E20SL32C"
tar -C $TMP/ -jcf RTM0AC0000XV264E20SL32C.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000XV264E20SL32C.tar.bz2 recipes-multimedia/omx-module/files/

unzip -q -d $TMP $OMXTMP/EVARTM0AC0000XVCMND20SL32C.zip
mv $TMP/EVARTM0AC0000XVCMND20SL32C $TMP/RTM0AC0000XVCMND20SL32C
tar zxf $TMP/RTM0AC0000XVCMND20SL32C/Software.tar.gz -C $TMP/RTM0AC0000XVCMND20SL32C
rm $TMP/RTM0AC0000XVCMND20SL32C/Software.tar.gz
change_names "$TMP/RTM0AC0000XVCMND20SL32C"
tar -C $TMP/ -jcf RTM0AC0000XVCMND20SL32C.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000XVCMND20SL32C.tar.bz2 recipes-multimedia/omx-module/files/

unzip -q -d $TMP $OMXTMP/EVARTM0AC0000XVCMNE20SL32C.zip
mv $TMP/EVARTM0AC0000XVCMNE20SL32C $TMP/RTM0AC0000XVCMNE20SL32C
tar zxf $TMP/RTM0AC0000XVCMNE20SL32C/Software.tar.gz -C $TMP/RTM0AC0000XVCMNE20SL32C
rm $TMP/RTM0AC0000XVCMNE20SL32C/Software.tar.gz
change_names "$TMP/RTM0AC0000XVCMNE20SL32C"
tar -C $TMP/ -jcf RTM0AC0000XVCMNE20SL32C.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000XVCMNE20SL32C.tar.bz2 recipes-multimedia/omx-module/files/

unzip -q -d $TMP $OMXTMP/RTM0AC0000UVCSCMN1SL32C.zip
mv $TMP/RTM0AC0000UVCSCMN1SL32C $TMP/uvcs
tar -C $TMP/ -jcf uvcs-kernel.tar.bz2 .
rm -rf $TMP
mv uvcs-kernel.tar.bz2 recipes-kernel/uvcs-module/files

rm -rf $OMXTMP
