#!/bin/sh

rcar_vin=$(cat /sys/class/video4linux/video*/name | grep "VIN")
csi20=$(cat /sys/class/video4linux/v4l-subdev*/name | grep "fea80000.csi2")
csi40=$(cat /sys/class/video4linux/v4l-subdev*/name | grep "feaa0000.csi2")
hostname=$(uname -n)

# User can change these below variables for their usage
# Vin Channel connect with CSI20 IF
vin_ch_csi20=4

# Vin Channel connect with CSI40 IF
vin_ch_csi40=0

# Vin Channel connect with CSI40 IF of G2E
vin_ch_g2e=4

# Virtual channel for CSI20 IF based on value which is set in devicetree
vc_csi20=1

# Virtual channel for CSI40 IF based on value which is set in devicetree
vc_csi40=1

# Virtual channel for CSI40 IF of G2E based on value which is set in devicetree
vc_csi_g2e=1

# Resolution setting of OV5645 which connects to CSI20 IF
ov5645_res_csi20=1920x1080

# Resolution setting of OV5645 which connects to CSI40 IF
ov5645_res_csi40=1920x1080

if [ -z "$rcar_vin" ]
then
	echo "No rcar-vin video device founds"
else
	media-ctl -d /dev/media0 -r
	case "$hostname" in
		hihope-rzg2m | hihope-rzg2n | hihope-rzg2h)
			if [ -z "$csi20" ]
			then
				echo "No CSI20 sub video device founds"
			else
				media-ctl -d /dev/media0 -l "'rcar_csi2 fea80000.csi2':$vc_csi20 -> 'VIN$vin_ch_csi20 output':0 [1]"
				media-ctl -d /dev/media0 -V "'rcar_csi2 fea80000.csi2':$vc_csi20 [fmt:UYVY8_2X8/$ov5645_res_csi20 field:none]"
				media-ctl -d /dev/media0 -V "'ov5645 2-003c':0 [fmt:UYVY8_2X8/$ov5645_res_csi20 field:none]"
				echo "Link VIN$vin_ch_csi20(/dev/video$vin_ch_csi20) to CSI20"
				echo "Link CSI20 to ov5645 2-003c with format UYVY8_2X8 and resolution $ov5645_res_csi20"
			fi

			if [ -z "$csi40" ]
			then
				echo "No CSI40 sub video device founds"
			else
				media-ctl -d /dev/media0 -l "'rcar_csi2 feaa0000.csi2':$vc_csi40 -> 'VIN$vin_ch_csi40 output':0 [1]"
				media-ctl -d /dev/media0 -V "'rcar_csi2 feaa0000.csi2':$vc_csi40 [fmt:UYVY8_2X8/$ov5645_res_csi40 field:none]"
				media-ctl -d /dev/media0 -V "'ov5645 3-003c':0 [fmt:UYVY8_2X8/$ov5645_res_csi40 field:none]"
				echo "Link VIN$vin_ch_csi40(/dev/video$vin_ch_csi40) to CSI40"
				echo "Link CSI40 to ov5645 3-003c with format UYVY8_2X8 and resolution $ov5645_res_csi40"
			fi
			;;
		ek874)
			if [ -z "$csi40" ]
			then
				echo "No CSI40 sub video device founds"
			else
				media-ctl -d /dev/media0 -l "'rcar_csi2 feaa0000.csi2':$vc_csi_g2e -> 'VIN$vin_ch_g2e output':0 [1]"
				media-ctl -d /dev/media0 -V "'rcar_csi2 feaa0000.csi2':$vc_csi_g2e [fmt:UYVY8_2X8/1280x960 field:none]"
				media-ctl -d /dev/media0 -V "'ov5645 3-003c':0 [fmt:UYVY8_2X8/1280x960 field:none]"
				echo "Link VIN$vin_ch_g2e(/dev/video$(expr $vin_ch_g2e - 4)) to CSI40"
				echo "Link CSI40 to ov5645 3-003c with format UYVY8_2X8 and resolution 1280x960"
			fi
			;;
		*)
	esac
fi
