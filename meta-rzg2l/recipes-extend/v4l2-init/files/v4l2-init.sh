#!/bin/bash

# List of valid resolutions
valid_resolutions=("2592x1944" "1920x1080" "1280x960")

# Usage information function
function print_usage {
    echo "Usage: $0 <resolution>"
    echo "Available resolutions for ov5645: ${valid_resolutions[@]}. \
Using default resolution '1280x960'."
    echo "Example: $0 1920x1080"
    echo "If no resolution is specified, the default resolution '1280x960' will be used."
}

# Check if help is requested
if [[ "$1" == "-h" ]] || [[ "$1" == "--help" ]]; then
    print_usage
    exit 0
fi

# Check for no input
if [ -z "$1" ]; then
    echo "No resolution specified. Using default resolution: 1280x960"
    ov5645_res="1280x960"
else
    ov5645_res=$1
    # Check if the given resolution is valid
    if [[ ! " ${valid_resolutions[@]} " =~ " ${ov5645_res} " ]]; then
        echo "Invalid resolution: $ov5645_res"
        ov5645_res="1280x960"
        echo "Input resolution is not available. \
Using default resolution: 1280x960"
    fi
fi

# Script operations
cru=$(cat /sys/class/video4linux/video*/name | grep "CRU")
csi2=$(cat /sys/class/video4linux/v4l-subdev*/name | grep "csi2" | head -n 1)
ip=$(cat /sys/class/video4linux/v4l-subdev*/name | grep "cru-ip" | head -n 1)

if [ -z "$cru" ]; then
    echo "No CRU video device found"
    exit 1
fi

media-ctl -d /dev/media0 -r
if [ -z "$csi2" ]; then
    echo "No MIPI CSI2 sub video device found"
    exit 1
fi

if [ -z "$ip" ]; then
    media-ctl -d /dev/media0 -l "'${csi2}':1 -> 'CRU output':0 [1]"
    media-ctl -d /dev/media0 -V "'${csi2}':1 [fmt:UYVY8_2X8/$ov5645_res field:none]"
    media-ctl -d /dev/media0 -V "'ov5645 0-003c':0 [fmt:UYVY8_2X8/$ov5645_res field:none]"
    echo "Linked CRU/CSI2 to ov5645 0-003c with format UYVY8_2X8 and resolution $ov5645_res"
else
    media-ctl -d /dev/media0 -l "'${csi2}':1 -> '${ip}':0 [1]"
    media-ctl -d /dev/media0 -l "'${ip}':1 -> 'CRU output':0 [1]"
    media-ctl -d /dev/media0 -V "'${csi2}':1 [fmt:UYVY8_2X8/$ov5645_res field:none]"
    media-ctl -d /dev/media0 -V "'ov5645 0-003c':0 [fmt:UYVY8_2X8/$ov5645_res field:none]"
    media-ctl -d /dev/media0 -V "'${ip}':0 [fmt:UYVY8_2X8/$ov5645_res field:none]"
    media-ctl -d /dev/media0 -V "'${ip}':1 [fmt:UYVY8_2X8/$ov5645_res field:none]"
    echo "Linked CRU/CSI2 to ov5645 0-003c with format UYVY8_2X8 and resolution $ov5645_res"
fi
