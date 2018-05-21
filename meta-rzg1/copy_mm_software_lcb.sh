#!/bin/sh

if [ ! -d $1/RZG_Series_Software_Package_for_Linux ] &&
   [ ! -d $1/RZG_Series*_Software_Package_for_Linux ]
then
  tar -C $1 -zxf $1/RZG_Series_Software_Package_for_Linux*.tar.gz 2>/dev/null ||
  tar -C $1 -zxf $1/RZG_Series*_Software_Package_for_Linux*.tar.gz
fi

if [ ! -d $1/RZG_Series_Software_Package_of_Linux_Drivers ] &&
   [ ! -d $1/RZG_Series*_Software_Package_of_Linux_Drivers ]
then
  tar -C $1 -zxf $1/RZG_Series_Software_Package_of_Linux_Drivers*.tar.gz 2>/dev/null ||
  tar -C $1 -zxf $1/RZG_Series*_Software_Package_of_Linux_Drivers*.tar.gz
fi

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

MM_DRVs=`find $1 -type d -name RZGMMPRDL001 | tail -1`
if [ -z "$MM_DRVs" ]
then
	echo "Could not find directory RZGMMPRDL001" >&2
	exit 1
fi
cp -rf $MM_DRVs $TMP

MM_LIBs=`find $1 -type d -name RZGMMPRLL001 | tail -1`
if [ -z "$MM_LIBs" ]
then
	echo "Could not find directory RZGMMPRLL001" >&2
	exit 1
fi
cp -rf $MM_LIBs $TMP

KERNEL_MODULES="$TMP/RZGMMPRDL001"
tar -C $KERNEL_MODULES/fdpm/fdpm-module/files/ -jcf fdpm-kernel.tar.bz2 .
tar -C $KERNEL_MODULES/mmngr/mmngr-module/files/ -jcf mmngr-kernel.tar.bz2 .
tar -C $KERNEL_MODULES/mmngrbuf/mmngrbuf-module/files/ -jcf mmngrbuf-kernel.tar.bz2 .
tar -C $KERNEL_MODULES/s3ctl/s3ctl-module/files/ -jcf s3ctl-kernel.tar.bz2 .
tar -C $KERNEL_MODULES/vspm/vspm-module/files/ -jcf vspm-kernel.tar.bz2 .

USER_MODULES="$TMP/RZGMMPRLL001"
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

OMX_LIBs=`find $1 -name omx_video_lib_v* | tail -1`
OMX_DRVs=`find $1 -name omx_video_v* | tail -1`
cp -rf $OMX_LIBs/* $OMXTMP
cp -rf $OMX_DRVs/* $OMXTMP

if [ -f $OMXTMP/RTM0AC0000M264D100JPCL4.zip ];then
	unzip -q -d $TMP $OMXTMP/RTM0AC0000M264D100JPCL4.zip
else
	unzip -q -d $TMP $OMXTMP/*RTM0AC0000M264D100JPCL4.zip
	mv $TMP/*RTM0AC0000M264D100JPCL4 $TMP/RTM0AC0000M264D100JPCL4
fi
tar zxf $TMP/RTM0AC0000M264D100JPCL4/Software.tar.gz -C $TMP/RTM0AC0000M264D100JPCL4/
rm $TMP/RTM0AC0000M264D100JPCL4/Software.tar.gz
tar -C $TMP/ -jcf RTM0AC0000M264D100JPCL4.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000M264D100JPCL4.tar.bz2 recipes-multimedia/omx-module/files/

if [ -f $OMXTMP/RTM0AC0000M264E100JPCL4.zip ];then
	unzip -q -d $TMP $OMXTMP/RTM0AC0000M264E100JPCL4.zip
else
	unzip -q -d $TMP $OMXTMP/*RTM0AC0000M264E100JPCL4.zip
	mv $TMP/*RTM0AC0000M264E100JPCL4 $TMP/RTM0AC0000M264E100JPCL4
fi
tar zxf $TMP/RTM0AC0000M264E100JPCL4/Software.tar.gz -C $TMP/RTM0AC0000M264E100JPCL4/
rm $TMP/RTM0AC0000M264E100JPCL4/Software.tar.gz
tar -C $TMP/ -jcf RTM0AC0000M264E100JPCL4.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000M264E100JPCL4.tar.bz2 recipes-multimedia/omx-module/files/

if [ -f $OMXTMP/RTM0AC0000MVPL0100JPCL4.zip ];then
	unzip -q -d $TMP $OMXTMP/RTM0AC0000MVPL0100JPCL4.zip
else
	unzip -q -d $TMP $OMXTMP/*RTM0AC0000MVPL0100JPCL4.zip
	mv $TMP/*RTM0AC0000MVPL0100JPCL4 $TMP/RTM0AC0000MVPL0100JPCL4
fi
tar zxf $TMP/RTM0AC0000MVPL0100JPCL4/Software.tar.gz -C $TMP/RTM0AC0000MVPL0100JPCL4/
rm $TMP/RTM0AC0000MVPL0100JPCL4/Software.tar.gz
tar -C $TMP/ -jcf RTM0AC0000MVPL0100JPCL4.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000MVPL0100JPCL4.tar.bz2 recipes-multimedia/omx-module/files/

if [ -f $OMXTMP/RTM0AC0000MVRC0100JPCL4.zip ];then
	unzip -q -d $TMP $OMXTMP/RTM0AC0000MVRC0100JPCL4.zip
else
	unzip -q -d $TMP $OMXTMP/*RTM0AC0000MVRC0100JPCL4.zip
	mv $TMP/*RTM0AC0000MVRC0100JPCL4 $TMP/RTM0AC0000MVRC0100JPCL4
fi
tar zxf $TMP/RTM0AC0000MVRC0100JPCL4/Software.tar.gz -C $TMP/RTM0AC0000MVRC0100JPCL4/
rm $TMP/RTM0AC0000MVRC0100JPCL4/Software.tar.gz
tar -C $TMP/ -jcf RTM0AC0000MVRC0100JPCL4.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000MVRC0100JPCL4.tar.bz2 recipes-multimedia/omx-module/files/

if [ -f $OMXTMP/RTM0AC0000ZMCL0100JPCL4.zip ];then
	unzip -q -d $TMP $OMXTMP/RTM0AC0000ZMCL0100JPCL4.zip
else
	unzip -q -d $TMP $OMXTMP/*RTM0AC0000ZMCL0100JPCL4.zip
	mv $TMP/*RTM0AC0000ZMCL0100JPCL4 $TMP/RTM0AC0000ZMCL0100JPCL4
fi
tar zxf $TMP/RTM0AC0000ZMCL0100JPCL4/Software.tar.gz -C $TMP/RTM0AC0000ZMCL0100JPCL4/
rm $TMP/RTM0AC0000ZMCL0100JPCL4/Software.tar.gz
tar -C $TMP/ -jcf RTM0AC0000ZMCL0100JPCL4.tar.bz2 .
rm -rf $TMP/*
mv RTM0AC0000ZMCL0100JPCL4.tar.bz2 recipes-multimedia/omx-module/files/

unzip -q -d $TMP $OMXTMP/RTM0AC0000ZUVC0100JPCL4.zip
mv $TMP/RTM0AC0000ZUVC0100JPCL4 $TMP/uvcs
tar -C $TMP/ -jcf uvcs-kernel.tar.bz2 .
rm -rf $TMP
mv uvcs-kernel.tar.bz2 recipes-kernel/uvcs-module/files

rm -rf $OMXTMP
