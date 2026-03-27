#!/bin/bash
set -uo pipefail

DEFAULT_RES="1280x960"
PIXFMT="UYVY8_1X16"
FIELD="none"

ALL=0
DEV=""
RES=""
LIST=0

VIN_LIST="4,0" # CSI20 VIN default, CSI40 VIN default
VIN_PROVIDED=0

model=$(cat /sys/devices/soc0/soc_id)

detect_camera_backend() {
  if [[ "$model" = *r8a774* ]]; then
    echo "VIN_CSI"
  else
    echo "CRU_CAMIDX"
  fi
}

CAMERA_BACKEND=$(detect_camera_backend)

# List of valid resolutions
if [[ "$model" = *r9a07g04* ]] || [[ "$model" = *r9a07g054* ]] || [[ "$model" = *r8a774* ]]; then
valid_resolutions=("2592x1944" "1920x1080" "1280x960")
elif [[ "$model" = *r9a09g057* ]] || [[ "$model" = *r9a09g047* ]] || [[ "$model" = *r9a09g056* ]]; then
valid_resolutions=("1920x1080" "1280x960")
fi


usage() {
cat <<EOF
v4l2-init.sh - Initialize media links/formats for all CRU/VINs cameras (dynamic count)
             - Available resolutions for $model ov5645: ${valid_resolutions[@]}.
USAGE:
  Init all detected CRU/VINs cameras:
    $0 -a [-r WxH]

  List detected CRU/VINs video nodes:
    $0 -l
EOF

  case "$CAMERA_BACKEND" in
    VIN_CSI)
cat <<EOF

  Init selected VIN(s) VIN4 for CSI20 and VIN0 for CSI40:
    $0 --vin 4,0 [-r WxH]

OPTIONS:
  -a, --all             Init VIN4 for CSI20 and VIN0 for CSI40
  -r, --res WxH         Resolution (default: ${DEFAULT_RES})
  -l, --list            List detected VIN video nodes
  --vin N[,M]           Init selected VIN(s), valid range: 0-7
                        vin_cs40:0->3; vin_cs20:4->7
  -h, --help            Show help
EOF
    ;;

    CRU_CAMIDX)
cat <<EOF

  Init a single camera by video node:
    $0 -d /dev/videoX [-r WxH]

OPTIONS:
  -a, --all             Init all detected CRU cameras
  -d, --device DEV      Init only one camera (/dev/videoX)
  -r, --res WxH         Resolution (default: ${DEFAULT_RES})
  -l, --list            List detected CRU video nodes
  -h, --help            Show help
EOF
    ;;
  esac
}

# ---- Discover video devices whose name contains "CRU"
get_cru_video_devs() {
  local n
  for n in /sys/class/video4linux/video*; do
    [[ -e "$n/name" ]] || continue
    if grep -Eq "CRU|VIN" "$n/name"; then
      echo "/dev/$(basename "$n")"
    fi
  done | sort -V
}

# Map /dev/videoX -> X
video_dev_to_index() {
  local dev="$1"
  dev="${dev#/dev/video}"
  [[ "$dev" =~ ^[0-9]+$ ]] || return 1
  echo "$dev"
}

# Sort subdev names by v4l-subdev index
subdev_names_sorted() {
  local n idx name
  for n in /sys/class/video4linux/v4l-subdev*; do
    [[ -r "$n/name" ]] || continue
    idx="${n##*/v4l-subdev}"
    name="$(cat "$n/name")"
    printf "%04d %s\n" "$idx" "$name"
  done | sort -n | cut -d' ' -f2-
}

pick_nth_match() {
  local pattern="$1"
  local nth="$2"
  subdev_names_sorted | grep -i "$pattern" | sed -n "${nth}p"
}


