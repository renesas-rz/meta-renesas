#!/bin/sh

file="/etc/gstvspfilter.conf"

current_input=`cat $file | head -n 1 | cut -d'=' -f 2`
current_output=`cat $file | tail -n 1 | cut -d'=' -f 2`

for media_device in `ls /dev/media*`
do
	error=`media-ctl -d $media_device -e "fe9a0000.vsp rpf.0 input" | awk '{print $1}'`
	if [ $error != "Entity" ]
	then
		input=`media-ctl -d $media_device -e "fe9a0000.vsp rpf.0 input"`
		output=`media-ctl -d $media_device -e "fe9a0000.vsp wpf.0 output"`
	break
	fi
done

sed -i "s|$current_input|$input|g" $file
sed -i "s|$current_output|$output|g" $file
