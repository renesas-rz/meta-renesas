#!/bin/bash

model=$(cat /sys/devices/soc0/soc_id)
if [[ "$model" = *r9a07g04* ]] || [[ "$model" = *r9a07g054* ]]; then
# List of valid resolutions
valid_resolutions=("2592x1944" "1920x1080" "1280x960")
elif [[ "$model" = *r9a09g057* ]] || [[ "$model" = *r9a09g047* ]]; then
valid_resolutions=("1920x1080" "1280x960")
fi

# Usage information function
function print_usage {
    echo "Usage: $0 <resolution>"
    echo "Available resolutions for $model ov5645: ${valid_resolutions[@]}.
Using default resolution '1280x960'."
    echo "Example: $0 1920x1080"
    echo "If no resolution is specified, the default resolution '1280x960' will be used."
}

# Check if help is requested
if [[ "$1" == "-h" ]] || [[ "$1" == "--help" ]]; then
    print_usage
    exit 0
fi

# Script operations
cru=$(cat /sys/class/video4linux/video*/name | grep "CRU")
if [ -z "$cru" ]; then
    echo "No CRU video device found"
    exit 1
fi

count=$(cat /sys/class/video4linux/video*/name | grep "CRU" | wc -l)

for i in $(seq 1 "$count"); do
	media="/dev/media$((i-1))"
	csi2=$(cat /sys/class/video4linux/v4l-subdev*/name | grep "csi2" | sed -n "${i}p")
	ip=$(cat /sys/class/video4linux/v4l-subdev*/name | grep "cru-ip" | sed -n "${i}p")
	ov5645=$(cat /sys/class/video4linux/v4l-subdev*/name | grep "ov5645" | sed -n "${i}p")

	# Check for no input
	if [ -z "$1" ]; then
		echo "No resolution specified. Using default resolution: 1280x960"
		ov5645_res="1280x960"
	else
		ov5645_res=${!i}
		# Check if the given resolution is valid
		if [[ ! " ${valid_resolutions[@]} " =~ " ${ov5645_res} " ]]; then
			echo "Invalid resolution $ov5645_res for $ov5645. Using default resolution: 1280x960"
			ov5645_res="1280x960"
		fi
	fi

	media-ctl -d $media -r

	if [ -z "$csi2" ]; then
		echo "No MIPI CSI2 sub video device found"
		exit 1
	fi

		media-ctl -d $media -l "'${csi2}':1 -> '${ip}':0 [1]"
		media-ctl -d $media -l "'${ip}':1 -> 'CRU output':0 [1]"
		media-ctl -d $media -V "'${csi2}':1 [fmt:UYVY8_1X16/$ov5645_res field:none]"
		media-ctl -d $media -V "'${ov5645}':0 [fmt:UYVY8_1X16/$ov5645_res field:none]"
		media-ctl -d $media -V "'${ip}':0 [fmt:UYVY8_1X16/$ov5645_res field:none]"
		media-ctl -d $media -V "'${ip}':1 [fmt:UYVY8_1X16/$ov5645_res field:none]"
		echo "Camera $((i-1)) linked CRU/CSI2 to $ov5645 with format UYVY8_1X16 and resolution $ov5645_res"

done