init_one_cam_by_camidx() {
  local cam_idx="$1"   # 0..count-1
  local res="$2"
  local nth=$((cam_idx + 1))
  local media="/dev/media${cam_idx}"

  if [[ ! -e "$media" ]]; then
    echo "Camera idx ${cam_idx}: missing ${media} -> skip"
    return 0
  fi

  local csi2 ip ov5645
  csi2="$(pick_nth_match "csi2" "$nth" || true)"
  ip="$(pick_nth_match "cru-ip" "$nth" || true)"
  ov5645="$(pick_nth_match "ov5645" "$nth" || true)"

  if [[ ! " ${valid_resolutions[@]} " =~ " ${res} " ]]; then
	  echo "Invalid resolution $res for $ov5645. Using default resolution: 1280x960"
	  res="1280x960"
  fi

  if [[ -z "$csi2" || -z "$ip" || -z "$ov5645" ]]; then
    echo "Camera idx ${cam_idx}: subdev missing (csi2='$csi2' ip='$ip' ov5645='$ov5645') -> skip"
    return 0
  fi

  media-ctl -d $media -r
  media-ctl -d $media -V "'${csi2}':1 [fmt:${PIXFMT}/${res} field:${FIELD}]"
  media-ctl -d $media -V "'${ov5645}':0 [fmt:${PIXFMT}/${res} field:${FIELD}]"
  media-ctl -d $media -V "'${ip}':0 [fmt:${PIXFMT}/${res} field:${FIELD}]"
  media-ctl -d $media -V "'${ip}':1 [fmt:${PIXFMT}/${res} field:${FIELD}]"

  echo "Camera idx ${cam_idx} linked CRU/CSI2 to ${ov5645} with ${PIXFMT} ${res}"
}

init_vin_default() {
  # Vin Channel connect with CSI20 IF
  local vin_ch_csi20="$1"
  # Vin Channel connect with CSI40 IF
  local vin_ch_csi40="$2"
  local res="$3"
  local csi20 csi40
  csi20=$(cat /sys/class/video4linux/v4l-subdev*/name | grep "fea80000.csi2")
  csi40=$(cat /sys/class/video4linux/v4l-subdev*/name | grep "feaa0000.csi2")

  if [[ ! " ${valid_resolutions[@]} " =~ " ${res} " ]]; then
    echo "Invalid resolution $res for csi20 and csi40. Using default resolution: 1280x960"
    res="1280x960"
  fi

  # Virtual channel for CSI20 IF based on value which is set in devicetree
  local vc_csi20=1

  # Virtual channel for CSI40 IF based on value which is set in devicetree
  local vc_csi40=1

  media-ctl -d /dev/media0 -r

  if [ -z "$csi20" ]
  then
    echo "No CSI20 sub video device founds"
  else
    media-ctl -d /dev/media0 -l "'${csi20}':$vc_csi20 -> 'VIN$vin_ch_csi20 output':0 [1]"
    media-ctl -d /dev/media0 -V "'${csi20}':$vc_csi20 [fmt:${PIXFMT}/${res} field:none]"
    media-ctl -d /dev/media0 -V "'ov5645 2-003c':0 [fmt:${PIXFMT}/${res} field:none]"
    echo "Link VIN$vin_ch_csi20(/dev/video$vin_ch_csi20) to CSI20"
    echo "Link CSI20 to ov5645 2-003c with format ${PIXFMT} and resolution ${res}"
  fi

  if [ -z "$csi40" ]
  then
    echo "No CSI40 sub video device founds"
  else
    media-ctl -d /dev/media0 -l "'${csi40}':$vc_csi40 -> 'VIN$vin_ch_csi40 output':0 [1]"
    media-ctl -d /dev/media0 -V "'${csi40}':$vc_csi40 [fmt:${PIXFMT}/${res} field:none]"
    media-ctl -d /dev/media0 -V "'ov5645 3-003c':0 [fmt:${PIXFMT}/${res} field:none]"
    echo "Link VIN$vin_ch_csi40(/dev/video$vin_ch_csi40) to CSI40"
    echo "Link CSI40 to ov5645 3-003c with format ${PIXFMT} and resolution ${res}"
  fi
}


init_pre_common() {
# Default resolution
[[ -n "$RES" ]] || RES="$DEFAULT_RES"

# ---- Discover count
CRU_DEVS="$(get_cru_video_devs || true)"
if [[ -z "$CRU_DEVS" ]]; then
  echo "No CRU/VIN cameras detected (no /sys/class/video4linux/video*/name contains 'CRU/VIN')."
  exit 0
fi

if [[ "$LIST" -eq 1 ]]; then
  count="$(printf "%s\n" "$CRU_DEVS" | wc -l | tr -d ' ')"
  echo "Detected $count CRU/VIN video node(s):"
  printf "  %s\n" $CRU_DEVS
  exit 0
fi
}

init_camera_vin() {
  IFS=',' read -r -a VINS <<< "$VIN_LIST"

  if (( VIN_PROVIDED )); then
    if [[ ${#VINS[@]} -ne 2 ]]; then
      echo "ERROR: --vin must contain exactly 2 elements (e.g. --vin 0,4)"
      exit 1
    fi


    if [[ "${VINS[0]}" == "${VINS[1]}" ]]; then
      echo "ERROR: VINs must be different (got ${VINS[0]},${VINS[1]})"
      exit 1
    fi

    for vin in "${VINS[@]}"; do
      if [[ ! "$vin" =~ ^[0-7]$ ]]; then
        echo "ERROR: invalid VIN \"$vin\" (valid range: 0 -> 7)"
        exit 1
      fi
    done
  fi

  init_vin_default "${VINS[0]}" "${VINS[1]}" "$RES"
}

init_camera_camidx() {
  if [[ "$ALL" -eq 1 ]]; then
    count="$(printf "%s\n" "$CRU_DEVS" | wc -l | tr -d ' ')"
    echo "Detected $count CRU/VIN camera(s):"

    cam_idx=0
    while [[ $cam_idx -lt $count ]]; do
      init_one_cam_by_camidx "$cam_idx" "$RES"
      cam_idx=$((cam_idx + 1))
    done
  else
    # Find DEV position in detected list -> cam_idx
    cam_idx=-1
    idx=0

    for d in $CRU_DEVS; do
      if [[ "$d" == "$DEV" ]]; then
        cam_idx="$idx"
        break
      fi
      idx=$((idx + 1))
    done

    if [[ "$cam_idx" -lt 0 ]]; then
      echo "Device '$DEV' is not a detected CRU camera."
      exit 1
    fi

    init_one_cam_by_camidx "$cam_idx" "$RES"
  fi
}

# ---- Parse args (with missing-arg checks)
while [[ $# -gt 0 ]]; do
  case "$1" in
    -a|--all)
      ALL=1
      shift
      ;;

    -l|--list)
      LIST=1
      shift
      ;;

    -d|--device)
      if [[ $# -lt 2 || "$2" == -* ]]; then
        echo "Error: -d/--device requires an argument (e.g. /dev/video0)"
        usage
        exit 1
      fi
      DEV="$2"
      shift 2
      ;;

    -r|--res)
      if [[ $# -lt 2 || "$2" == -* ]]; then
        echo "Error: -r/--res requires an argument (e.g. 1920x1080)"
        usage
        exit 1
      fi
      RES="$2"
      shift 2
      ;;

    --vin)
      if [[ $# -lt 2 || "$2" == -* ]]; then
	echo "Error: --vin requires an argument (e.g. 0,4)"
	usage
	exit 1
      fi
      VIN_LIST="$2"
      VIN_PROVIDED=1
      shift 2
      ;;

    -h|--help)
      usage
      exit 0
      ;;

    *)
      echo "Unknown option: $1"
      usage
      exit 1
      ;;
  esac
done


# ---- Execute
case "$CAMERA_BACKEND" in
  VIN_CSI)
    [[ -n "$DEV" ]] && { echo "Error: Option -d cannot supported"; usage; exit 1; }
    [[ "$LIST" -eq 0 && "$ALL" -eq 1 && "$VIN_PROVIDED" -eq 1 ]] && { echo "Error: do not use -a with --vin"; exit 1; }
    [[ "$LIST" -eq 0 && "$ALL" -eq 0 && "$VIN_PROVIDED" -eq 0 ]] && { echo "Error: must use -a or --vin (or -l to list)"; usage; exit 1; }
    init_pre_common
    init_camera_vin
    ;;
  CRU_CAMIDX)
    [[ "$VIN_PROVIDED" -eq 1 ]] && { echo "Error: Option --vin cannot supported"; usage; exit 1; }
    [[ "$LIST" -eq 0 && "$ALL" -eq 1 && -n "$DEV" ]] && { echo "Error: do not use -a with -d"; exit 1; }
    [[ "$LIST" -eq 0 && "$ALL" -eq 0 && -z "$DEV" ]] && { echo "Error: must use -a or -d (or -l to list)"; usage; exit 1; }
    init_pre_common
    init_camera_camidx
    ;;
  *)
    echo "ERROR: Unknown camera detected"
    exit 1
    ;;
esac

